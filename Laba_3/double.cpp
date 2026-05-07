#include <iostream>
#include <iomanip>
#include <cmath>
#include <numbers>
using namespace std;
//Замечание: для <|v|> и <v^2> знак не играет роли, поэтому будем рассматривать только неотрицательные значения, домножив вероятность на 2
double create_v(double* &vel, unsigned v_max, unsigned size){
    double dv = static_cast<double>(v_max)/static_cast<double>(size);
    vel[0]=0;
    for(unsigned i=1; i<size; i++){
        vel[i] = vel[i-1]+dv;
        if(vel[i]==vel[i-1]){
            cout<<"Слишком много промежутков -- dv cлишком мало"<<endl;
            return 0;
        }
    } 
    return dv;
}
float const pi_f = 3.14159265359f;
float const e_f = 2.718281828459;
double const pi_d = 3.141592653589793;
double const e_d = 2.718281828459045; 
double *create_v_pow2(unsigned v_max, unsigned size){
    double dv = static_cast<double>(v_max)/static_cast<double>(size);
    double *vel2 = new double[size];
    double v = 0;
    vel2[0] = 0;
    for(unsigned i=1; i<size; i++){
        vel2[i] = (v+dv)*(v+dv);
        v = v+dv;
        if(vel2[i]==vel2[i-1]){
            cout<<vel2[i]<<" Слишком много промежутков -- (2vdv+dv) cлишком мало"<<endl;
            return 0;
        }
    } 
    return vel2;
}
double* create_pdf(double* vel, unsigned size, double T){
    double *pdf = new double[size];
    for(unsigned i=0; i<size; i++) pdf[i] = (exp(-vel[i]*vel[i]/T))/sqrt(T*pi_d);
    return pdf;
}
double rec(double *vel, double *pdf, unsigned first_idx, unsigned size){
    if(size==1) return vel[first_idx]*pdf[first_idx];
    double s=0;
    s+=rec(vel, pdf, first_idx, size/2);
    s+=rec(vel, pdf,  first_idx + size/2 , size -size/2);
    return s;
}
double mean_rec(double *vel, double *pdf, double dv, unsigned size){
    return 2*dv*rec(vel, pdf, 0, size);
}
double m_near(double *vel, double *pdf, unsigned size, double dv){
    double *mean = new double[size];
    for (unsigned i = 0; i<size; i++) mean[i] = vel[i]*pdf[i];
    unsigned d = 1;
    while (d<size){
        for(unsigned i = 0; i+d<size; i+=2*d) mean[i] = mean[i] + mean[i+d];
        d*=2;
    }
    double m = 2*dv*mean[0];
    delete[] mean;
    return m;
}
double m_kahan(double *vel, double *pdf, unsigned size, double dv){
    double sum = 0;
    double t = 0;
    for(unsigned i=0; i<size; i++){
        double y = vel[i]*pdf[i] - t;
        double z = sum +y;
        t = z- sum - y;
        sum =  z;
    }
    return 2*dv*sum;
}

double integral(double *vel, double *pdf, unsigned size, double dv){
    double sum = 0;
    for (unsigned i =0; i<size; i++){
        double m = dv*vel[i]*pdf[i];
        sum+= m;
    }
    return 2*sum;
}
double integral_fma(double *vel, double *pdf, unsigned size, double dv){
    double sum = 0;
    for (unsigned i=0; i<size; i++){
        double m = vel[i]*pdf[i];
        sum = fma(dv, m, sum);
    }
    return 2*sum;
}
unsigned V_max(double T){
    double v = 1;
    while((exp(-v*v/T))/sqrt(T*pi_d)>0) v+=1000;
    while((exp(-v*v/T))/sqrt(T*pi_d)==0) v-=100;
    while((exp(-v*v/T))/sqrt(T*pi_d)>0) v+=10;
    return static_cast<unsigned>(v);
}
int main(){
    double T_arr[]={0.1, 1, 10, 100, 10000};
    unsigned V_max_arr[5] = {0};
    unsigned S[] = {10, 100, 1000, 6000};
    cout<<setprecision(15)<<scientific;
    for(unsigned i=0; i<5;i++) V_max_arr[i]=V_max(T_arr[i]);
    for(unsigned i=0; i<5; i++) cout<<V_max_arr[i]<<" ";
    cout<<endl;
    for(unsigned i=0; i<5; i++){
        double T = T_arr[i]; unsigned v_max = V_max_arr[i];
        double *vel_0 = new double[S[0]];
        double dv_0 = create_v(vel_0, v_max, S[0]);
        double *pdf_0 = create_pdf(vel_0, S[0], T);
        double *vel2_0 = create_v_pow2(v_max, S[0]);
        double *vel_1 = new double[S[1]]; double dv_1 = create_v(vel_1, v_max, S[1]); double *pdf_1 = create_pdf(vel_1, S[1], T); double *vel2_1 = create_v_pow2(v_max, S[1]);
        double *vel_2 = new double[S[2]]; double dv_2 = create_v(vel_2, v_max, S[2]); double *pdf_2 = create_pdf(vel_2, S[2], T); double *vel2_2 = create_v_pow2(v_max, S[2]);
        double *vel_3 = new double[S[3]]; double dv_3 = create_v(vel_3, v_max, S[3]); double *pdf_3 = create_pdf(vel_3, S[3], T); double *vel2_3 = create_v_pow2(v_max, S[3]);
        cout<<endl<<"T="<<T<<"\n\n";
        cout<<"Средний модуль скорости для размеров 10, 100, 1000, 6000 соответственно:"<<endl;
        cout<<"Аналитически "<<sqrt(T/pi_d)<<endl;
        cout<<"Рекурсивно "<<mean_rec(vel_0, pdf_0, dv_0, S[0])<<" "<<mean_rec(vel_1, pdf_1, dv_1, S[1])<<" "<<mean_rec(vel_2, pdf_2, dv_2, S[2])<<" "<<mean_rec(vel_3, pdf_3, dv_3, S[3])<<endl;
        cout<<"Рекурсивно без явной рекурсии: "<<m_near(vel_0, pdf_0, S[0], dv_0)<<" "<<m_near(vel_1, pdf_1, S[1], dv_1)<<" "<<m_near(vel_2, pdf_2, S[2], dv_2)<<" "<<m_near(vel_3, pdf_3, S[3], dv_3)<<"\n";
        cout<<"Kahan algorithm: "<<m_kahan(vel_0, pdf_0, S[0], dv_0)<<" "<<m_kahan(vel_1, pdf_1, S[1], dv_1)<<" "<<m_kahan(vel_2, pdf_2, S[2], dv_2)<<" "<<m_kahan(vel_3, pdf_3, S[3], dv_3)<<endl;
        cout<<"integral: "<<integral(vel_0, pdf_0, S[0], dv_0)<<" "<<integral(vel_1, pdf_1, S[1], dv_1)<<" "<<integral(vel_2, pdf_2, S[2], dv_2)<<" "<<integral(vel_3, pdf_3, S[3], dv_3)<<endl;
        cout<<"integral with fma: "<<integral_fma(vel_0, pdf_0, S[0], dv_0)<<" "<<integral_fma(vel_1, pdf_1, S[1], dv_1)<<" "<<integral_fma(vel_2, pdf_2, S[2], dv_2)<<" "<<integral_fma(vel_3, pdf_3, S[3], dv_3)<<"\n\n";
        cout<<"Средний квадрат скорости:"<<endl;
        cout<<"Аналитически "<<static_cast<float>(T)/2<<endl;
        cout<<"Рекурсивно "<<mean_rec(vel2_0, pdf_0, dv_0, S[0])<<" "<<mean_rec(vel2_1, pdf_1, dv_1, S[1])<<" "<<mean_rec(vel2_2, pdf_2, dv_2, S[2])<<" "<<mean_rec(vel2_3, pdf_3, dv_3, S[3])<<endl;
        cout<<"Рекурсивно без явной рекурсии: "<<m_near(vel2_0, pdf_0, S[0], dv_0)<<" "<<m_near(vel2_1, pdf_1, S[1], dv_1)<<" "<<m_near(vel2_2, pdf_2, S[2], dv_2)<<" "<<m_near(vel2_3, pdf_3, S[3], dv_3)<<"\n";
        cout<<"Kahan algorithm: "<<m_kahan(vel2_0, pdf_0, S[0], dv_0)<<" "<<m_kahan(vel2_1, pdf_1, S[1], dv_1)<<" "<<m_kahan(vel2_2, pdf_2, S[2], dv_2)<<" "<<m_kahan(vel2_3, pdf_3, S[3], dv_3)<<endl;
        cout<<"integral: "<<integral(vel2_0, pdf_0, S[0], dv_0)<<" "<<integral(vel2_1, pdf_1, S[1], dv_1)<<" "<<integral(vel2_2, pdf_2, S[2], dv_2)<<" "<<integral(vel2_3, pdf_3, S[3], dv_3)<<endl;
        cout<<"integral with fma: "<<integral_fma(vel2_0, pdf_0, S[0], dv_0)<<" "<<integral_fma(vel2_1, pdf_1, S[1], dv_1)<<" "<<integral_fma(vel2_2, pdf_2, S[2], dv_2)<<" "<<integral_fma(vel2_3, pdf_3, S[3], dv_3)<<"\n\n";

        delete[] pdf_0; delete[] vel_0; delete[] vel2_0;
        delete[] pdf_1; delete[] vel_1; delete[] vel2_1;
        delete[] pdf_2; delete[] vel_2; delete[] vel2_2;
    } 
    return 0;
}
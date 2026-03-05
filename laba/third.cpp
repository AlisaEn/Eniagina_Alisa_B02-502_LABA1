#include <iostream>
#include <chrono>
#include <random>
using namespace std;
void delete_array(int *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
void equel_arr(int *ptr, int *arr, unsigned ptr_size){
    for(unsigned idx=0; idx<ptr_size; ++idx) arr[idx]=ptr[idx];
}
bool s_lin(int array[], unsigned size, int m){
    for(unsigned i=0; i<size; ++i){
        if (array[i]==m) return true;
    }
    return false;
}
void print_arr(int *ptr, unsigned size){
    for(unsigned i=0; i<size; ++i) cout<<"this_ptr["<<i<<"] = "<<ptr[i]<<' ';
    cout<<endl;
}
int *create_array(unsigned N){
    int *ptr = new int[N];
    for(unsigned i=0; i<N;++i){
        ptr[i]=i;
    }
    return ptr;
}

int *generate_array(unsigned int N, default_random_engine& rng){
    uniform_int_distribution<int> dstr(-10'000'000, 10'000'000);
    int *ptr = new int[N];
    for (unsigned idx = 0; idx < N; ++idx) {
        ptr[idx] = dstr(rng);
    }
    return ptr;
}


bool s_A(int *ptr, unsigned size, int m){
    for(unsigned i=0; i<size; ++i){
        if (ptr[i]==m){
            if(i!=0) swap(ptr[0], ptr[i]);
            return true;
        }
    }
    return false;
}

bool s_B(int *ptr, unsigned size, int m){
    for(unsigned i =0; i<size; ++i){
        if(ptr[i]==m){
            if(i!=0) swap(ptr[i-1], ptr[i]);
            return true;
        }
    }
    return false;
}

bool s_C(int *ptr, unsigned size, int m){
    int *count = new int [size];
    for(unsigned i=0; i<size; ++i) count[i] = {0};
    for(unsigned i=0; i<size; ++i){
        if(ptr[i]==m){
            count[i]+=1;
            if(i!=0 and count[i-1]<count[i]){
                swap(count[i], count[i-1]);
                swap(ptr[i], ptr[i-1]);
            }
            delete_array(count);
            return true;
        }
    }
    delete_array(count);
    return false;
}

int main(){
    cout<<"Программа запущена"<<endl;
    unsigned seed = 0;
    default_random_engine rng(seed);
    // Как и предполагалось, не сортирует массив длины 1'000'000
    /*
    unsigned int a =1'000'000;
    int *ptr = generate_array(a, rng);
    sort_arr(ptr, a);
    for(unsigned i =0; i<a; i+=1000){
        cout<<ptr[i];
        if(i!=a-1) cout<<' ';
    }
    cout<<endl;
    delete_array(ptr); */ 
    unsigned len[]={500, 1000, 10000, 40000, 100000,300000, 700000, 1000000};
    long t1_A[8]={0}, t2_A[8]={0}, t1_B[8]={0}, t2_B[8]={0}, t1_C[8]={0}, t2_C[8]={0};
    uniform_int_distribution<int> ds(-10'000'000, 10'000'000);
    uniform_int_distribution<int> ds2(0, 99999);
    for(int i=0; i<8;++i){  //замер времени
        unsigned N=len[i];
        int *ptr_a = generate_array(N, rng);
        int *ptr_b=new int[N], *ptr_c=new int[N], *ptr=new int[N];
        equel_arr(ptr_a, ptr, N);
        equel_arr(ptr_a, ptr_b, N);
        equel_arr(ptr_a, ptr_c, N);
        int *even_arr = new int [100'000], *uneven_arr=new int[100'000];
        for(int k=0; k<9900; k+=500){  //создаём равномерный массив
            for(int j=k; j<k+500; ++j) even_arr[j]=ptr_a[k/500];
        }
        for(int j=99500; j<100'000; j++) even_arr[j] = ptr_a[N-1];
        int step = 1000;  //создаём неравномерный массив
        for(int k=0; k<100'000; k+=step){
            for(int j=k; j<k+step; ++j) uneven_arr[j]=ptr_a[k/step];
            step+= 10000;
        }
        for(int j=63999; j<100'000; ++j) uneven_arr[j]=ds(rng);

        for(int j=0; j<100000; ++j){  //случайным образом перемешиваем массивы
            int r = ds2(rng);
            if(r!=j) swap(even_arr[j],even_arr[r]);
        }
        for(int j=0; j<64000; ++j){
            int r = ds2(rng);
            if(r!=j) swap(uneven_arr[j],uneven_arr[r]);
        }

        auto begin_a1 = chrono::steady_clock::now();
        for (int j =0; j<10'000; ++j){
            s_A(ptr_a, N, even_arr[j]);
        } 
        auto end_a1 = chrono::steady_clock::now();
        auto time_a1 = chrono::duration_cast<chrono::milliseconds>(end_a1 - begin_a1);
        t1_A[i] = time_a1.count();
        equel_arr(ptr, ptr_a, N);
        auto begin_a2 = chrono::steady_clock::now();
        for (int j =0; j<10'000; ++j){
            s_A(ptr_a, N, uneven_arr[j]);
        } 
        auto end_a2 = chrono::steady_clock::now();
        auto time_a2 = chrono::duration_cast<chrono::milliseconds>(end_a2 - begin_a2);
        t2_A[i] = time_a2.count();
        delete_array(ptr_a);

        auto begin_b1 = chrono::steady_clock::now();
        for (int j =0; j<10'000; ++j){
            s_B(ptr_b, N, even_arr[j]);
        } 
        auto end_b1 = chrono::steady_clock::now();
        auto time_b1 = chrono::duration_cast<chrono::milliseconds>(end_b1 - begin_b1);
        t1_B[i] = time_b1.count();
        equel_arr(ptr, ptr_b, N);
        auto begin_b2 = chrono::steady_clock::now();
        for (int j =0; j<10'000; ++j){
            s_B(ptr_b, N, uneven_arr[j]);
        } 
        auto end_b2 = chrono::steady_clock::now();
        auto time_b2 = chrono::duration_cast<chrono::milliseconds>(end_b2 - begin_b2);
        t2_B[i] = time_b2.count();
        delete_array(ptr_b);

        auto begin_c1 = chrono::steady_clock::now();
        for (int j =0; j<10'000; ++j){
            s_C(ptr_c, N, even_arr[j]);
        } 
        auto end_c1 = chrono::steady_clock::now();
        auto time_c1 = chrono::duration_cast<chrono::milliseconds>(end_c1 - begin_c1);
        t1_C[i] = time_c1.count();
        equel_arr(ptr, ptr_c, N);
        auto begin_c2 = chrono::steady_clock::now();
        for (int j =0; j<10'000; ++j){
            s_C(ptr_c, N, uneven_arr[j]);
        } 
        auto end_c2 = chrono::steady_clock::now();
        auto time_c2 = chrono::duration_cast<chrono::milliseconds>(end_c2 - begin_c2);
        t2_C[i] = time_c2.count();
        delete_array(ptr_c);

        delete_array(ptr);
        delete_array(even_arr);
        delete_array(uneven_arr);
    }

    cout<<"Время за 100'000 запусков при равномерном распределении для s_A для длин 500, 1000, 10000, 40000, 100000,300000, 700000, 1000000 соответсвенно"<<endl;
    for(int i=0; i<8; ++i) cout<<t1_A[i]<<", ";
    cout<<"\n\n";

    cout<<"Время за 100'000 запусков при неравномерном распределении для s_A для длин 500, 1000, 10000, 40000, 100000,300000, 700000, 1000000 соответсвенно"<<endl;
    for(int i=0; i<8; ++i) cout<<t2_A[i]<<", ";
    cout<<"\n\n";

    cout<<"Время за 100'000 запусков при равномерном распределении для s_B для длин 500, 1000, 10000, 40000, 100000,300000, 700000, 1000000 соответсвенно"<<endl;
    for(int i=0; i<8; ++i) cout<<t1_B[i]<<", ";
    cout<<"\n\n";

    cout<<"Время за 100'000 запусков при неравномерном распределении для s_B для длин 500, 1000, 10000, 40000, 100000,300000, 700000, 1000000 соответсвенно"<<endl;
    for(int i=0; i<8; ++i) cout<<t2_B[i]<<", ";
    cout<<"\n\n";

    cout<<"Время за 100'000 запусков при равномерном распределении для s_C для длин 500, 1000, 10000, 40000, 100000,300000, 700000, 1000000 соответсвенно"<<endl;
    for(int i=0; i<8; ++i) cout<<t1_C[i]<<", ";
    cout<<"\n\n";

    cout<<"Время за 100'000 запусков при неравномерном распределении для s_B для длин 500, 1000, 10000, 40000, 100000,300000, 700000, 1000000 соответсвенно"<<endl;
    for(int i=0; i<8; ++i) cout<<t2_C[i]<<", ";
    cout<<"\n\n";
    cout<<"Программа выполнена"<<endl;
    return 0;
}
#include <iostream>
using namespace std;
struct Pol{
    int a;
    int k;
};
struct Polynom{
    int n;
    Pol *pol;
};
Polynom mult(Polynom pol1, Polynom pol2){
    int n1 = pol1.n;
    int n2 = pol2.n;
    Pol *p1 = pol1.pol;
    Pol *p2 = pol2.pol;
    int m = p1[0].k + p2[0].k + 1;

    Pol *p =new Pol[m];
    for(int i=m-1; i>=0; --i) {
        p[m-i-1].k=i;
        p[m-i-1].a=0;
    }
    for(int i=0; i<n1; ++i){
        for(int j=0; j<n2; ++j){
            int k,a;
            k=p1[i].k+p2[j].k;
            a=p1[i].a*p2[j].a;
            p[m-k-1].a+=a;
        }
    }
    int n=0;
    for(int i=0; i<m; ++i){
        if(p[i].a!=0) ++n;
    }

    Pol *res = new Pol[n];
    int j=0;
    for(int i=0; i<m; ++i){
        if(p[i].a!=0){
            res[j] = p[i];
            ++j;
        }
    }
    delete[] p;
    p =nullptr;
    Polynom result;
    result.n = n;
    result.pol = res;
    return result;
}

int main(){
    Polynom p1, p2;
    cin>>p1.n;
    p1.pol = new Pol[p1.n];
    for(int i=0; i<p1.n; ++i){
        cin>>p1.pol[i].a>>p1.pol[i].k;
    }
    cin>>p2.n;
    p2.pol = new Pol[p2.n];
    for(int i=0; i<p2.n; ++i){
        cin>>p2.pol[i].a>>p2.pol[i].k;
    }
    Polynom p = mult(p1, p2);
    cout<<p.n<<' ';
    for(int i=0; i<p.n; ++i) cout<<p.pol[i].a<<' '<<p.pol[i].k<<' ';
    delete[] p1.pol;
    p1.pol = nullptr;
    delete[] p2.pol;
    p2.pol = nullptr;
    delete[] p.pol;
    p.pol = nullptr;
    return 0;
}

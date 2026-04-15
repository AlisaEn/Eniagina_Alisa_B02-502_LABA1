//Алгоритм Прима - "про дороги"
#include <iostream>
using namespace std;

int main(){
    long m, n;
    cin>>m;
    cin>>n;
    long k =1;
    while(m>0){
        while(m*k - n < 0) ++k;
        m = m*k - n;
        n = n*k;
        if(m>0) cout<<k<<' ';
        else cout<<k;
    } 
    return 0;
}
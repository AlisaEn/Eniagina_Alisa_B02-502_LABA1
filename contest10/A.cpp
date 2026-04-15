#include <iostream>
using namespace std;
int main(){
    unsigned long g0, g1, g2, n, G;
    g0 = 1, g1 = 1, g2 = 4, G = g1;
    cin>>n;
    if(n==2){
        cout<<4;
        return 0;
    }
    while(n>2){
        G = 2*g2 + 2*g1 -g0;
        g0 = g1, g1 = g2, g2 =G;
        n--;
    }
    cout<<G;
    return 0;
}
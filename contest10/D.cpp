#include <iostream> 
using namespace std;
int main(){
    int f0 =1, f1 =1, f2 =2, n, F =f1;
    cin>>n;
    if(n==2){
        cout<<2;
        return 0;
    }
    for(int i=3; i<=n; i++){
        F = f0 +f1+f2;
        f0 = f1, f1 = f2, f2 =F;
    } 
    cout<<F;
    return 0;
}
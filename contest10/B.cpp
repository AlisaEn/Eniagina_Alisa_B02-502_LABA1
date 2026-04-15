#include <iostream>
using namespace std;
int main(){
    int arr[10] ={1, 5, 8, 10, 13, 16, 18, 21, 24, 30};
    int n;
    cin>>n;
    int mP = (n/10) * arr[9];
    if(n%10!=0) mP+= arr[n%10-1];
    cout<<mP;
    return 0;
}
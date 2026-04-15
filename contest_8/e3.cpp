#include <iostream>
using namespace std;

int main(){
    int n, k, s;
    cin>>n>>k>>s;
    int *arr = new int[s+2];
    arr[0] =0;
    arr[s+1] = n;
    for(int i=1; i<s+1; i++){
        cin>>arr[i];
    }
    int p_idx = 0;
    int c = 0;
    for(int i =1; i<s+2; i++){
        if(arr[i] - arr[i-1]>k){
            cout<<-1;
            delete[] arr;
            return 0;
        }
        if(arr[i]-arr[p_idx]>k){
            p_idx = i-1;
            c++;
        }
    }
    cout<<c;
    delete[] arr;
    return 0;
}
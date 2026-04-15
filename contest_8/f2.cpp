#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int c=1;
    int b, time_end;
    cin>>b>>time_end;
    for(int i=1; i<n; i++){
        int s, e;
        cin>>s>>e;
        if(s>=time_end){
            c++;
            time_end = e;
        }
    }
    cout<<c;
    return 0;
}
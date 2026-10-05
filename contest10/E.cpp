#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    string s1, s2;
    cin>>s1>>s2;
    int m = s1.length(), n = s2.length();
    int **max_L = new int*[n+1];
    for(int i=0; i<n+1; i++){
        max_L[i] = new int[m+1];
    }
    for(int i = 0; i<n+1; i++) max_L[i][0] = 0;
    for(int i=0; i<m+1; i++) max_L[0][i]=0;
    for(int i=1; i<n+1; i++){
        for(int j = 1; j<m+1; j++){
            if(s1[i-1]==s2[j-1]){
                max_L[i][j] = max_L[i-1][j-1] +1;
            }
            else max_L[i][j] = max(max_L[i-1][j], max_L[i][j-1]);
        }
    }
    cout<<(max_L[n][m]*100)/(min(n,m));
    return 0;
}
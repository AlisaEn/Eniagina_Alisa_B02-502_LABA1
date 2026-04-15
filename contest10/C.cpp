#include <iostream>
using namespace std;
int main(){
    int p[10] ={1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int dP[10] = {0};
    int best[10][10];
    for(int i=0; i<10;i++){
        for(int j=0; j<10; j++) best[i][j]=0;
    }
    dP[0] = 1; best[0][0] =1;
    int n;
    cin>>n;
    for (int i=1; i<10; i++){
        dP[i] = p[i];
        int b = i;
        for(int j=0; j<i; j++){
            if(dP[j] +dP[i-j-1]>dP[i]){
                dP[i] = dP[j] + dP[i-j-1];
                b =j;
            }
        }
        if(b<i){
            for(int j=0; j<=i-b-1; j++){
            best[i][j] = best[b][j] +best[i-b-1][j];
            }
        }
        else best[i][i] = 1;
    }
    int n_best[10] = {0};
    int N = n/10;
    int q = n%10;
    cout<<q<<endl;
    for(int i=0; i<10; i++){
        n_best[i] = best[9][i]*N;
        if(q>0) n_best[i] +=best[q-1][i];
    }
    for(int i = 0; i<10; i++){
        if(n_best[i]!=0){
            for(int j=0; j<n_best[i]; j++) cout<<i+1<<" ";
        }
    }
    cout<<"n_best: ";
    for(int i=0; i<10; i++) cout<<n_best[i]<<" ";
    return 0;
}
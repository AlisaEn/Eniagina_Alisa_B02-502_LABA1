#include <iostream>
using namespace std;
struct Mat{
    int N, M;
    int *values;
};
int el (Mat mat, int i, int j){
    int M = mat.M;
    return mat.values[(i-1)*M + j-1];
    }
bool search(Mat mat, int k){
    int N =mat.N;
    int M=mat.M;
    int n=1;
    int m=M;
    while(n<=N and m>0){
        if(el(mat, n, m)==k){
             return true;
        }
        if(el(mat, n, m)<k) ++n;
        if(el(mat, n, m)>k) --m;
    }
    return false;
}
int main(){
   
    Mat mat;
    cin>>mat.N>>mat.M;
    int k;
    cin>>k;
    mat.values = new int[mat.N*mat.M];
    for(int i=0; i<mat.N*mat.M; ++i) cin>>mat.values[i];
    if(search(mat, k)) cout<<'1';
    else cout<<'0';
    delete[] mat.values;
    mat.values = nullptr;
    return 0;
}
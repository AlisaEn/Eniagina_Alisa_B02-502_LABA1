#include <iostream>
using namespace std;
void sort_arr(int *ptr,int N){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int last= N-1; last>0; --last){
            for(int i=0; i<last; ++i){
                if(ptr[i]>ptr[i+1]){
                     int temp = ptr[i];
                    ptr[i] = ptr[i+1];
                    ptr[i+1]= temp; 
                    sorted = false;
                }
            }
        }
    }
} 
void print_arr(int *arr,int N){
    for (int i =0; i<N-1; ++i) cout<<arr[i]<<" ";
    cout<<arr[N-1]<<endl;
}
int main(){
    int v;
    int N;
    cin>>v>>N;
    int *arr = new int[N];
    for (int i=0; i<N;++i){
        int input;
        cin>>input;
        arr[i]=input;
    }
    sort_arr(arr, N);
    int c=0;
    while(v>=arr[c] and c<N){
        v = v -arr[c];
        c++;
    }
    cout<<c;
    return 0;
}
#include <iostream>
using namespace std;
void delete_arr2(int **arr, int n){
    for(int i=0; i<n;i++){
        delete[] arr[i];
    }
}
void print_arr2(int **arr, int n){
    for(int i=0; i<n; i++){
        cout<<'('<<arr[i][0]<<','<<arr[i][1]<<')'<<" ";
    }
}
void sort_arr2(int **arr, int N){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int last= N-1; last>0; --last){
            for(int i=0; i<last; ++i){
                if(arr[i][1]>arr[i+1][1]){
                    swap(arr[i][0], arr[i+1][0]);
                    swap(arr[i][1], arr[i+1][1]);
                    sorted = false;
                }
            }
        }
    }
}
int main(){
    int n;
    cin>>n;
    int **arr = new int*[n];
    for (int i=0; i<n; i++){
        arr[i] = new int[2];
        cin>>arr[i][0]>>arr[i][1];
    }
    sort_arr2(arr,n);
    int c =1;
    int i =0;
    while(i<n){
        int time = arr[i][1];
        i++;
        while(arr[i][0]<time and i<n-1) i++;
        if(arr[i][0]>=time) c++;
        else break;
    }
    cout<<c;
    delete_arr2(arr, n);
    return 0;
}
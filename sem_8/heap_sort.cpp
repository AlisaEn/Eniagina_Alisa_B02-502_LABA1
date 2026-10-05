#include <iostream>
using namespace std;
void print_arr(int *arr, const int size){
    for (int i=0; i<size-1; ++i){
        cout<<arr[i]<<' ';
    }
    cout<<arr[size-1]<<endl;
}
void heapify(int *arr, const int size, int idx_root){ //heap - куча
    int idx_largest = idx_root;
    int idx_l = idx_root*2 +1;
    if(idx_l<size and arr[idx_l]>arr[idx_largest]) idx_largest = idx_l;
    int idx_r = idx_root*2 +2;
    if(idx_r<size and arr[idx_r]>arr[idx_largest]) idx_largest = idx_r;
    if(idx_largest!=idx_root){
        swap(arr[idx_largest], arr[idx_root]);
        heapify(arr, size, idx_largest);
    }
}

void heapSort(int *arr, const int size){
    for (int idx = size-1; idx>=0; --idx) heapify(arr, size, idx);
    for (int idx = size -1; idx>=0; idx--){
        swap(arr[idx], arr[0]);
        heapify(arr, idx, 0);
    }
}

int main(){ //Проверка
    int arr[] = {7, 3, 1, 3, 7, 6, 4, 7, 9, 0};
    const int size = sizeof(arr)/sizeof(arr[0]);
    cout<<size<<endl;
    print_arr(arr, size);
    heapSort(arr, size);
    print_arr(arr, size);
    return 0;
}
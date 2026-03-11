#include <iostream>
using namespace std;
void quicksort(int *arr, int l_idx, int r_idx, int size){
    int op = arr[(l_idx+r_idx)/2];
    while (l_idx < r_idx){
        while (arr[l_idx] < op) ++l_idx;
        while(arr[r_idx] > op) --r_idx;
        if(l_idx <r_idx) swap(arr[l_idx], arr[r_idx]);
    }
    quicksort(arr, 0, l_idx, l_idx -1);
    quicksort(arr, l_idx + 1, size - 1, size - 1 - l_idx);
}
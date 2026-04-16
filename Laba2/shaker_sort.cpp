#include <iostream>
using namespace std;

void delete_array(int *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
int *read_array(unsigned n){
    int *ptr = new int[n];
    for(unsigned i=0; i<n; i++){
        cin>>ptr[i];
    }
    return ptr;
}
void print_arr(int *ptr, unsigned size){
    for(unsigned i=0; i<size-1; ++i) cout<<ptr[i]<<", ";
    cout<<ptr[size-1]<<endl;
}
bool forward_step(int *ptr, unsigned idx_s, unsigned idx_end){
    bool sorted =true;
    for(unsigned i=idx_s; i<idx_end; ++i){
        if(ptr[i]>ptr[i+1]){
            swap(ptr[i], ptr[i+1]);
            sorted = false;
        }
    }
    return sorted;
}
void copy_arr(int *ptr, int*tmp,  unsigned size){
    for(int i=0; i<size; i++) tmp[i]=ptr[i];
}

bool backward_step(int *ptr, unsigned const idx_s, unsigned idx_end){
    bool sorted = true;
    for(unsigned i=idx_end; i>idx_s; --i){
        if(ptr[i]<ptr[i-1]){
             swap(ptr[i], ptr[i-1]);
             sorted =  false;
        }
    }
    return sorted;
}
void shaker_sort(int *ptr, unsigned idx_s, unsigned idx_end){
    bool sorted = false;
    unsigned right = idx_end;
    unsigned left = idx_s;
    while(!sorted){
        sorted = forward_step(ptr, left, right--);
        if (sorted==true) break;
        sorted = backward_step(ptr, left++, right);
    }
}

int main(){
    unsigned n;
    cin>>n;
    int *arr = read_array(n);
    int *tmp =new int[n];
    // Проверка forward_step
    copy_arr(arr, tmp, n);
    forward_step(tmp, 0, n-1);
    cout<<"После одного  шага forward_step"<<endl;
    print_arr(tmp, n);
    // Проверка backward_step
    copy_arr(arr, tmp, n);
    backward_step(tmp, 0, n-1);
    cout<<"После одного  шага backward_step"<<endl;
    print_arr(tmp, n);
    
    //Проверка shaker_sort
    copy_arr(arr, tmp, n);
    shaker_sort(tmp, 0, n-1);
    cout<<"После сортировки shaker_sort"<<endl;
    print_arr(tmp, n);
    delete_array(tmp);
    delete_array(arr);
    /*  ПРИМЕР
    Ввод:
    10
6 2 5 7 4 1 2 9 8 3
Вывод:
После одного  шага forward_step
2, 5, 6, 4, 1, 2, 7, 8, 3, 9
После одного  шага backward_step
1, 6, 2, 5, 7, 4, 2, 3, 9, 8
После сортировки shaker_sort
1, 2, 2, 3, 4, 5, 6, 7, 8, 9
    
    
    */
    return 0;
}

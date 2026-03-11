#include <iostream>
#include <chrono>
#include <random>
using namespace std;
void delete_array(int *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
int *create_array(unsigned N){
    int *ptr = new int[N];
    for(unsigned i=0; i<N;++i){
        ptr[i]=i;
    }
    return ptr;
}
bool s_lin(int array[], unsigned size, int m){
    for(unsigned i=0; i<size; ++i){
        if (array[i]==m) return true;
    }
    return false;
}
bool s_binary(int array[], unsigned size, int m){
    unsigned left_idx =0, r_idx = size-1, mid_idx;
    while(left_idx <r_idx){
        mid_idx = (left_idx + r_idx)/2;
        if(array[mid_idx]==m) return true;
        if(array[mid_idx]>m) r_idx = mid_idx;
        if(array[mid_idx]<m) left_idx = mid_idx +1;
    }
    return false;
}
void print_arr(long *ptr, unsigned size){
    for(unsigned i=0; i<size-1; ++i) cout<<ptr[i]<<", ";
    cout<<ptr[size-1]<<endl;
}

int main(){
    unsigned len[] = {500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000, 500'000, 700'000, 1'000'000};
    long times_lin[10] = {0};
    long times_bin[10]={0};
    for(unsigned int i=0; i<10; ++i){
        unsigned N = len[i];
        int *first = create_array(N);
        int *second = create_array(N);
        auto begin_lin = chrono::steady_clock::now();
        for (unsigned cnt = 100'000;  cnt>0; --cnt){
            s_lin(first, N, 2'000'000);
        } 
        auto end_lin = chrono::steady_clock::now();
        auto time_lin = chrono::duration_cast<chrono::milliseconds>(end_lin - begin_lin);
        times_lin[i] = time_lin.count();
        delete_array(first);
        auto begin_bin = chrono::steady_clock::now();
         for (unsigned cnt = 1'000'000; cnt>0; --cnt){
            s_binary(second, N, 2'000'000);
        }
        auto end_bin = chrono::steady_clock::now();
        auto time_bin = chrono::duration_cast<chrono::milliseconds>(end_bin - begin_bin);
        times_bin[i] = time_bin.count();
        delete_array(second); 
    }
    cout<<"Время (мс) s_lin для худшего случая на 100'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000, 500'000, 700'000, 1'000'0000 соответственно:"<<endl;
    print_arr(times_lin, 10);
    cout<<endl;
    cout<<"Время(худший случай) (мс) s_bin на 1'000'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000, 500'000, 700'000, 1'000'000 соответственно:"<<endl;
    print_arr(times_bin, 10);

    return 0;
}
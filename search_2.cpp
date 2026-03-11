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

int main(){
    unsigned seed = 0;
    default_random_engine rng(seed);
    uniform_int_distribution<int> ds(-10'000'000, 10'000'000);
    unsigned len[] = {500, 1'000, 6'000,  10'000, 40'000, 100'000, 1'000'000};
    long times_s_bin[7]={0};
    for (unsigned i = 0; i<7; ++i){
        unsigned N = len[i];
        int *second = create_array(N);
        auto begin_s_bin = chrono::steady_clock::now();
        for (unsigned cnt = 10'000'000; cnt>0; --cnt){
            s_binary(second, N, ds(rng));
        }
        auto end_s_bin = chrono::steady_clock::now();
        auto time_s_bin = chrono::duration_cast<chrono::milliseconds>(end_s_bin - begin_s_bin);
        times_s_bin[i] = time_s_bin.count();
        delete_array(second);
    }
    cout<<"Время (мс) s_binary на 10'000'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 1'000'000  соответственно:"<<endl;
    for(int i =0; i<7; ++i) cout<<times_s_bin[i]<<", ";
    cout<<endl; 
        return 0;
 }
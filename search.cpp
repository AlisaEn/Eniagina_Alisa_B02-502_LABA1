#include <iostream>
#include <chrono>
#include <random>
using namespace std;
void delete_array(int *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
void print_arr(int *ptr, unsigned size){
    for(unsigned i=0; i<size; ++i) cout<<"this_ptr["<<i<<"] = "<<ptr[i]<<' ';
    cout<<endl;
}
void sort_arr(int *ptr, unsigned size){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(unsigned last=size-1; last>0; --last){
            for(unsigned i=0; i<last; ++i){
                if(ptr[i]>ptr[i+1]){
                    swap(ptr[i], ptr[i+1]);
                    sorted = false;
                } 
            }
        }
    }
}
int *create_array(unsigned N){
    int *ptr = new int[N];
    for(unsigned i=0; i<N;++i){
        ptr[i]=i;
    }
    return ptr;
}
int *generate_array(unsigned int N, default_random_engine& rng){
    uniform_int_distribution<int> dstr(-10'000'000, 10'000'000);
    int *ptr = new int[N];
    for (unsigned idx = 0; idx < N; ++idx) {
        ptr[idx] = dstr(rng);
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
    
    unsigned len[] = {500, 1'000, 6'000,  10'000, 40'000, 100'000};
    long times_s_lin[7]={0};
    long times_s_bin[6]={0};
    for (unsigned i = 0; i<6; ++i){
        unsigned N = len[i];
        int *first = generate_array(N, rng);
        int *second =new int[N];
        for(unsigned j=0; j<N; ++j){
            second[j] = first[j];
        } 
        sort_arr(second, N); 
        auto begin_s_lin = chrono::steady_clock::now();
        for (unsigned cnt = 100'000;  cnt>0; --cnt){
            s_lin(first, N, ds(rng));
        } 
        auto end_s_lin = chrono::steady_clock::now();
        auto time_s_lin = chrono::duration_cast<chrono::milliseconds>(end_s_lin - begin_s_lin);
        times_s_lin[i] = time_s_lin.count();
        delete_array(first);
        auto begin_s_bin = chrono::steady_clock::now();
         for (unsigned cnt = 1'000'000; cnt>0; --cnt){
            s_binary(second, N, ds(rng));
        }
        auto end_s_bin = chrono::steady_clock::now();
        auto time_s_bin = chrono::duration_cast<chrono::milliseconds>(end_s_bin - begin_s_bin);
        times_s_bin[i] = time_s_bin.count();
        delete_array(second); 
    }
    int *first = generate_array(1'000'000, rng);
    auto begin_s_lin = chrono::steady_clock::now();
        for (unsigned cnt = 100'000;  cnt>0; --cnt){
            s_lin(first, 1'000'000, ds(rng));
        } 
        auto end_s_lin = chrono::steady_clock::now();
        auto time_s_lin = chrono::duration_cast<chrono::milliseconds>(end_s_lin - begin_s_lin);
        times_s_lin[8] = time_s_lin.count();
        delete_array(first); 
    cout<<"Время (мс) s_lin на 100'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 1'000'000 соответственно:"<<endl;
    for(int i =0; i<9; ++i) cout<<times_s_lin[i]<<", ";
    cout<<endl;
    cout<<"Время (мс) s_bin на 1'000'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000 соответственно:"<<endl;
    for(int i =0; i<7; ++i) cout<<times_s_bin[i]<<", ";
    cout<<endl; 
    return 0;
}

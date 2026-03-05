#include <iostream>
#include <chrono>
#include <random>
using namespace std;
void delete_array(int *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
void print_arr(int *ptr, unsigned size){
    for(unsigned i=0; i<size; ++i) cout<<"this_ptr["<<i<<"] = "<<ptr[i]<<endl;
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
int *create_array(unsigned n){
    int *ptr = new int[n];
    for(unsigned i=0; i<n;++i){
        ptr[i]=i;
    }
    return ptr;
}
int *generate_array(unsigned int n, default_random_engine& rng){
    uniform_int_distribution<int> dstr(-10'000'000, 10'000'000);
    int *ptr = new int[n];
    for (unsigned idx = 0; idx < n; ++idx) {
        ptr[idx] = dstr(rng);
    }
    return ptr;
}


bool sum_sqr(int ptr[],unsigned size, int m){
    for(unsigned i=0; i<size-1; ++i){
        for(unsigned j=i+1; j<size; ++j){
            if(ptr[i]+ptr[j]==m) {
               // cout<<i<<' '<<j<<endl;
                return true;
            }
        }
    }
    return false;
}
bool sum_linear(int ptr[], unsigned size, int m){
    unsigned left = 0, right = size-1;
    while(left<right){
        if(ptr[left]+ptr[right]==m) return true;
        if(ptr[left]+ptr[right]>m) right-=1;
        if(ptr[left]+ptr[right]<m) left+=1;
    }
    return false;
}
int main(){
    unsigned seed = 0;
    default_random_engine rng(seed);
    
    uniform_int_distribution<int> ds(-10'000'000, 10'000'000);
    
    unsigned len[] = {500, 1'000, 6'000,  10'000, 40'000, 100'000};
    long times_sum_sqr[7]={0};
    long times_sum_lin[6]={0};
    for (unsigned i = 0; i<6; ++i){ // Замеры времени
        unsigned N = len[i];
        int *first = generate_array(N, rng);
       int *second =new int[N];
        for(unsigned j=0; j<N; ++j){
            second[j] = first[j];
        } 
        sort_arr(second, N); 
        auto begin_sum_sqr = chrono::steady_clock::now();
        for (unsigned cnt = 1000;  cnt>0; --cnt){
            sum_sqr(first, N, ds(rng));
        }
        auto end_sum_sqr = chrono::steady_clock::now();
        auto time_sum_sqr = chrono::duration_cast<chrono::milliseconds>(end_sum_sqr - begin_sum_sqr);
        times_sum_sqr[i] = time_sum_sqr.count();
        delete_array(first);
        auto begin_sum_lin = chrono::steady_clock::now();
         for (unsigned cnt = 500'000; cnt>0; --cnt){
            sum_linear(second, N, ds(rng));
        }
        auto end_sum_lin = chrono::steady_clock::now();
        auto time_sum_lin = chrono::duration_cast<chrono::milliseconds>(end_sum_lin - begin_sum_lin);
        times_sum_lin[i] = time_sum_lin.count();
        delete_array(second);  
    }
    int *first = generate_array(1'000'000, rng); // при N =1'000'000 не сортирует, поэтому 1'000'000 отдельно для неотсортированных 
    auto begin_sum_sqr = chrono::steady_clock::now();
    for (unsigned cnt = 1000;  cnt>0; --cnt){
        sum_sqr(first, 1'000'000, ds(rng));
    } 
    auto end_sum_sqr = chrono::steady_clock::now(); 
    auto time_sum_sqr = chrono::duration_cast<chrono::milliseconds>(end_sum_sqr - begin_sum_sqr);
    times_sum_sqr[6] = time_sum_sqr.count();
    delete_array(first);

    cout<<"Время (мс) sum_sqr на 1000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 1'000'000 соответственно:"<<endl;
    for(int i =0; i<7; ++i) cout<<times_sum_sqr[i]<<", ";
    cout<<endl; 
   cout<<"Время (мс) sum_linear на 500'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000 соответственно:"<<endl;
   for(int i =0; i<6; ++i) cout<<times_sum_lin[i]<<", ";
   cout<<endl; 
    return 0;
}

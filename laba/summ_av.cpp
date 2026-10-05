#include <iostream>
#include <chrono>
#include <random>
using namespace std;
void delete_array(int *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
void print_arr(long *ptr, unsigned size){
    for(unsigned i=0; i<size-1; ++i) cout<<ptr[i]<<", ";
    cout<<ptr[size-1]<<endl;
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
    for(unsigned i = 0; i<n;++i){
        ptr[i]=-n/2+i;
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

    unsigned len[] = {500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000, 500'000, 700'000, 1'000'000};
    long times_sqr[10]={0};
    long times_linear_r[6]={0};
    long times_linear_nr[10]={0};
    for (unsigned i = 0; i<10; ++i){
        unsigned N = len[i];
        int *first = generate_array(N, rng);
        if(i<6){
            int *second =new int[N];
            for(unsigned j=0; j<N; ++j){
                second[j] = first[j];
            } 
            sort_arr(second, N); 
            auto begin_linear_r = chrono::steady_clock::now();
            for (unsigned cnt = 10'000; cnt>0; --cnt){
                sum_linear(second, N, ds(rng));
            }
            auto end_linear_r = chrono::steady_clock::now();
            auto time_linear_r = chrono::duration_cast<chrono::milliseconds>(end_linear_r - begin_linear_r);
            times_linear_r[i] = time_linear_r.count();
            delete_array(second);
        
        } 
        int *third = create_array(N); 
        auto begin_sqr = chrono::steady_clock::now();
        for (unsigned cnt = 1'000;  cnt>0; --cnt){
            sum_sqr(first, N, ds(rng));
        } 
        auto end_sqr = chrono::steady_clock::now();
        auto time_sqr = chrono::duration_cast<chrono::milliseconds>(end_sqr - begin_sqr);
        times_sqr[i] = time_sqr.count();
        delete_array(first);
        auto begin_linear_nr = chrono::steady_clock::now();
         for (unsigned cnt = 10'000; cnt>0; --cnt){
            sum_linear(third, N, ds(rng));
        }
        auto end_linear_nr = chrono::steady_clock::now();
        auto time_linear_nr = chrono::duration_cast<chrono::milliseconds>(end_linear_nr - begin_linear_nr);
        times_linear_nr[i] = time_linear_nr.count();
        delete_array(third); 
    }
    
    cout<<"Время (мс) sum_sqr для среднего случая на 1'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000,500'000,  700'000, 1'000'0000 соответственно:"<<endl;
    print_arr(times_sqr, 10);
    cout<<endl;
    cout<<"Время (мс) sum_linear (random) на 10'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000 соответственно:"<<endl;
    print_arr(times_linear_r, 6);
    cout<<"Время (мс) sum_linear (not_random) на 10'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000,500'000, 700'000, 1'000'000 соответственно:"<<endl;
    print_arr(times_linear_nr, 10);
    return 0;
}

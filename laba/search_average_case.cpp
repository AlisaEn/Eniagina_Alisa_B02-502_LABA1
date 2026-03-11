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

    unsigned len[] = {500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000, 500'000, 700'000, 1'000'000};
    long times_s_lin[10]={0};
    long times_s_bin_r[6]={0};
    long times_s_bin_nr[10]={0};
    for (unsigned i = 0; i<6; ++i){
        unsigned N = len[i];
        int *first = generate_array(N, rng);
        int *second =new int[N];
        for(unsigned j=0; j<N; ++j){
            second[j] = first[j];
        } 
        sort_arr(second, N); 
        auto begin_s_bin_r = chrono::steady_clock::now();
         for (unsigned cnt = 1'000'000; cnt>0; --cnt){
            s_binary(second, N, ds(rng));
        }
        auto end_s_bin_r = chrono::steady_clock::now();
        auto time_s_bin_r = chrono::duration_cast<chrono::milliseconds>(end_s_bin_r - begin_s_bin_r);
        times_s_bin_r[i] = time_s_bin_r.count();
        delete_array(second); 
        int *third = create_array(N); 
      /*  auto begin_s_lin = chrono::steady_clock::now();
        for (unsigned cnt = 100'000;  cnt>0; --cnt){
            s_lin(first, N, ds(rng));
        } 
        auto end_s_lin = chrono::steady_clock::now();
        auto time_s_lin = chrono::duration_cast<chrono::milliseconds>(end_s_lin - begin_s_lin);
        times_s_lin[i] = time_s_lin.count(); */
        delete_array(first);
        auto begin_s_bin_nr = chrono::steady_clock::now();
         for (unsigned cnt = 1'000'000; cnt>0; --cnt){
            s_binary(third, N, ds(rng));
        }
        auto end_s_bin_nr = chrono::steady_clock::now();
        auto time_s_bin_nr = chrono::duration_cast<chrono::milliseconds>(end_s_bin_nr - begin_s_bin_nr);
        times_s_bin_nr[i] = time_s_bin_nr.count();
        delete_array(third); 
    }
    for(unsigned int i=6; i<10; ++i){
        unsigned N = len[i];
        int *first = generate_array(N, rng);
        int *third = create_array(N); 
        auto begin_s_lin = chrono::steady_clock::now();
       for (unsigned cnt = 100'000;  cnt>0; --cnt){
            s_lin(first, N, ds(rng));
        } 
        auto end_s_lin = chrono::steady_clock::now();
        auto time_s_lin = chrono::duration_cast<chrono::milliseconds>(end_s_lin - begin_s_lin);
        times_s_lin[i] = time_s_lin.count();
        delete_array(first); 
        auto begin_s_bin_nr = chrono::steady_clock::now();
         for (unsigned cnt = 1'000'000; cnt>0; --cnt){
            s_binary(third, N, ds(rng));
        }
        auto end_s_bin_nr = chrono::steady_clock::now();
        auto time_s_bin_nr = chrono::duration_cast<chrono::milliseconds>(end_s_bin_nr - begin_s_bin_nr);
        times_s_bin_nr[i] = time_s_bin_nr.count();
        delete_array(third); 
    }
    cout<<"Время (мс) s_lin для среднего случая на 100'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000, 500'000, 700'000, 1'000'0000 соответственно:"<<endl;
    print_arr(times_s_lin, 10);
    cout<<endl; 
    cout<<"Время (мс) s_bin (random) на 1'000'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000 соответственно:"<<endl;
    print_arr(times_s_bin_r, 6);
    cout<<"Время (мс) s_bin (not_random) на 1'000'000 запусков для длин 500, 1'000, 6'000,  10'000, 40'000, 100'000, 350'000, 500'000, 700'000, 1'000'000 соответственно:"<<endl;
    print_arr(times_s_bin_nr, 10);
    return 0;
}

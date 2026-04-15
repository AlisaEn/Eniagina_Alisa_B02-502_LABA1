#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int *generate_array(unsigned int N, default_random_engine& rng){
    uniform_int_distribution<int> dstr(-10'000'000, 10'000'000);
    int *ptr = new int[N];
    for (unsigned idx = 0; idx < N; ++idx) {
        ptr[idx] = dstr(rng);
    }
    return ptr;
}
void delete_array(unsigned long *ptr) {
    delete[] ptr;
    ptr = nullptr;
}

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
void print_arr(unsigned long *ptr, unsigned size){
    for(unsigned i=0; i<size-1; ++i) cout<<ptr[i]<<", ";
    cout<<ptr[size-1]<<endl;
}
void print_arr(int *ptr, unsigned size){
    for(unsigned i=0; i<size-1; ++i) cout<<ptr[i]<<", ";
    cout<<ptr[size-1]<<endl;
}
void print_arr(unsigned ptr[], unsigned size){
    for(int i=0; i<size-1; ++i) cout<<ptr[i]<<", ";
    cout<<ptr[size-1]<<endl;
}
unsigned long *create_arr(unsigned N){
    unsigned long *arr = new unsigned long[N];
    for(int i=0; i<N; i++) arr[i] = 0;
    return arr;
}

unsigned long sort_step(int *ptr,unsigned N, unsigned step){
    unsigned long cnt = 0;
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int last=N-step; last>0; last -=step){
            for(unsigned i=0; i<last; i+=step){
                if(ptr[i]>ptr[i+step]){
                    swap(ptr[i], ptr[i+step]);
                    cnt++;
                    sorted = false;
                } 
            }
        }
    }
    return  cnt;
}

unsigned long bubble_sort(int *ptr, unsigned N){
    unsigned long count_swap= 0;
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(unsigned last=N-1; last>0; --last){
            for(unsigned i=0; i<last; ++i){
                if(ptr[i]>ptr[i+1]){
                    swap(ptr[i], ptr[i+1]);
                    count_swap++;
                    sorted = false;
                } 
            }
        }
    }
    return count_swap;
}
unsigned long comb_sort(int *ptr, unsigned N){
    unsigned long count_swap= 0;
    unsigned step = N/2;
    while(step>1){
        count_swap +=sort_step(ptr, N, step);
        step = step/2;
    }
    count_swap += bubble_sort(ptr, N);
    return count_swap;
}

int main(){
    //Проверка сортировки
    unsigned n;
    cin>>n;
    int *arr = read_array(n);
    cout<<bubble_sort(arr, n)<<endl;
    print_arr(arr, n); 
    delete_array(arr);
    //Замер времени
    unsigned len[] = {500, 1'000, 6'000,  10'000, 25'000, 35'000, 50'000, 65'000, 80'000};
    unsigned s = size(len);
    unsigned long *comb_time = create_arr(s);
    unsigned long *comb_count =create_arr(s);
    unsigned long *bubble_time = create_arr(s);
    unsigned long *bubble_count = create_arr(s);
    unsigned seed = 0;
    default_random_engine rng(seed);
    for (unsigned i=s-1; i<s; i++){
        unsigned N = len[i];
        unsigned long count_comb =0;
        unsigned long count_bubble =0;
        auto begin_comb = chrono::steady_clock::now();
         for (unsigned cnt = 50; cnt>0; --cnt){
            int *arr = generate_array(N, rng);
            count_comb += comb_sort(arr, N); 
            delete_array(arr);
        }
        auto end_comb = chrono::steady_clock::now();
        auto time_comb = chrono::duration_cast<chrono::milliseconds>(end_comb - begin_comb);
        comb_time[i] = time_comb.count();
        comb_count[i] = count_comb/50;
        
        auto begin_bubble = chrono::steady_clock::now();
         for (unsigned cnt = 50; cnt>0; --cnt){
            int *arr = generate_array(N, rng);
            count_bubble += bubble_sort(arr, N); 
            delete_array(arr);
        }
        auto end_bubble = chrono::steady_clock::now();
        auto time_bubble = chrono::duration_cast<chrono::milliseconds>(end_bubble - begin_bubble);
        bubble_time[i] = time_bubble.count();
        bubble_count[i] = count_bubble/50;
    };
    cout<<"COMB_SORT"<<endl;
    cout<<"Длины, N"<<endl;
    print_arr(len, s);
    cout<<"Время на сортировку 50 массивов, мс:"<<endl;
    print_arr(comb_time, s);
    cout<<"Среднее кол-во перестановок:"<<endl;
    print_arr(comb_count, s);
    delete_array(comb_time);
    delete_array(comb_count);
    cout<<endl<<endl;

    cout<<"BUBBLE_SORT"<<endl;
    cout<<"Длины, N"<<endl;
    print_arr(len, s);
    cout<<"Время на сортировку 50 массивов, мс:"<<endl;
    print_arr(bubble_time, s);
    cout<<"Среднее кол-во перестановок:"<<endl;
    print_arr(bubble_count, s);
    delete_array(bubble_time);
    delete_array(bubble_count);

    /* Ввод на проверку работы сортировки:
    10
    5 2 7 4 1 3 9 8 10 6
    Вывод:
    15
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    ВЫВОД времени:
    COMB_SORT
    Длины, N
    500, 1000, 6000, 10000, 25000, 35000, 50000, 65000, 80000
    Время на сортировку 50 массивов, мс:
    27, 85, 3148, 9624, 138560, 154232, 479528, 495926, 908655
    Среднее кол-во перестановок:
    46779, 185930, 5930547, 17192546, 127887113, 227090395, 510902026, 779586557, 1097626438

    BUBBLE_SORT
    Длины, N
    500, 1000, 6000, 10000, 25000, 35000, 50000, 65000, 80000
    Время на сортировку 50 массивов, мс:
    21, 77, 2679, 7850, 68482, 147313, 320802, 611441, 1127952
    Среднее кол-во перестановок:
    62809, 250654, 8991978, 24986322, 156092886, 306401992, 625068025, 1057011953, 1599849229
    */
    return 0;
}

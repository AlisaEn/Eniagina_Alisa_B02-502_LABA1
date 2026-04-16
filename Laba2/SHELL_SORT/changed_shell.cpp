#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int *read_array(unsigned n){
    int *ptr = new int[n];
    for(unsigned i=0; i<n; i++){
        cin>>ptr[i];
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
void delete_array(unsigned long *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
void delete_array(int *ptr) {
    delete[] ptr;
    ptr = nullptr;
}
void delete_array(unsigned *ptr) {
    delete[] ptr;
    ptr = nullptr;
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
    for(unsigned i=0; i<size-1; ++i) cout<<ptr[i]<<", ";
    cout<<ptr[size-1]<<endl;
}
unsigned long *create_arr(unsigned N){
    unsigned long *arr = new unsigned long[N];
    for(int i=0; i<N; i++) arr[i] = 0;
    return arr;
}
int * copy_arr(int *ptr, unsigned size){
    int* tmp = new int[size];
    for(int i=0; i<size; i++) tmp[i]=ptr[i];
    return tmp;
}

unsigned long insert_sort(int *ptr, unsigned N){
    unsigned long cnt = 0;
    for(unsigned sorted_idx = N-1; sorted_idx>0; sorted_idx--){
        for(unsigned i = sorted_idx-1; i<N-1; i++){
            if(ptr[i]<=ptr[i+1]) break;
            swap(ptr[i], ptr[i+1]);
            cnt++;
        }
    }
    return cnt;
}
unsigned long shell_step(int *ptr, unsigned n, unsigned step){
    unsigned long cnt = 0;
    for(int sorted_idx = n-1; sorted_idx>0; sorted_idx-=step){
        for(unsigned i = sorted_idx-step; i<n-step; i+=step){
            if(ptr[i]<=ptr[i+step]) break;
            swap(ptr[i], ptr[i+step]);
            cnt++;
        }
    }
    return cnt;
}

unsigned long shell_1(int *ptr, unsigned n){
    unsigned long cnt =0;
    unsigned step = n/2;
    while(step>0){
        cnt+=shell_step(ptr, n, step);
        step /=2;
    }
    return cnt;
}


unsigned long shell_2(int *ptr, unsigned n, unsigned max_d_idx, unsigned *deg){
    unsigned long cnt = 0;
    for(int i = max_d_idx; i>=0; i--){
        cnt+=shell_step(ptr, n, deg[i]);
    }
    return cnt;
}
unsigned long shell_3(int *ptr, unsigned n, unsigned max_F_idx, unsigned *fib){
    unsigned long cnt = 0;
    for(unsigned i = max_F_idx; i>1; i--){
        cnt+=shell_step(ptr, n, fib[i]);
        
    }
    cnt+=insert_sort(ptr, n);
    return cnt;
}
int main(){
    unsigned len[] = {500, 1000, 6000, 10000, 25000, 50'000, 65'000, 80'000};
    unsigned s = size(len);

    unsigned *fib = new unsigned[len[s-1]];
    fib[0]=1; fib[1] =1;
    for(int i=2; i<len[s-1]; i++){
        fib[i] = fib[i-1] + fib[i-2];
    }
    unsigned *max_F = new unsigned[len[s-1]];
    int idx = 0;
    for(int i=0; i<len[s-1]; i++){
        while(i+1>fib[idx]) idx++;
        if(fib[idx]>i+1) idx--;
        max_F[i] = idx;
    }
    unsigned *deg = new unsigned[len[s-1]];
    unsigned m = 2;
    for(int i=0; i<len[s-1]; i++){
        deg[i] = m -1;
        m*=2;
    }
    unsigned *max_d = new unsigned[len[s-1]];
    unsigned id2 = 0;
    max_d[0]=1;
    for(unsigned i=1; i<len[s-1]; i++){
       while(deg[id2]<i+1) id2++;
       if(deg[id2]>i+1) id2--;
       max_d[i] = id2;
    } 

    unsigned seed = 0;
    default_random_engine rng(seed);
    unsigned n;
    cin>>n;
    //Проверка сортировок
    int *arr = generate_array(n, rng);
    int *ptr_1 = copy_arr(arr, n);
    int * ptr_2 =copy_arr(arr, n);
    int *ptr_3 = copy_arr(arr, n);
    cout<<"original_array: ";
    print_arr(arr, n);
    cout<<"insert_sort: "<<insert_sort(ptr_1, n)<<endl;
    print_arr(ptr_1, n);
    cout<<"shell_1: "<<shell_1(arr, n)<<endl;
    print_arr(arr, n);
    cout<<"shell_2: "<<shell_2(ptr_2, n, max_d[n-1], deg)<<endl;
    print_arr(ptr_2, n);
    cout<<"shell_3: "<<shell_3(ptr_3, n, max_F[n-1], fib)<<endl;
    print_arr(ptr_3, n);
    delete(arr);
    delete(ptr_1);
    delete(ptr_2);
    delete(ptr_3);
    
    // Измерение времени
    
    unsigned long *insert_time = create_arr(s);
    unsigned long *insert_count = create_arr(s);
    unsigned long *sh1_time = create_arr(s);
    unsigned long *sh1_count =create_arr(s);
    unsigned long *sh2_time = create_arr(s);
    unsigned long *sh2_count = create_arr(s);
    unsigned long *sh3_time = create_arr(s);
    unsigned long *sh3_count = create_arr(s);
    for (unsigned i=0; i<s; i++){
        unsigned N = len[i];
        unsigned long count_insert =0, count_1 = 0, count_2 = 0, count_3 = 0;
       /* auto begin_insert = chrono::steady_clock::now();
         for (unsigned cnt = 10; cnt>0; --cnt){
            int *arr = generate_array(N, rng);
            count_insert += insert_sort(arr, N); 
            delete_array(arr);
        }
        auto end_insert = chrono::steady_clock::now();
        auto time_insert = chrono::duration_cast<chrono::milliseconds>(end_insert - begin_insert);
        insert_time[i] = time_insert.count();
        insert_count[i] = count_insert/10;
        
        auto begin_1 = chrono::steady_clock::now();
         for (unsigned cnt = 10; cnt>0; --cnt){
            int *arr = generate_array(N, rng);
            count_1 += shell_1(arr, N); 
            delete_array(arr);
        }
        auto end_1 = chrono::steady_clock::now();
        auto time_1 = chrono::duration_cast<chrono::milliseconds>(end_1 - begin_1);
        sh1_time[i] = time_1.count();
        sh1_count[i] = count_1/10;
        */
        auto begin_2 = chrono::steady_clock::now();
         for (unsigned cnt = 15; cnt>0; --cnt){
            int *arr = generate_array(N, rng);
            count_2 += shell_2(arr, N, max_d[N-1], deg); 
            delete_array(arr);
        }
        auto end_2 = chrono::steady_clock::now();
        auto time_2 = chrono::duration_cast<chrono::milliseconds>(end_2 - begin_2);
        sh2_time[i] = time_2.count();
        sh2_count[i] = count_2/15;

        auto begin_3 = chrono::steady_clock::now();
         for (unsigned cnt = 15; cnt>0; --cnt){
            int *arr = generate_array(N, rng);
            count_3 += shell_3(arr, N, max_F[N-1], fib); 
            delete_array(arr);
        }
        auto end_3 = chrono::steady_clock::now();
        auto time_3 = chrono::duration_cast<chrono::milliseconds>(end_3 - begin_3);
        sh3_time[i] = time_3.count();
        sh3_count[i] = count_3/15;
    };
    cout<<"Длины, N:"<<endl;
    print_arr(len, s);
    /*cout<<endl;
    cout<<" INSERT_SORT:"<<endl;
    cout<<"t, мс на сортировку 10 массивов: "<<endl;
    print_arr(insert_time, s);
    cout<<" (среднее) <кол-во перестановок>:"<<endl;
    print_arr(insert_count, s);
    cout<<endl;
    cout<<"SHELL_1:"<<endl;
    cout<<"t, мс на сортировку 10 массивов: "<<endl;
    print_arr(sh1_time, s);
    cout<<" (среднее) <кол-во перестановок>:"<<endl;
    print_arr(sh1_count, s);
    cout<<endl;
    */
    cout<<" SHELL_2:"<<endl;
    cout<<"t, мс на сортировку 15 массивов: "<<endl;
    print_arr(sh2_time, s);
    cout<<" (среднее) <кол-во перестановок>:"<<endl;
    print_arr(sh2_count, s);
    cout<<endl;
    cout<<" SHELL_3:"<<endl;
    cout<<"t, мс на сортировку 15 массивов: "<<endl;
    print_arr(sh3_time, s);
    cout<<" (среднее) <кол-во перестановок>:"<<endl;
    print_arr(sh3_count, s);
    cout<<endl;
    delete_array(insert_time); delete_array(insert_count); 
    delete_array(sh1_time); delete_array(sh1_count);
    delete_array(sh2_time); delete_array(sh2_count);
    delete_array(sh3_time); delete_array(sh3_count);

    delete_array(fib); delete_array(max_F);delete_array(max_d); delete_array(deg);
    return 0;
}
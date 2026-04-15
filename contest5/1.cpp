#include <iostream>
#include <string>
struct Student
{
    std::string name;
    int mark;
};
void delete_array(Student *ptr) {
    delete[] ptr;
    ptr = nullptr;
}

void sort_st(Student *ptr,int N){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int last= N-1; last>0; --last){
            for(int i=0; i<last; ++i){
                if(ptr[i].mark>ptr[i+1].mark or (ptr[i].mark==ptr[i+1].mark and ptr[i].name>ptr[i+1].name)){
                    Student temp = ptr[i];
                    ptr[i] = ptr[i+1];
                    ptr[i+1]= temp; 
                    sorted = false;
                }
            }
        }
    }
} 

int main(){
    int N, idx = 0;
    float M;
    std::cin>>N;
    Student *students = new Student[N];
    Student *good_stud = new Student[N];
    for(int i=0; i<N; ++i){
        std::cin>>students[i].name>>students[i].mark;
    }
    std::cin>>M;
    for(int i = 0; i<N; ++i){
        if(students[i].mark>=M){
            good_stud[idx].name = students[i].name;
            good_stud[idx].mark = students[i].mark;
            ++idx;
        }
    }
    sort_st(good_stud, idx);
    for(int i=0; i<idx-1; ++i) std::cout<<good_stud[i].name<<' ';
    std::cout<<good_stud[idx-1].name<<std::endl; 
    delete_array(students); 
    delete_array (good_stud);
    return 0;
}
#include <iostream>
using namespace std;
struct Stack{
    unsigned top = 0;
    int arr[100];
};

void push(Stack &s, int value){
    s.arr[s.top++] = value;
}
int pop(Stack &s){
    return s.arr[--s.top];
}

int main(){
    int k;
    cin>>k;
    Stack s;
    for (int i =0; i<k; i++){
        int input;
        cin>>input;
         push(s, input);
    }
    int m, c;
    c=0;
    cin>>m;
    while(m>0){
        int p = pop(s);
        c+= m/p;
        m = m%p;
    }
    cout<<c;
    return 0;

}
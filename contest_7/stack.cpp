#include <iostream>
using namespace std;

struct Stack{
    unsigned top = 0;
    char arr[100];
};

void push(Stack &s, char value){
    s.arr[s.top++] = value;
}
int pop(Stack &s){
    return s.arr[--s.top];
}

int main(){
    Stack s_c, s_sq, s_f, s_tr;
    int w =0;
    
    for(char c = getchar(); c!='\n'; c=getchar()){
        if(w>0) break;
        switch(c){
            case '(':
                push(s_c, c);
                break;
            case ')':
                if(s_c.top!=0) pop(s_c);
                else{
                    ++w;
                } 
                break;
            case '[':
                push(s_sq, c);
                break;
            case ']':
                if(s_sq.top!=0) pop(s_sq);
                else{
                    ++w;
                }
                break;
            case '<':
                push(s_tr, c);
                break;
            case '>':
                if(s_tr.top!=0) pop(s_tr);
                else {
                    ++w;
                }
                break;
            case '{':
                push(s_f, c);
                break;
            case '}':
                if(s_f.top!=0) pop(s_f);
                else{
                     ++w;
                }
                break;
        }
    }
    if(s_c.top==0 and s_sq.top==0 and s_f.top==0 and s_tr.top==0 and w==0) cout<<"YES";
    else cout<<"NO";
    return 0;
}
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
    Stack s;
    int w = 0;
    for(char c = getchar(); c!='\n'; c=getchar()){
        if (w>0) break;
        if( c == '[' or c == '<' or c == '{' or c == '(') push(s, c);
        else {
            if (s.top == 0){
                ++w;
                break;
            }
            switch(c){
                case '}':
                    if (s.arr[s.top-1]!='{')  ++w;
                    else pop(s);
                    break;
                case ')':
                    if (s.arr[s.top-1]!='(') ++w;
                    else pop(s);
                    break;
                case ']':
                    if (s.arr[s.top-1]!='[') ++w;
                    else pop(s);
                    break;
                case '>':
                    if (s.arr[s.top-1]!='<') ++w;
                    else pop(s);
                    break;
            }
        }
    }
    if(s.top==0 and w==0) cout<<"YES";
    else cout<<"NO";
    return 0;
}
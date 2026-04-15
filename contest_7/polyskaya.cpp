#include <iostream>
#include <string>
using namespace std;
struct Stack{
    unsigned top = 0;
    string arr[5000];
};

void push(Stack &s, string value){
    s.arr[s.top++] = value;
}
string pop(Stack &s){
    return s.arr[--s.top];
}
string calculate(Stack &s, string n){
    int a = stoi(pop(s));
    int b = stoi(n);
    string sign = pop(s);
    if(sign=="+") return to_string(a+b);
    if(sign=="*") return to_string(a*b);
    return "!";
}

int main(){
    Stack s;
    string input;
    while(true){
        getline(cin, input, ' ');
        if(input =="stop") break;
        if(input== "+" or input=="*") push(s, input);
        else{
            if(s.arr[s.top-1]=="+" or s.arr[s.top-1]=="*"){
                push(s, input);
            }
            else{
                string n = input;
                while(s.top>1 and s.arr[s.top-1]!="+" and s.arr[s.top-1]!="*"){
                    n = calculate(s, n);
                }
                push(s, n);
            }
            
        }
    }
    cout<<stoi(s.arr[0]);
    return 0;
}
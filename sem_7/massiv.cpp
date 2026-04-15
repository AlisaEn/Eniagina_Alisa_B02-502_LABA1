#include <iostream>
using namespace std;

struct Node{
    int field;
    Node *next;
};
struct List{
    Node *HEAD;
    Node *TAIL;
    Node *NIL;
};
void push_front(List *&list, int value){ //Добавление в начало;
    if (list->HEAD == nullptr){
        list->HEAD = new Node();
        list->HEAD->field = value;
        list->HEAD->next = list->NIL;
        list->TAIL= list->HEAD;
        return;
    }
    Node *new_HEAD = new Node();
    new_HEAD->field = value;
    new_HEAD->next = list->HEAD;
    list->HEAD = new_HEAD;
}
List create_list(){
}
void clear(List *&list){
    Node *current = list->HEAD;
    Node *tmp = nullptr;
    while(current!=list->NIL){
        tmp = current->next;
        delete current;
        current = tmp;
}
void destroy(List *&list){
    clear(list);
    delete list->HEAD;
    delete list->NIL;
}
/*void delete_elem(Node *&HEAD, int elem){
    for(Node *current = HEAD; current!=nullptr; current = current->next){
        if(current->next==nullptr and current->field==elem){
             
        }
    } 
}*/
List create_list()
int main(){
    Node *HEAD = nullptr;
    push(list->HEAD, 0);
    push(list->HEAD, -1);
    push(list->HEAD, -2);
    for (Node *current = HEAD; current!=nullptr; current=current->next) cout<<current->field<<' ';
    
}

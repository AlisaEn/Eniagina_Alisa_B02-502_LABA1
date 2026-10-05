#include <iostream>
#include <string>
using namespace std;

struct Node{
    Node *prev;
    Node *next;
    string name;
};

struct List{
    size_t size;
    Node* HEAD;
    Node* TAIL;
    Node* NIL;
    Node *START;
};
List * create_empty_list(){
    List *list = new List;
    list->NIL = new Node();
    list->HEAD = list->NIL;
    list->TAIL = list->NIL;
    list->START = list->HEAD;
    return list;
}
List* push_back(List* list, string new_name){
    if(list==nullptr) return nullptr;
    Node *new_tail = new Node();
    new_tail->name = new_name;
    if(list->HEAD==list->NIL){
      new_tail->prev = list->NIL;
      new_tail->next = list->NIL;
      list->HEAD = new_tail;
      list->TAIL = new_tail;
      list->NIL->next = list->HEAD;
      list->NIL->prev = list->TAIL;
      list->size = 1;
      return list;
    }
    new_tail->prev = list->TAIL;
    new_tail->next = list->NIL;
    list->TAIL->next = new_tail;
    list->TAIL = new_tail;
    list->NIL->prev = list->TAIL;
    list->size++;
    return list;
}
string need_pop(List *&list, int k){
    int a =1;
    Node *current = list->START;
    while(a<k){
        current = current->next;
        if(current==list->NIL) current = current->next;
        ++a;
    }
    string Name = current->name;
    current->next->prev = current->prev;
    current->prev->next = current->next;
    list->START = current->next;
    delete current;
    return Name;
}
void print_list(const List* list){
    if(list==nullptr or list->HEAD==list->NIL) return;
    for(Node *current = list->HEAD; current!=list->TAIL; current=current->next) cout<<current->name<<' ';
    cout<<list->TAIL->name<<endl;
}

int main(){
    int n, k;
    cin>>n;
    List * circle = create_empty_list();
    for(int i=0; i<n; ++i){
        string name;
        cin>>name;
        push_back(circle, name);
    }
    cin>>k;
    string fixed_name;
    cin>>fixed_name;
    Node *current = circle->HEAD;
    int count = 1;
    string name = need_pop(circle, k);
    while(name!=fixed_name){
        count++;
        cout<<endl;
        cout<<name<<' ';
        name =  need_pop(circle, k);
    }
    print_list(circle);
    cout<<endl;
    cout<<count;
    return 0;
}
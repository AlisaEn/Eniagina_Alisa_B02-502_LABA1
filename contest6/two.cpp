#include <iostream>


struct Node{
    Node *prev;
    Node *next;
    int key;
};

struct List{
    size_t size;
    Node* HEAD;
    Node* TAIL;
    Node* NIL;
};
List * create_empty_list(){
    List *list = new List;
    list->NIL = new Node();
    list->HEAD = list->NIL;
    list->TAIL = list->NIL;
    return list;
}

 List* push_front(List *&list, int new_key) {
  if(list==nullptr) return nullptr;
  Node *new_head = new Node();
  new_head->key =new_key;
  if(list->HEAD == list->NIL){
    new_head->prev = list->NIL;
    new_head->next = list->NIL;
    list->HEAD = new_head;
    list->TAIL = new_head;
    list->NIL->prev =new_head;
    list->NIL->next =new_head;
    list->size=1;
    return list;
  }
  new_head->next = list->HEAD;
  new_head->prev = list->NIL;
  list->HEAD->prev = new_head;
  list->HEAD = new_head;
  list->NIL->next = list->HEAD;
  list->size++;
  return list;
}

List* push_back(List* list, int new_key){
    if(list==nullptr) return nullptr;
    Node *new_tail = new Node();
    new_tail->key = new_key;
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

List* insert_after(List* list, Node* prev_ptr, int new_key){
    if(list == nullptr) return nullptr;
    if(prev_ptr ==nullptr) return list;
    Node *new_node = new Node();
    new_node->key = new_key;
    if(list->HEAD==list->NIL){
      new_node->prev = list->NIL;
      new_node->next = list->NIL;
      list->HEAD = new_node;
      list->TAIL = new_node;
      list->NIL->next = list->HEAD;
      list->NIL->prev = list->TAIL;
      list->size = 1;
      return list;
    }
    if(prev_ptr==list->TAIL){
      new_node->prev = list->TAIL;
      new_node->next = list->NIL;
      list->TAIL->next = new_node;
      list->TAIL = new_node;
      list->NIL->prev = list->TAIL;
      list->size++;
      return list;
    }
    new_node->prev = prev_ptr;
    new_node->next = prev_ptr->next;
    new_node->next->prev = new_node;
    prev_ptr->next = new_node;
    list->size++;
    return list;
}
void print_list(const List* list){
    if(list==nullptr or list->HEAD==list->NIL) return;
    for(Node *current = list->HEAD; current!=list->TAIL; current=current->next) std::cout<<current->key<<' ';
    std::cout<<list->TAIL->key<<std::endl;
}

void clear_list(List *&list){
    if(list == nullptr or list->HEAD==list->NIL) return;
    Node* tmp = nullptr;
    for(Node *current = list->HEAD; current!=list->NIL; current=tmp){
      tmp = current->next;
      delete current;
    }
    list->HEAD = list->NIL;
    list->TAIL = list->NIL;
    list->size =0;
}
void destroy_list(List* &list){
    if(list == nullptr) return;
    if( list->HEAD==list->NIL){
      delete list->NIL;
      delete list;
      list = nullptr;
    }
    Node* tmp = nullptr;
    for(Node *current = list->HEAD; current!=list->NIL; current=tmp){
      tmp = current->next;
      delete current;
      return;
    }
    list->HEAD = list->NIL;
    list->TAIL = list->NIL;
    list->size =0;
    delete list->NIL;
    delete list;
    list = nullptr;
}
 Node* find_key(List* list, int key){
    if(list == nullptr or list->HEAD == list->NIL) return list->NIL;
    for (Node *current = list->HEAD; current!=list->NIL; current=current->next){
      if(current->key == key) return current;
    }
    return list->NIL;
 } 

void remove_key(List* &list, int key){
  if(list == nullptr or list->HEAD == list->NIL) return;
  if(list->HEAD->key ==key){
    Node *tmp = list->HEAD;
    list->HEAD = list->HEAD->next;
    delete tmp;
    list->size--;
    return;
  }
  for (Node *current = list->HEAD; current!=list->TAIL; current=current->next){
      if(current->key == key){
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        list->size--;
        return;
      }
  }
  if(list->TAIL->key == key){
    Node* tmp = list->TAIL;
    list->TAIL = list->TAIL->prev;
    list->TAIL->next = list->NIL;
    list->NIL->prev= list->TAIL;
    delete tmp;
    list->size--;
    return;
  }
  
}
using namespace std;
int main() {
 List* list = create_empty_list();
  push_back(list, 0);
  push_back(list, 1);
  push_back(list, 2);
  remove_key(list, 2);
  print_list(list);
  return 0;
}
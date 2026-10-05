
#include <iostream>
struct Node{
    int key;
    Node *next;
};
void push_back(Node *&head, int value){
    if(head==nullptr){
        head = new Node();
        head->key = value;
        head->next =nullptr;
        return;
    }
    Node *current = head;
    while(current->next!=nullptr) current = current->next;
    Node *tail = new Node();
    tail->key = value;
    tail->next = nullptr;
    current->next = tail;
}

void insert_after(Node*& prev_ref, int new_key){
    Node *new_ref = new Node();
    new_ref->key = new_key;
    new_ref->next = prev_ref->next;
    prev_ref->next = new_ref;
}

void destroy_list(Node *&head){
    Node *current= head;
    Node *tmp = nullptr;
    while(current!=nullptr){
      tmp = current->next;
      delete current;
      current = tmp;
    }
    head = nullptr;
}

void print_list(Node *&head){
    if (head==nullptr) {
      std::cout<<std::endl;
      return;
    }
    Node *current = head;
    while(current->next!=nullptr){
       std::cout<<current->key<<' ';
       current=current->next;
    }
    std::cout<<current->key<<std::endl;
}

Node* find(Node *&head, int value){
  if(head==nullptr) return nullptr;
    for(Node *current = head; current!=nullptr; current = current->next){
      if(current->key == value) return current;
    }
    return nullptr;
}
void remove_key(Node*& head, int key){
    if(head==nullptr) return;
    if(head->key==key){
      head = nullptr;
      return;
    }
    Node *current = head;
    while(current->next!=nullptr){
      if(current->next->key==key){
        Node *tmp = current->next->next;
        delete current->next;
        current->next = tmp;
        delete tmp;
        return;
      }
      current=current->next;
    }
}
using std::cout;
using std::endl;

int main() {
  Node* HEAD = nullptr;
  push_back(HEAD, 0);
  push_back(HEAD, 1);
  push_back(HEAD, 2);
  remove_key(HEAD, 0);
  remove_key(HEAD, 1);
  remove_key(HEAD, 2);
  remove_key(HEAD, 3);
  if (HEAD == nullptr) {
    cout << "OK" << endl;
  }
  return 0;
}
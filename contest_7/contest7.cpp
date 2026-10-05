#include <iostream>
using namespace std;
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
      cout<<endl;
      return;
    }
    Node *current = head;
    while(current->next!=nullptr){
       cout<<current->key<<' ';
       current=current->next;
    }
    cout<<current->key<<endl;
}

Node *read_list(Node* head){
    int input = 1;
    while(input!=0){
        cin>>input;
        push_back(head, input);
    }
    return head;
}
Node *reverse(Node *head){
    if(head==nullptr) return nullptr;
    if(head->next==nullptr) return head;
    Node *current = head->next;
    head->next =nullptr;
    while(current->next!=nullptr){
        Node *tmp = current->next;
        current->next = head;
        head=current;
        current = tmp;
    }
    current->next = head;
    head = current;
    return head;
}
 
int main(){
  Node* head = nullptr;
  head = read_list(head);
  head = reverse(head);
  print_list(head);
  destroy_list(head);
  return 0;
}
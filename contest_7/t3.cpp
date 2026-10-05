#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
void print_list(Node *&head){
    if (head==nullptr) {
      cout<<endl;
      return;
    }
    Node *current = head;
    while(current->next!=nullptr){
       cout<<current->data<<' ';
       current=current->next;
    }
    cout<<current->data<<endl;
}
void push_back(Node *&head, int value){
    if(head==nullptr){
        head = new Node();
        head->data = value;
        head->next =nullptr;
        return;
    }
    Node *current = head;
    while(current->next!=nullptr) current = current->next;
    Node *tail = new Node();
    tail->data = value;
    tail->next = nullptr;
    current->next = tail;
}
Node *read_list(Node* head){
    int input;
    cin>>input;
    while(input!=0){
        push_back(head, input);
        cin>>input;
    }
    return head;
}
Node* mergeTwoLists(Node* list1, Node* list2){
    if(list1==nullptr) return list2;
    if(list2==nullptr) return list1;
    if(list1->data > list2->data){
        Node *head = list1;
        list1 = list2;
        list2 = head;
    }
    Node *current = list1;
    while(current->next!=nullptr){
        if(current->next->data <= list2->data) current = current->next;
        else{
            Node *tmp = current->next;
            current->next = list2;
            list2=tmp;
        }
    }
    if(list2!=nullptr) current->next = list2;
    return list1;
}

int main(){
    Node *list1=nullptr;
    Node *list2=nullptr;
    list1= read_list(list1);
    list2=read_list(list2);
    Node *list=mergeTwoLists(list1, list2);
    cout<<"done"<<endl;
    print_list(list);
    return 0;
}
#include <iostream>
using namespace std;

struct Node {
    char name;
    Node* next;
};
Node* create_Node(char name) {
    Node* new_node = new Node;
    new_node->name = name;
    new_node->next = nullptr;
    return new_node;
}
Node* create_Circle(int n, char names[]) {
    if (n <= 0) return nullptr;
    Node* head = create_Node(names[0]);
    Node* current = head;
    for (int i = 1; i < n; i++) {
        current->next = create_Node(names[i]);
        current = current->next;
    }
    current->next = head;
    return head;
}
int find_pop(Node* head, int k, char fix_name, int n) {
    Node* current = head;
    Node* prev = nullptr;
    int round = 0;
    int rem = n;
    while (rem > 0) {
        for (int i = 1; i < k; i++) {
            prev = current;
            current = current->next;
        }
        round++;
        if (current->name == fix_name) {
            Node* to_delete = current->next;
            while (to_delete != current) {
                Node* temp = to_delete;
                to_delete = to_delete->next;
                delete temp;
            }
            delete current;
            return round;
        } 
        prev->next = current->next;
        delete current;
        current = prev->next;
        rem--;
    }
    return -1;
}
int main() {
    int n, k;
    char target;
    cin >> n;
    char* names = new char[n];
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }
    cin >> k >> target;
    Node* head = create_Circle(n, names);
    cout << find_pop(head, k, target, n) << endl;
    delete[] names;
    return 0;
}
#include <iostream>
using namespace std;

struct Node{
    int field_int;
    double field_double;
};
struct EmptyNode {};

int main(){
    Node my_favourite_node = Node();
    cout<<sizeof(my_favourite_node)<<endl;
    cout<<sizeof(EmptyNode)<<endl;
    Node *node_array = new Node[12];
    node_array[0].field_int = 1;
    cout<<node_array->field_int<<endl; //выводит для 0-го эл-та
    delete[] node_array;
    return 0;
}
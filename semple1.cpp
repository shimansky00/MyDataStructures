#include <iostream>
#include "forward_list.h"

using std::cout, std::endl;

void print_list(const forward_list<int> &list);

int main() {
    forward_list<int> list;
    for (int i = 0; i < 20; i++) {
        list.push_back(i);
    }
    print_list(list);

    list.remove_last();
    print_list(list);
    
    list.remove_first();
    print_list(list);

    list.remove_at(10);
    print_list(list);

    list.push_back(30);
    print_list(list);

    return 0;
}

void print_list(const forward_list<int> &list) {
    for (int i = 0; i < list.getSize(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}

#include <iostream>
#include "linked_list.h"

using std::cout, std::endl;

int main()
{

    linked_list<int> *list = new linked_list<int>();
    for (int i = 0; i < 10; ++i) {
        list->push_back(i);
    }

    for (auto& i: *list) {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}

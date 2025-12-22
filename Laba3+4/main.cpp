#include "OneList.h"
#include "TwoList.h"

using namespace std;

int main() {
    OneList list, list1, list2, list3, emptyList; // -----------------------------------
    
    cout << "1. Testing append and operator[]:" << endl;
    list.append(42);
    list.append(3.14);
    list.append(string("Hi"));
    cout << "list[0] = " << list[0] << ", list[1] = " << list[1] << ", list[2] = " << list[2] << endl;

    cout << "\n2. Testing assignment operator:" << endl;
    list1 = { 1, 2.1, string("Hello") };
    cout << "list1[0] = " << list1[0] << ", list1[1] = " << list1[1] << ", list1[2] = " << list1[2] << endl;

    cout << "\n3. Testing empty() and size():" << endl;
    cout << "list.empty() = " << (list.empty() ? "true" : "false") << endl;
    cout << "list.size() = " << list.size() << endl;

    cout << "\n4. Testing front() and back():" << endl;
    cout << "list.front() = " << list.front() << endl;
    cout << "list.back() = " << list.back() << endl;

    cout << "\n5. Testing push_front() and push_back():" << endl;
    list.push_front(100);
    list.push_back(string("New End"));
    cout << "After push_front(100) and push_back('New End'):" << endl;
    cout << "list[0] = " << list[0] << ", list.back() = " << list.back() << endl;

    cout << "\n6. Testing insert():" << endl;
    list.insert(2, string("Inserted"));
    cout << "After insert(2, 'Inserted'): list[2] = " << list[2] << endl;

    cout << "\n7. Testing pop_front() and pop_back():" << endl;
    cout << "Before pop - front = " << list.front() << ", back = " << list.back() << endl;
    list.pop_front();
    list.pop_back();
    cout << "After pop - front = " << list.front() << ", back = " << list.back() << endl;

    cout << "\n8. Testing remove():" << endl;
    list2 = {1, 2, 3, 2, 4, 2};
    cout << "Before remove(2): ";
    for (int i = 0; i < list2.size(); i++) {
        cout << list2[i] << " ";
    }
    cout << endl;
    list2.remove(2);
    cout << "After remove(2): ";
    for (int i = 0; i < list2.size(); i++) {
        cout << list2[i] << " ";
    }
    cout << endl;

    cout << "\n9. Testing iterator functionality:" << endl;
    list.reset_iterator();
    cout << "Manual iteration: ";
    for (int i = 0; i < list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;

    cout << "\n10. Testing ++ and -- operators:" << endl;
    list3 = {1, 6, 3, 2, 4, 2};
    
    cout << "Initial current element: " << list3 << " (index: " << list3.get_current() << ")" << endl;
    
    OneList temp1 = list3++; // -----------------------------------
    cout << "After list3++: " << temp1 << " (list3 current index: " << list3.get_current() << ")" << endl;
    
    OneList temp2 = list3--; // -----------------------------------
    cout << "After list3--: " << temp2 << " (list3 current index: " << list3.get_current() << ")" << endl;
    
    cout << "After ++list3: " << (++list3) << " (index: " << list3.get_current() << ")" << endl;
    cout << "After --list3: " << (--list3) << " (index: " << list3.get_current() << ")" << endl;

    cout << "\n11. Testing with empty list:" << endl;
    cout << "emptyList.empty() = " << (emptyList.empty() ? "true" : "false") << endl;
    cout << "emptyList.size() = " << emptyList.size() << endl;

    cout << "\n12. Testing sorting: binary_insertion_sort(), shaker_sort():" << endl;
    list2 = { 1, 2, 3, 2, 4, 2 };
    list3 = { 1, 2, 3, 2, 4, 2 };
    cout << "Before sorting: ";
    for (int i = 0; i < list2.size(); i++) {
        cout << list2[i] << " ";
    }
    cout << endl;
    list2.binary_insertion_sort<int>(); // -----------------------------------
    list3.shaker_sort<int>(); // -----------------------------------
    cout << "After sorting 1) ";
    for (int i = 0; i < list2.size(); i++) {
        cout << list2[i] << " ";
    }
    cout << endl;
    cout << "After sorting 2) ";
    for (int i = 0; i < list3.size(); i++) {
        cout << list3[i] << " ";
    }
    cout << endl;
}
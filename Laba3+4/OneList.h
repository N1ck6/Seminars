#ifndef ONELIST_H
#define ONELIST_H

#include <any>
#include <initializer_list>
#include <typeinfo>
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct OneList {
    struct Element {
        any value;
        Element* next;
        Element(const any& val) : value(val), next(nullptr) {}
    };

    Element* head = nullptr;
    int list_size = 0;
    int current = 0;

    template<typename T>
    void addElem(const T& value) {
        Element* newElem = new Element(value);
        if (!head) {
            head = newElem;
        }
        else {
            Element* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newElem;
        }
        ++list_size;
    }

    Element* findElem(int index) {
        index = index < 0 ? list_size + index : index;
        if (index < 0 || index >= list_size)
            throw out_of_range("Index out of range");
        Element* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

    class Proxy {
        any& ref;
    public:
        Proxy(any& anyRef) : ref(anyRef) {}

        template<typename T>
        Proxy& operator=(const T& newValue) {
            ref = newValue;
            return *this;
        }

        friend ostream& operator<<(ostream& os, const Proxy& proxy) {
            if (proxy.ref.type() == typeid(int)) {
                os << any_cast<int>(proxy.ref);
            }
            else if (proxy.ref.type() == typeid(double)) {
                os << any_cast<double>(proxy.ref);
            }
            else if (proxy.ref.type() == typeid(string)) {
                os << any_cast<string>(proxy.ref);
            }
            else {
                os << "[unknown type]";
            }
            return os;
        }
    };

    ~OneList() {
        Element* current = head;
        while (current) {
            Element* next = current->next;
            delete current;
            current = next;
        }
    }

    OneList& operator=(initializer_list<any> values) {
        Element* current = head;
        while (current) {
            Element* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        list_size = 0;

        for (const auto& value : values) {
            addElem(value);
        }
        this->current = 0;
        return *this;
    }

    template<typename T>
    void append(const T& value) {
        addElem(value);
    }

    Proxy operator[](int index) {
        return Proxy(findElem(index)->value);
    }

    OneList& operator++() {
        if (current < list_size - 1) {
            current++;
        }
        return *this;
    }

    OneList operator++(int) {
        OneList temp = *this;
        ++(*this);
        return temp;
    }

    OneList& operator--() {
        if (current > 0) {
            current--;
        }
        return *this;
    }

    OneList operator--(int) {
        OneList temp = *this;
        --(*this);
        return temp;
    }

    Proxy operator()() {
        if (list_size == 0) throw out_of_range("List is empty");
        return Proxy(findElem(current)->value);
    }

    friend ostream& operator<<(ostream& os, OneList& list) {
        if (list.list_size == 0) {
            os << "[empty list]";
        }
        else {
            any& value = list.findElem(list.current)->value;
            if (value.type() == typeid(int)) {
                os << any_cast<int>(value);
            }
            else if (value.type() == typeid(double)) {
                os << any_cast<double>(value);
            }
            else if (value.type() == typeid(string)) {
                os << any_cast<string>(value);
            }
            else {
                os << "[unknown type]";
            }
        }
        return os;
    }

    bool empty() {
        return (head == nullptr);
    }

    int size() {
        return list_size;
    }

    Proxy front() {
        if (!head) throw out_of_range("List is empty");
        return Proxy(head->value);
    }

    Proxy back() {
        if (!head) throw out_of_range("List is empty");
        return Proxy(findElem(-1)->value);
    }

    void pop_front() {
        if (!head) return;
        Element* temp = head;
        head = head->next;
        delete temp;
        list_size--;
        if (current >= list_size) current = list_size - 1;
    }

    void pop_back() {
        if (!head) return;
        if (list_size == 1) {
            delete head;
            head = nullptr;
            list_size = 0;
            current = 0;
            return;
        }
        Element* temp = findElem(list_size - 2);
        delete temp->next;
        temp->next = nullptr;
        list_size--;
        if (current >= list_size) current = list_size - 1;
    }

    template<typename T>
    void remove(const T& value) {
        if (!head) return;

        while (head && any_cast<T>(&(head->value)) && any_cast<T>(head->value) == value) {
            Element* temp = head;
            head = head->next;
            delete temp;
            list_size--;
        }

        if (!head) {
            current = 0;
            return;
        }

        Element* current_elem = head;
        while (current_elem->next) {
            if (any_cast<T>(&(current_elem->next->value)) && any_cast<T>(current_elem->next->value) == value) {
                Element* temp = current_elem->next;
                current_elem->next = current_elem->next->next;
                delete temp;
                list_size--;
            }
            else {
                current_elem = current_elem->next;
            }
        }
        if (current >= list_size) current = list_size - 1;
    }

    template<typename T>
    void insert(int index, const T& value) {
        if (index == 0) {
            Element* inserted = new Element(value);
            inserted->next = head;
            head = inserted;
            list_size++;
            if (current >= index) current++;
            return;
        }

        Element* prev = findElem(index - 1);
        Element* inserted = new Element(value);
        inserted->next = prev->next;
        prev->next = inserted;
        list_size++;
        if (current >= index) current++;
    }

    template<typename T>
    void push_front(const T& value) {
        insert(0, value);
    }

    template<typename T>
    void push_back(const T& value) {
        addElem(value);
    }

    void reset_iterator() {
        current = 0;
    }

    int get_current() {
        return current;
    }

    template <typename T>
    void binary_insertion_sort() {
        int n = list_size;
        if (n <= 1) return;

        vector<T> arr;
        for (int i = 0;i < n;i++) {
            arr.push_back(any_cast<T>(findElem(i)->value));
        }

        int p = 0;
        for (int i = 1; i < n; i++) {
            T tmp = arr[i];
            int p1 = 0;
            int p2 = i;

            while (p1 < p2) {
                int mid = p1 + (p2 - p1) / 2;
                if (arr[mid] <= tmp) {
                    p1 = mid + 1;
                }
                else {
                    p2 = mid;
                }
            }
            for (int j = i; j > p1; j--) {
                arr[j] = arr[j - 1];
            }
            arr[p1] = tmp;
        }

        for (int i = 0;i < n;i++) {
            findElem(i)->value = arr[i];
        }
    }

    template <typename T>
    void shaker_sort() {
        int n = size();
        if (n <= 1) return;

        vector<T> arr;
        for (int i = 0;i < n;i++) {
            arr.push_back(any_cast<T>(findElem(i)->value));
        }

        int p1 = 0;
        int p2 = n - 1;
        bool f = true;
        while (p1 < p2&& f) {
            f = false;
            for (int j = p1; j < p2; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    f = true;
                }
            }
            p2--;
            for (int j = p2; j > p1; j--) {
                if (arr[j] < arr[j - 1]) {
                    swap(arr[j], arr[j - 1]);
                    f = true;
                }
            }
            p1++;
        }

        for (int i = 0;i < n;i++) {
            findElem(i)->value = arr[i];
        }
    }
};

#endif
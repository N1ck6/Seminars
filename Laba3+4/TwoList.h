#ifndef TWOLIST_H
#define TWOLIST_H

#include "OneList.h"
#include <any>
#include <initializer_list>
#include <typeinfo>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

struct TwoList : public OneList {
    struct Element {
        any value;
        Element* next;
        Element* prev;
        Element(const any& val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Element* head = nullptr;
    Element* tail = nullptr;
    int list_size = 0;
    int current = 0;

    template<typename T>
    void addElem(const T& value) {
        Element* newElem = new Element(value);
        if (!head) {
            head = tail = newElem;
            newElem->prev = nullptr;
        }
        else {
            tail->next = newElem;
            newElem->prev = tail;
            tail = newElem;
        }
        ++list_size;
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

    Proxy operator[](int index) {
        return Proxy(findElem(index)->value);
    }

    Proxy operator()() {
        if (list_size == 0) throw out_of_range("List is empty");
        return Proxy(findElem(current)->value);
    }

    Element* findElem(int index) {
        index = index < 0 ? list_size + index : index;
        if (index < 0 || index >= list_size)
            throw out_of_range("Index out of range");

        Element* current;
        if (index < list_size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        }
        else {
            current = tail;
            for (int i = list_size - 1; i > index; i--) {
                current = current->prev;
            }
        }
        return current;
    }

    ~TwoList() {
        Element* current = head;
        while (current) {
            Element* next = current->next;
            delete current;
            current = next;
        }
    }

    TwoList& operator=(initializer_list<any> values) {
        Element* current = head;
        while (current) {
            Element* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        list_size = 0;
        this->current = 0;

        for (const auto& value : values) {
            addElem(value);
        }
        return *this;
    }

    TwoList& operator++() {
        if (current < list_size - 1) {
            current++;
        }
        return *this;
    }

    TwoList operator++(int) {
        TwoList temp = *this;
        ++(*this);
        return temp;
    }

    TwoList& operator--() {
        if (current > 0) {
            current--;
        }
        return *this;
    }

    TwoList operator--(int) {
        TwoList temp = *this;
        --(*this);
        return temp;
    }

    template<typename T>
    void append(const T& value) {
        addElem(value);
    }

    template<typename T>
    void push_front(const T& value) {
        Element* newElem = new Element(value);
        if (!head) {
            head = tail = newElem;
        }
        else {
            newElem->next = head;
            head->prev = newElem;
            head = newElem;
        }
        list_size++;
        if (current >= 0) current++;
    }

    template<typename T>
    void push_back(const T& value) {
        addElem(value);
    }

    void pop_front() {
        if (!head) return;
        Element* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        list_size--;
        if (current >= list_size) current = list_size - 1;
        if (current < 0) current = 0;
    }

    void pop_back() {
        if (!tail) return;
        Element* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        list_size--;
        if (current >= list_size) current = list_size - 1;
    }

    template<typename T>
    void insert(int index, const T& value) {
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == list_size) {
            push_back(value);
            return;
        }

        Element* current_elem = findElem(index);
        Element* newElem = new Element(value);

        newElem->prev = current_elem->prev;
        newElem->next = current_elem;
        current_elem->prev->next = newElem;
        current_elem->prev = newElem;

        list_size++;
        if (this->current >= index) this->current++;
    }

    template<typename T>
    void remove(const T& value) {
        Element* current_elem = head;
        while (current_elem) {
            if (any_cast<T>(&(current_elem->value)) && any_cast<T>(current_elem->value) == value) {
                if (current_elem == head) {
                    pop_front();
                    current_elem = head;
                }
                else if (current_elem == tail) {
                    pop_back();
                    current_elem = nullptr;
                }
                else {
                    Element* temp = current_elem;
                    current_elem->prev->next = current_elem->next;
                    current_elem->next->prev = current_elem->prev;
                    current_elem = current_elem->next;
                    delete temp;
                    list_size--;
                }
            }
            else {
                current_elem = current_elem->next;
            }
        }
        if (current >= list_size) current = list_size - 1;
    }

    Proxy front() {
        if (!head) throw out_of_range("List is empty");
        return Proxy(head->value);
    }

    Proxy back() {
        if (!tail) throw out_of_range("List is empty");
        return Proxy(tail->value);
    }
};

#endif
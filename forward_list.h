#ifndef FORWARD_LIST_H

#define FORWARD_LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct node
{
    T data;
    node<T> *next;
    node(T const &i): data(i), next(nullptr) {};
};

template <typename T>
class forward_list
{
    node<T> *head;
    int size;

    node<T>* find_last() {
        if (this->head == nullptr) {
            throw std::out_of_range("This list is empty");
        }

        node<T> *current = this->head;
        while (current->next != nullptr) {
            current = current->next;
        }

        return current;
    }
        
public:
    forward_list();
    ~forward_list();

    T& operator[](const int index) const {
        if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of array bounds");
        }

        node<T> *current = this->head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void push_back(const T &val) {
        node<T> *newItem = new node<T>(val);

        if (this->head == nullptr) {
            this->head = newItem;
            this->size++;
            return;
        }

        node<T> *last = this->find_last();
        last->next = newItem;
        this->size++;
    }

    void remove_last() {
        if (this->head == nullptr) {
            throw std::out_of_range("This list is empty");
        }

        node<T> *last = this->head;
        node<T> *prev = nullptr;

        while (last->next != nullptr) {
            prev = last;
            last = last->next;
        }

        prev->next = nullptr;
        delete last;
        this->size--;
    }

    void remove_first() {
        if (this->head == nullptr) {
            throw std::out_of_range("This list is empty");
        }

        node<T> *first = this->head;
        this->head = this->head->next;
        delete first;
        this->size--;
    }

    void remove_at(int index) {
        if (index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of array bounds");
        }

        node<T> *item = this->head;
        node<T> *prev = nullptr;

        if (index == 0) {
            this->head = item->next;
            delete item;
        } else {
            for (int i = 0; i < index; i++) {
                prev = item;
                item = item->next;
            }
            prev->next = item->next;
            delete item;
        }
        this->size--;
    }

    int getSize() const {
        return this->size;
    }
};

template <typename T>
forward_list<T>::forward_list()
{
    this->head = nullptr;
    this->size = 0;
}

template <typename T>
forward_list<T>::~forward_list()
{
    node<T> *current = this->head;
    node<T> *next = nullptr;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

#endif

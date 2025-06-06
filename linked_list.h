#ifndef LIST_H

#define LIST_H

#include <cstddef>
// #include <stdexcept>

using std::size_t;

template<typename T>
struct node
{
    node *prev, *next;
    T data;
    node (const T &data): prev(0), next(0), data(data);
};

template<typename T>
class linked_list {
    node<T> *head;
    node<T> *tail;
    size_t size;

public:

    linked_list();
    ~linked_list();

    void push_front(const T &val);
    void push_back(const T &val);
    T pop_front();
    T pop_back();

    T front();
    T back();
    void insert(const T &val, size_t index);
    void unique();
    void merge();
    void remove_if();

    template <typename NodeType>
    class ListIterator {
        NodeType* current;
        friend class LinkedList<T>; 
        ListIterator(NodeType* ptr) : m_ptr(ptr) {}

     public:
        T& operator*();
        const T& operator*() const;
        T* operator->()
        ListIterator operator++();
        ListIterator& operator++(int);
        ListIterator operator--();
        ListIterator& operator--(int);
        bool operator==(const ListIterator& other) const;
        bool operator!=(const ListIterator& other) const;
    }

    using iterator = ListIterator<Node>;
    using const_iterator = ListIterator<const Node>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    T& operator[](const int index) const;
};

template<typename T>
linked_list<T>::linked_list(): head(0), tail(0), size(0) {}

template<typename T>
linked_list<T>::~linked_list() {
    
}

template<typename T>
void linked_list<T>::push_front(const T &val)
{
    if(this->head == 0) {
        this->head = new node<T>(val);
        this->tail = this->head;
        this->size++;
        return;
    }

    node<T> *newItem = new node<T>(val);
    newItem->next = this->head;
    this->head->prev = newItem;
    this->head = newItem;
    this->size++;
}

template<typename T>
void linked_list<T>::push_back(const T &val)
{
    if (this->head == 0) {
        this->head = new node<T>(val);
        this->tail->prev = this->head;
        this->size++;
        return;
    }

    node<T> *newItem = new node<T>(val);
    newItem->prev = this->tail;
    this->tail = newItem;
    this->size++;
}

template<typename T>
T linked_list<T>::pop_front() {
    if(this->head == 0) {
        throw std::out_of_range("This list is empty");
    }

    node<T> *item = this->head;
    T data = item->data;
    this->head = this->head->next;
    this->head->prev = 0;
    delete item;
    this->size--;
    return item->data;
}

template<typename T>
T linked_list<T>::pop_back() {
    if(this->head == 0) {
        throw std::out_of_range("This list is empty");
    }

    if (this->head == this->tail) {
        node<T> *item = this->head;
        T val = item->data;
        this->head = 0;
        this->tail = 0;
        delete item;
        this->size--;
        return val;
    }

    node<T> *item = this->tail;
    T val = item->data;
    this->tail = this->tail->prev;
    this->tail->next = 0;
    delete item;
    this->size--;
    return val;
}


#endif

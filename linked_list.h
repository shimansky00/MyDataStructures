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
    node (const T &data): prev(0), next(0), data(data) {}
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

    void insert(const T &val, size_t index);
    void unique();
    // void merge(linked_list& other); // todo
    // void remove_if(Predicate p); // todo

    template <typename NODE>
    class linked_list_iterator {
        NODE* current;
        friend class linked_list<T>; 
        linked_list_iterator(NODE* node) : current(node) {}

     public:
        T& operator*();
        const T& operator*() const;
        T* operator->();
        linked_list_iterator& operator++();
        linked_list_iterator operator++(int);
        linked_list_iterator& operator--();
        linked_list_iterator operator--(int);
        bool operator==(const linked_list_iterator& other) const;
        bool operator!=(const linked_list_iterator& other) const;
    };

    using iterator = linked_list_iterator<node<T>>;
    using const_iterator = linked_list_iterator<const node<T>>;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // T& operator[](const int index) const;
};

template<typename T>
linked_list<T>::linked_list(): head(0), tail(0), size(0) {}

template<typename T>
linked_list<T>::~linked_list()
{
    node<T> *current = this->head;
    node<T> *next = 0;
    for (size_t i = 0; i < this->size; i++) {
        next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
void linked_list<T>::push_front(const T &val)
{
    node<T> *newItem = new node<T>(val);

    if (this->head == 0) {
        this->head = newItem;
        this->tail = newItem;
    } else {
        newItem->next = this->head;
        this->head->prev = newItem;
        this->head = newItem;
    }

    this->size++;
}

template<typename T>
void linked_list<T>::push_back(const T &val)
{
    node<T> *newItem = new node<T>(val);

    if (this->head == 0) {
        this->head = newItem;
        this->tail = newItem;
    } else {
        this->tail->next = newItem;
        newItem->prev = this->tail;
        this->tail = newItem;
    }

    this->size++;
}

template<typename T>
T linked_list<T>::pop_front() {
    if (this->head == 0) {
        throw std::out_of_range("Cannot pop from an empty list");
    }
    
    node<T> *item = this->head;
    T data = item->data;
    this->head = this->head->next;
    this->size--;

    if (this->head != nullptr) {
        this->head->prev = 0;
    } else {
        this->tail = 0;
    }

    delete item;
    return data;
}

template<typename T>
T linked_list<T>::pop_back() {
    if (this->head == 0) {
        throw std::out_of_range("Cannot pop from an empty list");
    }
    
    node<T> *item = this->tail;
    T data = item->data;
    this->tail = tail->prev;
    this->size--;

    if (this->tail != 0) {
        this->tail->next = 0;
    } else {
        this->head = 0;
    }

    delete item;
    return data;
}

template<typename T>
void linked_list<T>::insert(const T &val, size_t index)
{
    if (index > this->size) {
        throw std::out_of_range("Index is out of range");
    }

    if (index == 0) {
        this->push_front(val);
        return;
    }

    if (index == this->size) {
        this->push_back(val);
        return;
    }

    node<T> *current = this->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    node<T> *newItem = new node<T>(val);
    newItem->prev = current->prev;
    newItem->next = current;
    current->prev = newItem;
    newItem->prev->next = newItem;

    this->size++;
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::begin()
{
    return iterator(this->head);
}

template<typename T>
typename linked_list<T>::iterator linked_list<T>::end()
{
    return iterator(0);
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::begin() const
{
    return const_iterator(this->head);
}

template<typename T>
typename linked_list<T>::const_iterator linked_list<T>::end() const
{
    return const_iterator(0);
}

template<typename T>
template<typename NODE>
T& linked_list<T>::linked_list_iterator<NODE>::operator*()
{
    return this->current->data;
}

template<typename T>
template<typename NODE>
const T& linked_list<T>::linked_list_iterator<NODE>::operator*() const
{
    return this->current->data;
}

template<typename T>
template<typename NODE>
T* linked_list<T>::linked_list_iterator<NODE>::operator->()
{
    return &(this->current->data);
}

template<typename T>
template<typename NODE>
typename linked_list<T>::linked_list_iterator<NODE>&
linked_list<T>::linked_list_iterator<NODE>::operator++()
{
    current = current->next;
    return *this;
}

template<typename T>
template<typename NODE>
typename linked_list<T>::linked_list_iterator<NODE>
linked_list<T>::linked_list_iterator<NODE>::operator++(int)
{
    linked_list_iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
template<typename NODE>
typename linked_list<T>::linked_list_iterator<NODE>&
linked_list<T>::linked_list_iterator<NODE>::operator--()
{
    if(current->prev == 0) {
        throw std::out_of_range("Index is out of range");
    }

    if (current == 0) {
        throw std::logic_error("Cannot decrement end iterator"); // todo
    }

    current = current->prev;
    return *this;
}

template<typename T>
template<typename NODE>
typename linked_list<T>::linked_list_iterator<NODE>
linked_list<T>::linked_list_iterator<NODE>::operator--(int)
{
    if(current->prev == 0) {
        throw std::out_of_range("Index is out of range");
    }
    linked_list_iterator temp = *this;
    --(*this);
    return temp;
}

template<typename T>
template<typename NODE>
bool linked_list<T>::linked_list_iterator<NODE>
::operator==(const linked_list_iterator& other) const
{
    return this->current == other.current;
}

template<typename T>
template<typename NODE>
bool linked_list<T>::linked_list_iterator<NODE>
::operator!=(const linked_list_iterator& other) const
{
    return !(*this == other);
}

#endif

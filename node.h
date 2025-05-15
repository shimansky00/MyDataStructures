#ifndef NODE_H

#define NODE_H

template <typename T>
struct node
{
    T data;
    node<T> *next;
    node(T const &i): data(i), next(nullptr) {};
};

#endif

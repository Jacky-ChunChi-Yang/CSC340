#ifndef NODE
#define NODE

template <typename T>
class Node {
    private:
        T* data;
        Node* prev;
        Node* next;
    public:
        Node(T data);
        T* getData() const;
        void setData(T* newData);
        Node* getPrev() const;
        void setPrev(Node<T>* newPrev);
        Node* getNext() const;
        void setNext(Node<T>* newNext);
};

template <typename T>
bool operator==(Node<T> lhs, Node<T> rhs);
template <typename T>
bool operator!=(Node<T> lhs, Node<T> rhs);
template <typename T>
bool operator<(Node<T> lhs, Node<T> rhs);
template <typename T>
bool operator>(Node<T> lhs, Node<T> rhs);
template <typename T>
bool operator<=(Node<T> lhs, Node<T> rhs);
template <typename T>
bool operator>=(Node<T> lhs, Node<T> rhs);

template <typename T>
bool operator==(Node<T> lhs, Node<T> rhs);
template <typename T>
bool operator!=(Node<T> lhs, T rhs);
template <typename T>
bool operator<(Node<T> lhs, T rhs);
template <typename T>
bool operator>(Node<T> lhs, T rhs);
template <typename T>
bool operator<=(Node<T> lhs, T rhs);
template <typename T>
bool operator>=(Node<T> lhs, T rhs);

template <typename T>
bool operator!=(T lhs, Node<T> rhs);
template <typename T>
bool operator==(T lhs, Node<T> rhs);
template <typename T>
bool operator<(T lhs, Node<T> rhs);
template <typename T>
bool operator>(T lhs, Node<T> rhs);
template <typename T>
bool operator<=(T lhs, Node<T> rhs);
template <typename T>
bool operator>=(T lhs, Node<T> rhs);

#include "node.hpp"

#endif
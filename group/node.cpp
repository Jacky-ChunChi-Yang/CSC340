#include "node.h"

using namespace std;

template <typename T>
Node<T>::Node(const T &data) {
    this->setData(data);
}

template <typename T>
T Node<T>::getData() const {
    return this->data;
}

template <typename T>
Node<T>* Node<T>::getPrev() const {
    return this->prev;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
    return this->next;
}

template <typename T>
void Node<T>::setData(const T &newData) {
    this->data = newData;
}

template <typename T>
void Node<T>::setPrev(Node<T>* newPrev) {
    this->prev = newPrev;
}

template <typename T>
void Node<T>::setNext(Node<T>* newNext) {
    this->next = newNext;
}

template <typename T>
bool operator==(Node<T> lhs, Node<T> rhs) {
    return lhs.getData()==rhs.getData();
}
template <typename T>
bool operator!=(Node<T> lhs, Node<T> rhs) {
    return !(lhs==rhs);
}
template <typename T>
bool operator<(Node<T> lhs, Node<T> rhs) {
    return lhs.getData()<rhs.getData();
}
template <typename T>
bool operator>(Node<T> lhs, Node<T> rhs) {
    return rhs<lhs;
}
template <typename T>
bool operator<=(Node<T> lhs, Node<T> rhs){
    return !(rhs<lhs);
}
template <typename T>
bool operator>=(Node<T> lhs, Node<T> rhs) {
    return !(lhs<rhs);
}

template <typename T>
bool operator==(Node<T> lhs, T rhs) {
    return lhs.getData()==rhs;
}
template <typename T>
bool operator!=(Node<T> lhs, T rhs) {
    return !(lhs==rhs);
}
template <typename T>
bool operator<(Node<T> lhs, T rhs) {
    return lhs.getData()<rhs;
}
template <typename T>
bool operator>(Node<T> lhs, T rhs) {
    return lhs.getData()>rhs;
}
template <typename T>
bool operator<=(Node<T> lhs, T rhs) {
    return !(rhs<lhs);
}
template <typename T>
bool operator>=(Node<T> lhs, T rhs) {
    return !(lhs<rhs);
}

template <typename T>
bool operator==(T lhs, Node<T> rhs) {
    return rhs==lhs;
}
template <typename T>
bool operator!=(T lhs, Node<T> rhs) {
    return !(rhs==lhs);
}
template <typename T>
bool operator<(T lhs, Node<T> rhs) {
    return rhs>lhs;
}
template <typename T>
bool operator>(T lhs, Node<T> rhs) {
    return rhs<lhs;
}
template <typename T>
bool operator<=(T lhs, Node<T> rhs) {
    return !(rhs<lhs);
}
template <typename T>
bool operator>=(T lhs, Node<T> rhs) {
    return !(lhs<rhs);
}
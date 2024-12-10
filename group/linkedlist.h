#ifndef LINKEDLIST
#define LINKEDLIST

#include "node.h"

template <typename T> class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    public:
        LinkedList();
        ~LinkedList();
        Node<T>* getHead() const;
        Node<T>* getTail() const;
        int getSize() const;
        void setHead(Node<T>* newHead);
        void setTail(Node<T>* newTail);
        void setSize(const int &newSize);
        void push_back(const T& data);
        void push_back(Node<T>* newNode);
        void operator+=(LinkedList<T> &rhs);
        Node<T>* insert_before(T newData, Node<T>* knownNode);
        void insert_before(Node<T>* newPrev, Node<T>* baseNode);
        void merge(LinkedList<T>* listB);
        void mergeSort();
        void mergeSort(LinkedList<T>* topListPtr);
};

#include "linkedlist.hpp"

#endif
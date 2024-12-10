#include "linkedlist.h"

using namespace std;

template <typename T>
LinkedList<T>::LinkedList() {
    this->setHead(nullptr);
    this->setTail(nullptr);
    this->setSize(0);
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = this->getHead();
    if (current) {
       while (current->getNext()) {
           current = current->getNext();
           delete current->getPrev();
       }
       delete current;
    }
}

template <typename T>
Node<T>* LinkedList<T>::getHead() const {
    return this->head;
}

template <typename T>
Node<T>* LinkedList<T>::getTail() const {
    return this->tail;
}

template <typename T>
int LinkedList<T>::getSize() const {
    return this->size;
}

template <typename T>
void LinkedList<T>::setHead(Node<T>* newHead) {
    this->head = newHead;
}

template <typename T>
void LinkedList<T>::setTail(Node<T>* newTail) {
    this->tail = newTail;
}

template <typename T>
void LinkedList<T>::setSize(const int &newSize) {
    this->size = newSize;
}

template <typename T>
void LinkedList<T>::push_back(const T& data) {
    if (this->getSize() > 0) {
        this->getTail()->setNext(new Node<T>(data));
        this->getTail()->getNext()->setPrev(getTail());
        this->setTail(this->getTail()->getNext());
        this->setSize(this->getSize() + 1);
    }
    else {
        this->setHead(new Node<T>(data));
        this->setTail(this->getHead());
        this->setSize(1);
    }
}

template <typename T>
void LinkedList<T>::push_back(Node<T>* newNode) {
    if (this->getSize() > 0) {
        this->getTail()->setNext(newNode);
        newNode->setPrev(this->getTail());
        this->setTail(newNode);
        this->setSize(this->getSize() + 1);
    }
    else {
        this->setHead(newNode);
        this->setTail(newNode);
        this->setSize(1);
    }
}

template <typename T>
void LinkedList<T>::operator+=(LinkedList<T> &rhs) {
    this->getTail()->setNext(rhs.getHead());
    rhs.getHead()->setPrev(this->getTail());
    this->setTail(rhs.getTail());
    this->setSize(this->getSize() + rhs.getSize());
    rhs.setTail(nullptr);
    rhs.setHead(nullptr);
    rhs.setSize(0);
}

template <typename T>
Node<T>* LinkedList<T>::insert_before(T newData, Node<T>* knownNode) {
    if (!knownNode) {
        this->push_back(newData);
        return this->getTail();
    }
    else {
        Node<T>* newNode = new Node<T>(newData);

        if (knownNode->getPrev()) {
            newNode->setPrev(knownNode->getPrev());
            newNode->getPrev()->setNext(newNode);
        }
        else {
            this->setHead(newNode);
        }
        newNode->setNext(knownNode);
        knownNode->setPrev(newNode);

        this->setSize(this->getSize() + 1);
        return newNode;
    }
}

template <typename T>
void LinkedList<T>::insert_before(Node<T>* newPrev, Node<T>* baseNode) {
    if (baseNode->getPrev()) {
        newPrev->setPrev(baseNode->getPrev());
        newPrev->getPrev()->setNext(newPrev);
    }
    else {
        this->setHead(newPrev);
    }
    newPrev->setNext(baseNode);
    baseNode->setPrev(newPrev);

    this->setSize(this->getSize() + 1);
}

template <typename T>
void LinkedList<T>::merge(LinkedList<T>* listB) {
    Node<T>* movePtr = this->getHead();
    Node<T>* tempPtr;

    //ptr moves through *this and move front element of listB to before the ptr if appropriate
    while (movePtr && listB->getHead()) {
        if (*movePtr == *listB->getHead()) {
            tempPtr = listB->getHead()->getNext();
            delete listB->getHead();
            listB->setHead(tempPtr);
            listB->setSize(listB->getSize() - 1);
        }
        else if (*movePtr < *listB->getHead()) {
            movePtr = movePtr->getNext();
        }
        else if (*movePtr > *listB->getHead()) {
            tempPtr = listB->getHead()->getNext();
            this->insert_before(listB->getHead(), movePtr);
            listB->setHead(tempPtr);
            listB->setSize(listB->getSize() - 1);
        }
    }

    //add remaining listB to end if movePtr reaches end
    if (listB->getHead()) {
            *this+=*listB;
    }

    listB->setSize(0);
}

template <typename T>
void LinkedList<T>::mergeSort() {
    mergeSort(this);
}

//can likely remove fList and just alter *this
template <typename T>
void LinkedList<T>::mergeSort(LinkedList<T>* topListPtr) {
    LinkedList<T>* fList = new LinkedList();
    LinkedList<T>* bList = new LinkedList();
    Node<T>* movPtr = topListPtr->getHead();
    int halfSize = this->getSize()/2;

    if (halfSize == 0) {
        return;
    }

    //move to start of 2nd half; 2nd half bigger if odd
    for (int i = 0; i < halfSize; i++) {
        movPtr = movPtr->getNext();
    }

    fList->setHead(topListPtr->getHead());
    fList->setTail(movPtr->getPrev());
    fList->setSize(halfSize);

    bList->setHead(movPtr);
    bList->setTail(topListPtr->getTail());
    bList->setSize(halfSize);
    if (topListPtr->getSize() % 2 == 1) {
        bList->setSize(bList->getSize() + 1);
    }

    fList->getTail()->setNext(nullptr);
    bList->getHead()->setPrev(nullptr);

    fList->mergeSort();
    bList->mergeSort();

    fList->merge(bList);

    this->setHead(fList->getHead());
    this->setTail(fList->getTail());
}
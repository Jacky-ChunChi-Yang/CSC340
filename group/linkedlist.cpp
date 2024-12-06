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
           delete current->getPrevious();
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
void LinkedList<T>::setTail(Node<T>* newHead) {
    this->tail = newTail;
}

template <typename T>
void LinkedList<T>::setSize(const int &newSize) {
    this->size = newSize;
}

template <typename T>
void LinkedList<T>::push_back(Node<T>* newNode) {
    if (this->getSize() > 0) {
        this->getTail()->setNext(newNode);
        newNode->setPrevious(this->getTail());
        this->setTail(newNode);
        this->setSize(this->getSize++);
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
    rhs.getHead()->setPrevious(this->getTail());
    this->setTail(rhs.getTail());
    this->setCount(this->getSize()+rhs.getSize());
    rhs.setTail(nullptr);
    rhs.setHead(nullptr);
    rhs.setCount(0);
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
            listB->setSize(listB->getSize--);
        }
        else if (*movePtr < *listB->getHead()) {
            movePtr = movePtr->getNext();
        }
        else if (*movePtr > *listB->getHead()) {
            tempPtr = listB->getHead()->getNext();
            this->insert_before(listB->getHead(), movePtr);
            listB->setHead(tempPtr);
            listB->setSize(listB->getSize--);
        }
    }

    //add remaining listB to end if movePtr reaches end
    if (listB->getHead()) {
            *this+=*listB;
    }

    listB->setCount(0);
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
    int halfSize = this->size()/2;

    if (halfSize == 0) {
        return;
    }

    //move to start of 2nd half; 2nd half bigger if odd
    for (int i = 0; i < halfSize; i++) {
        movPtr = movPtr->getNext();
    }

    fList->setHead(topListPtr->getHead());
    fList->setTail(movPtr->getPrevious());
    fList->setCount(halfSize);

    bList->setHead(movPtr);
    bList->setTail(topListPtr->getTail());
    bList->setCount(halfSize);
    if (topListPtr->size() % 2 == 1) {
        bList->incCount();
    }

    fList->getTail()->setNext(nullptr);
    bList->getHead()->setPrevious(nullptr);

    fList->mergeSort();
    bList->mergeSort();

    fList->mergeDicts(bList);

    this->setHead(fList->getHead());
    this->setTail(fList->getTail());
}
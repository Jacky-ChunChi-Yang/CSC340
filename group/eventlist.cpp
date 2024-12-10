#include "eventlist.h"

using namespace std;

EventList::EventList(const string &name) {
    LinkedList();
    this->setName(name);
}

string EventList::getName() const {
    return this->name;
}

void EventList::setName(const string &newName) {
    this->name = newName;
}

void EventList::displayEvents() {
    Node<Event>* movPtr = this->getHead();
    while (movPtr) {
        movPtr->getData().printEvent();
        movPtr->setNext(movPtr->getNext());
    }
}

Node<Event>* EventList::findEvent(const string &name) {
    Node<Event>* movPtr = this->getHead();
    while (movPtr) {
        if (movPtr->getData().getName() == name) {
            return movPtr;
        }
        movPtr = movPtr->getNext();
    }
    return nullptr;
}

void EventList::deleteEvent(const string &eventName) {
    Node<Event>* event = this->findEvent(eventName);
    if (event == nullptr) {
        cout << "Event not found" << endl;
    }
    else if (event == this->getHead()) {
        this->setHead(this->getHead()->getNext());
        delete event;
        this->getHead()->setPrev(nullptr);
        this->setSize(this->getSize() + 1);
    }
    else if (event == this->getTail()) {
        this->setTail(this->getTail()->getPrev());
        delete event;
        this->getTail()->setNext(nullptr);
        this->setSize(this->getSize() + 1);
    }
    else {
        event->getPrev()->setNext(event->getNext());
        event->getNext()->setPrev(event->getPrev());
        delete event;
        this->setSize(this->getSize() + 1);
    }

}
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
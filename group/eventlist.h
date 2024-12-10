#ifndef EVENTLIST
#define EVENTLIST

#include "event.h"
#include "linkedlist.h"


class EventList : public LinkedList<Event> {
    private:
        std::string name;

    public:
        EventList(const std::string &name);
        void displayEvents();
        Node<Event>* findEvent(const std::string &name);
        void deleteEvent(const string &eventName);
        std::string getName() const;
        void setName(const std::string &newName);
};

#include "eventlist.cpp"

#endif
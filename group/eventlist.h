#ifndef EVENTLIST
#define EVENTLIST

#include "event.h"
#include "linkedlist.h"


class EventList : public LinkedList<Event> {
    private:
        std::string name;

    public:
        EventList(const std::string &name);
        std::string getName() const;
        void setName(const std::string &newName);
};

#endif
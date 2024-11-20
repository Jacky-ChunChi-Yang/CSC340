#ifndef CALENDAR_H
#define CALENDAR_H

#include "Event.h"

// Node class for linked list
class Node {
public:
    std::shared_ptr<Event> event;
    Node* next;
    Node(std::shared_ptr<Event> ev);
    // ~Node();
};

// Calendar class
class Calendar {
    Node* head;
public:
    Calendar();
    void addEvent(std::shared_ptr<Event> event);
    void searchEvent(const std::string& date) const;
    void displayAll() const;
    ~Calendar();
};

#endif 

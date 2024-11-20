#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <memory>


// Abstract class for Event
class Event {
protected:
    std::string name;
    std::string date; // YYYY-MM-DD
public:
    Event(std::string n, std::string d);
    virtual ~Event();
    virtual void display() const = 0;
    std::string getDate() const;
    virtual int compareTo(const Event& other) const;
};

// Derived class for a Meeting Event
class MeetingEvent : public Event {
    std::string organizer;
public:
    MeetingEvent(std::string n, std::string d, std::string o);
    void display() const override;
};

// Derived class for a Personal Event
class PersonalEvent : public Event {
    std::string location;
public:
    PersonalEvent(std::string n, std::string d, std::string loc);
    void display() const override;
};

#endif 

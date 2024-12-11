#ifndef EVENT
#define EVENT

#include <string>
#include <ctime>
#include <iostream>

class Event {
    private:
        std::string eventName;
        struct tm datetime;
    public:
        Event();
        Event(std::string eventName, struct tm datetime);
        virtual void printEvent() const {};

        std::string getName() const;
        struct tm getDateTime() const;
        void setName(const std::string &newName);
        void setDateTime(const struct tm &newDateTime);
};

class PersonalEvent : public Event {
    private:
        std::string location;
    public:
        PersonalEvent();
        PersonalEvent(std::string eventName, struct tm datetime, std::string location);
        void printEvent() const override;
        std::string getLocation() const;
        void setLocation(const std::string &newLocation);
};

class MeetingEvent : public Event {
    private:
        std::string attendee;
    public:
        MeetingEvent();
        MeetingEvent(std::string eventName, struct tm datetime, std::string attendee);
        void printEvent() const override;
        std::string getAttendee() const;
        void setAttendee(const std::string &newAttendee);
};

bool operator==(Event lhs, Event rhs);
bool operator!=(Event lhs, Event rhs);
bool operator<(Event lhs, Event rhs);
bool operator>(Event lhs, Event rhs);
bool operator<=(Event lhs, Event rhs);
bool operator>=(Event lhs, Event rhs);

bool operator==(Event lhs, struct tm rhs);
bool operator!=(Event lhs, struct tm rhs);
bool operator<(Event lhs, struct tm rhs);
bool operator>(Event lhs, struct tm rhs);
bool operator<=(Event lhs, struct tm rhs);
bool operator>=(Event lhs, struct tm rhs);

bool operator!=(struct tm lhs, Event rhs);
bool operator==(struct tm lhs, Event rhs);
bool operator<(struct tm lhs, Event rhs);
bool operator>(struct tm lhs, Event rhs);
bool operator<=(struct tm lhs, Event rhs);
bool operator>=(struct tm lhs, Event rhs);

#include "event.cpp"

#endif
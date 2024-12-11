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
        Event(const Event &oldEvent);
        Event(std::string eventName, struct tm datetime);
        virtual void printEvent() const;

        std::string getName() const;
        struct tm getDateTime() const;
        void setName(const std::string &newName);
        void setDateTime(const struct tm &newDateTime);
};

class PersonalEvent : public Event {
    private:
        std::string location;
    public:
        PersonalEvent(std::string eventName, struct tm datetime, std::string location);
        PersonalEvent(const PersonalEvent &oldPersonal);
        void printEvent() const override;
        std::string getLocation() const;
        void setLocation(const std::string &newLocation);
};

class MeetingEvent : public Event {
    private:
        std::string attendee;
    public:
        MeetingEvent(std::string eventName, struct tm datetime, std::string attendee);
        MeetingEvent(const MeetingEvent &oldMeeting);
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
#include "event.h"

using namespace std;

Event::Event() {
    this->setName("errorEvent");
    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);
    this->setDateTime(datetime);
}

Event::Event(string eventName, struct tm datetime) {
    this->setName(eventName);
    this->setDateTime(datetime);
}

string Event::getName() const {
    return this->eventName;
}

struct tm Event::getDateTime() const {
    return this->datetime;
}

void Event::setName(const string &newName) {
    this->eventName = newName;
}

void Event::setDateTime(const struct tm &newDateTime) {
    this->datetime = newDateTime;
}

PersonalEvent::PersonalEvent(string eventName, struct tm datetime, string location) {
    Event(eventName, datetime);
    this->setLocation(location);
}

string PersonalEvent::getLocation() const {
    return this->location;
}

void PersonalEvent::setLocation(const string &newLocation) {
    this->location = newLocation;
}

MeetingEvent::MeetingEvent(string eventName, struct tm datetime, string attendee) {
    Event(eventName, datetime);
    this->setAttendee(attendee);
}

string MeetingEvent::getAttendee() const {
    return this->attendee;
}

void MeetingEvent::setAttendee(const string &newAttendee) {
    this->attendee = newAttendee;
}

bool operator==(Event lhs, Event rhs) {
    return lhs.getName()==rhs.getName();
}
bool operator!=(Event lhs, Event rhs) {
    return !(lhs==rhs);
}
bool operator<(Event lhs, Event rhs) {
    return lhs.getName()<rhs.getName();
}
bool operator>(Event lhs, Event rhs) {
    return rhs<lhs;
}
bool operator<=(Event lhs, Event rhs){
    return !(rhs<lhs);
}
bool operator>=(Event lhs, Event rhs) {
    return !(lhs<rhs);
}
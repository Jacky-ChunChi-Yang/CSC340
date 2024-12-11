#include "event.h"

using namespace std;

Event::Event() {
    this->setName("errorEvent");
    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);
    this->setDateTime(datetime);
}

Event::Event(const Event &oldEvent) {
    this->setName(oldEvent.getName());
    this->setDateTime(oldEvent.getDateTime());
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

PersonalEvent::PersonalEvent(string eventName, struct tm datetime, string location) : Event(eventName, datetime) {
    this->setLocation(location);
}

PersonalEvent::PersonalEvent(const PersonalEvent &oldPersonal) {
    this->setName(oldPersonal.getName());
    this->setDateTime(oldPersonal.getDateTime());
    this->setLocation(oldPersonal.getLocation());
}

string PersonalEvent::getLocation() const {
    return this->location;
}

void PersonalEvent::setLocation(const string &newLocation) {
    this->location = newLocation;
}

MeetingEvent::MeetingEvent(const MeetingEvent &oldMeeting) {
    this->setName(oldMeeting.getName());
    this->setDateTime(oldMeeting.getDateTime());
    this->setAttendee(oldMeeting.getAttendee());
}

MeetingEvent::MeetingEvent(string eventName, struct tm datetime, string attendee) : Event(eventName, datetime) {
    this->setAttendee(attendee);
}

string MeetingEvent::getAttendee() const {
    return this->attendee;
}

void MeetingEvent::setAttendee(const string &newAttendee) {
    this->attendee = newAttendee;
}

void Event::printEvent() const {
    struct tm tempDT = this->getDateTime();
    time_t timestamp = mktime(&tempDT);
    cout << "Event: " << this->getName() << endl;
    cout << "At: " << ctime(&timestamp);
}

void PersonalEvent::printEvent() const {
    cout << "You have a meeting at location: " << this->getLocation() << endl;
    struct tm tempDT = this->getDateTime();
    time_t timestamp = mktime(&tempDT);
    cout << "It begins at: " << ctime(&timestamp);
}

void MeetingEvent::printEvent() const {
    struct tm tempDT = this->getDateTime();
    time_t timestamp = mktime(&tempDT);
    cout << "You have a meeting with: " << this->getAttendee() << endl
         << "It begins at: " << ctime(&timestamp);
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
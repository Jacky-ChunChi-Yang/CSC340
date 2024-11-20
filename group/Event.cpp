#include "Event.h"

using namespace std;
// Event implementation
Event::Event(string n, string d) : name(n), date(d) {}

Event::~Event() {}

string Event::getDate() const {
    return date;
}

int Event::compareTo(const Event& other) const {
    return date.compare(other.date);
}

// MeetingEvent implementation
MeetingEvent::MeetingEvent(string n, string d, string o) 
    : Event(n, d), organizer(o) {}

void MeetingEvent::display() const {
    cout << "Meeting: " << name << " on " << date << " organized by " << organizer << endl;
}

// PersonalEvent implementation
PersonalEvent::PersonalEvent(string n, string d, string loc) 
    : Event(n, d), location(loc) {}

void PersonalEvent::display() const {
    cout << "Personal Event: " << name << " on " << date << " at " << location << endl;
}

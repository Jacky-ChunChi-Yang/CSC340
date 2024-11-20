#include <iostream>
#include <string>
#include <memory> 
using namespace std;

// Abstract class for an event
class Event {
protected:
    string name;
    string date; // YYYY-MM-DD
public:
    Event(string n, string d) : name(n), date(d) {}
    virtual ~Event() {}
    virtual void display() const = 0;
    string getDate() const { return date; }
    virtual int compareTo(const Event& other) const {
        return date.compare(other.date);
    }
};

// Derived class for a meeting event
class MeetingEvent : public Event {
    string organizer;
public:
    MeetingEvent(string n, string d, string o) 
        : Event(n, d), organizer(o) {}
    void display() const {
        cout << "Meeting: " << name << " on " << date << " organized by " << organizer << endl;
    }
};

// Derived class for a personal event
class PersonalEvent : public Event {
    string location;
public:
    PersonalEvent(string n, string d, string loc) 
        : Event(n, d), location(loc) {}
    void display() const {
        cout << "Personal Event: " << name << " on " << date << " at " << location << endl;
    }
};

// Node for linked list
class Node {
public:
    shared_ptr<Event> event;
    Node* next;
    Node(shared_ptr<Event> ev) : event(ev), next(nullptr) {}
};

// Calendar class
class Calendar {
    Node* head;
public:
    Calendar() : head(nullptr) {}

    // Add event to the list
    void addEvent(shared_ptr<Event> event) {
        Node* newNode = new Node(event);
        if (!head || head->event->compareTo(*event) > 0) {
            newNode->next = head;
            head = newNode;
        } 
        else {
            Node* current = head;
            while (current->next && current->next->event->compareTo(*event) < 0) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Search for an event by date
    void searchEvent(const string& date) const {
        Node* current = head;
        while (current) {
            if (current->event->getDate() == date) {
                current->event->display();
                return;
            }
            current = current->next;
        }
        cout << "No event found on " << date << endl;
    }

    // Display all events
    void displayAll() const {
        Node* current = head;
        while (current) {
            current->event->display();
            current = current->next;
        }
    }

    ~Calendar() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function
int main() {
    Calendar calendar;

    // Add events
    calendar.addEvent(make_shared<MeetingEvent>("Team Meeting", "2024-12-01", "Alice"));
    calendar.addEvent(make_shared<PersonalEvent>("Birthday Party", "2024-11-20", "Home"));
    calendar.addEvent(make_shared<MeetingEvent>("Project Review", "2024-11-18", "Bob"));

    // Display all events
    cout << "All events:" << endl;
    calendar.displayAll();

    // Search for an event
    cout << "\nSearch for an event on 2024-11-20:" << endl;
    calendar.searchEvent("2024-11-20");

    return 0;
}

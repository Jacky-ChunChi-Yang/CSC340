#include "Calendar.h"

using namespace std;
// Node implementation
Node::Node(shared_ptr<Event> ev) : event(ev), next(nullptr) {}

// Node::~Node() {
//     // Destructor for Node
// }

// Calendar implementation
Calendar::Calendar() : head(nullptr) {}

void Calendar::addEvent(shared_ptr<Event> event) {
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

void Calendar::searchEvent(const string& date) const {
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

void Calendar::displayAll() const {
    Node* current = head;
    while (current) {
        current->event->display();
        current = current->next;
    }
}

Calendar::~Calendar() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

#include <iostream>
#include "node.h"
#include "linkedlist.h"
#include "eventlist.h"
#include "event.h" 

using namespace std;

int main() {
    // Test Node class
    cout << "Testing Node class..." << endl;

    Node<int> node1(10);
    Node<int> node2(20);

    // Setting next and prev pointers
    node1.setNext(&node2);
    node2.setPrev(&node1);

    // Accessing data
    cout << "Node 1 data: " << *node1.getData() << endl;
    cout << "Node 2 data: " << *node2.getData() << endl;

    // Accessing next and prev
    cout << "Node 1 next data: " << *node1.getNext()->getData() << endl;
    cout << "Node 2 prev data: " << *node2.getPrev()->getData() << endl;

    // Testing comparison operators
    cout << "Are Node 1 and Node 2 equal? " << (node1 == node2 ? "Yes" : "No") << endl;

    // Test LinkedList class
    cout << "\nTesting LinkedList class..." << endl;

    LinkedList<int> list;

    // Push back elements
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    cout << "List size after adding 3 elements: " << list.getSize() << endl;

    // Accessing elements via head and tail
    cout << "Head data: " << *list.getHead()->getData() << endl;
    cout << "Tail data: " << *list.getTail()->getData() << endl;

    // Insert before a known node
    Node<int>* nodeToInsertBefore = list.getHead()->getNext();
    list.insert_before(15, nodeToInsertBefore);

    // Display list after insertion
    cout << "List after inserting 15 before 20: ";
    Node<int>* current = list.getHead();
    while (current) {
        cout << *current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;

    // Test mergeSort
    cout << "\nTesting mergeSort..." << endl;

    LinkedList<int> unsortedList;
    unsortedList.push_back(50);
    unsortedList.push_back(10);
    unsortedList.push_back(40);
    unsortedList.push_back(30);
    unsortedList.push_back(20);

    cout << "Unsorted list: ";
    current = unsortedList.getHead();
    while (current) {
        cout << *current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;

    unsortedList.mergeSort();

    cout << "Sorted list: ";
    current = unsortedList.getHead();
    while (current) {
        cout << *current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;

    // Test merging two lists
    cout << "\nTesting merge..." << endl;

    LinkedList<int> listA;
    LinkedList<int> listB;

    listA.push_back(1);
    listA.push_back(3);
    listA.push_back(5);

    listB.push_back(2);
    listB.push_back(4);
    listB.push_back(6);

    cout << "List A: ";
    current = listA.getHead();
    while (current) {
        cout << *current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;

    cout << "List B: ";
    current = listB.getHead();
    while (current) {
        cout << *current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;

    listA.merge(&listB);

    cout << "Merged List: ";
    current = listA.getHead();
    while (current) {
        cout << *current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;

    // Test EventList and derived Event classes
    cout << "\nTesting EventList and derived Event classes..." << endl;

    EventList eventList("My Events");

    // Adding events
    struct tm datetime1 = {0, 0, 12, 12, 11, 124}; // December 12, 2024
    struct tm datetime2 = {0, 0, 13, 13, 11, 124}; // December 13, 2024
    struct tm datetime3 = {0, 0, 14, 14, 11, 124}; // December 14, 2024

    Event* event1 = new Event("Generic Event", datetime1);
    PersonalEvent* event2 = new PersonalEvent("Birthday Party", datetime2, "Home");
    MeetingEvent* event3 = new MeetingEvent("Work Meeting", datetime3, "John Doe");

    eventList.push_back(*event1);
    eventList.push_back(*event2);
    eventList.push_back(*event3);

    // Displaying events
    cout << "\nDisplaying events:" << endl;
    eventList.displayEvents();

    // Testing specific derived class methods
    cout << "\nTesting specific derived class methods:" << endl;
    cout << "PersonalEvent location: " << event2->getLocation() << endl;
    cout << "MeetingEvent attendee: " << event3->getAttendee() << endl;

    delete event1;
    delete event2;
    delete event3;

    return 0;
}

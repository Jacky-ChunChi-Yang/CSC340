#include "Calendar.h"

using namespace std;

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

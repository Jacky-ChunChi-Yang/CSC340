#include "calendar.h"
#include <filesystem>
#include <fstream>
#include <iomanip>

using namespace std;

enum MainMenu { QUIT,
                DISPLAY_EVENTS,
                CHANGE_YEAR,
                CHANGE_MONTH,
                ADD_EVENT,
                DELETE_EVENT,
                EDIT_EVENT,
                SORT_EVENTS,
                SAVE_EVENTLIST,
                LOAD_EVENTLIST };

enum EventTypes { MEETING,
                  PERSONAL };

enum EditChoices { NAME,
                   YEAR,
                   MONTH,
                   DAY,
                   TIME };

Calendar::Calendar(const string &name) {
    EventList* initEvents;
    initEvents = new EventList(name);
    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);
    this->setTime(timestamp);
    this->setYear(datetime.tm_year+1900);
    this->setMonth(datetime.tm_mon);
    this->setOpenList(initEvents);
}

void Calendar::menu() {
    int input;

    cout << "Options: " << endl
         << DISPLAY_EVENTS << ") Display All Events" << endl
         << CHANGE_YEAR << ") Change Year Viewed" << endl
         << CHANGE_MONTH << ") Change Month Viewed" << endl
         << ADD_EVENT << ") Add Event" << endl
         << DELETE_EVENT << ") Delete Event" << endl
         << EDIT_EVENT << ") Edit Event" << endl
         << SORT_EVENTS << ") Sort (By Time)" << endl
         << SAVE_EVENTLIST << ") Save (Unimplemented)" << endl
         << LOAD_EVENTLIST << ") Load (Unimplemented)" << endl
         << QUIT << ") Exit" << endl;

    cin >> input;

    if (input < 0 || input > LOAD_EVENTLIST) {
        cout << "Invalid input" << endl;
        this->menu();
    }

    switch (input) {
        case QUIT:
            cout << "Thank you! Bye!" << endl;
            return;
        case DISPLAY_EVENTS:
            this->displayEvents();
            break;
        case CHANGE_YEAR:
            this->changeYear();
            break;
        case CHANGE_MONTH:
            this->changeMonth();
            break;
        case ADD_EVENT:
            this->addEvent();
            break;
        case DELETE_EVENT:
            this->deleteEvent();
            break;
        case EDIT_EVENT:
            this->editEvent();
            break;
        case SORT_EVENTS:
            this->getOpenList()->mergeSort();
            break;
        case SAVE_EVENTLIST:
            cout << "This feature is not yet implemented" << endl;
            break;
        case LOAD_EVENTLIST:
            cout << "This feature is not yet implemented" << endl;
        break;
    }

    this->displayMonth();
    this->menu();
}

void Calendar::initCalendar() {
    /*
    //***fix error here
    if (filesystem::is_empty(filePath)) {
        string listName;

        cout << "Enter a name for your list of events: " << endl;
        getline(cin, listName);

        Calendar* openCalendar = new Calendar(listName);

    //***implement after saving
    } else {
        cout << "Enter a number to open a list of events" << endl;
    }*/
    string listName;

    cout << "Enter a name for your list of events: " << endl;
    getline(cin, listName);

    this->getOpenList()->setName(listName);

    this->displayMonth();

    this->menu();
}

EventList* Calendar::getOpenList() const {
    return this->openList;
}

time_t Calendar::getTime() const {
    return this->timestamp;
}

int Calendar::getYear() const {
    return this->year;
}

int Calendar::getMonth() const {
    return this->month;
}

void Calendar::setOpenList(EventList* newList) {
    this->openList = newList;
}

void Calendar::setTime(const time_t &newTimeStamp) {
    this->timestamp = newTimeStamp;
}

void Calendar::setYear(const int &newYear) {
    this->year = newYear;
}

void Calendar::setMonth(const int &newMonth) {
    this->month = newMonth;
}

void Calendar::displayMonth() const {
    int month = this->getMonth();
    int year = this->getYear();

    cout << "Calendar for " << getMonthName(month) << " " << year << endl;
    cout << "Su  Mo  Tu  We  Th  Fr  Sa\n";

    // Calculate starting weekday
    time_t t = time(nullptr);
    struct tm timeInfo = *localtime(&t);
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = month;
    timeInfo.tm_mday = 1;
    mktime(&timeInfo);
    int startDay = timeInfo.tm_wday;

    int daysInMonth = (month == 1 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) ? 29 :
                      (month == 1) ? 28 :
                      (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11) ? 31 : 30;

    //improve this
    bool daysWithEvents[31];
    for (int i=0; i<31; i++) {
        daysWithEvents[i] = false;
    }
    Node<Event>* movPtr = this->getOpenList()->getHead();
    struct tm eventDateTime;
    while (movPtr != nullptr) {
        eventDateTime = movPtr->getData().getDateTime();
        if (eventDateTime.tm_year == this->getYear() && eventDateTime.tm_mon == this->getMonth()) {
            daysWithEvents[eventDateTime.tm_mday-1] = true;
        }
        if (movPtr->getNext() != nullptr) {
            movPtr = movPtr->getNext();
        }
        else {
            movPtr = nullptr;
        }
    }

    for (int i = 0; i < startDay; i++) cout << "    ";
    for (int day = 1; day <= daysInMonth; day++) {
        if (daysWithEvents[day-1]) {
            cout << setw(2) << setfill('0') << day << "* ";
        } else {
            cout << setw(2) << setfill('0') << day << "  ";
        }
        if ((startDay + day) % 7 == 0) cout << endl;
    }
    cout << endl << endl;
}

void Calendar::displayEvents() {
    this->getOpenList()->displayEvents();
}

string getMonthName(const int month) {
    string months[12] = {"January", "February", "March", "April",
                         "May", "June", "July", "August",
                         "September", "October", "November", "December"};
    return months[month];
}

void Calendar::changeYear() {
    int newYear;
    cout << "What year would you like to view?" << endl;
    cin >> newYear;

    if (!cin) {
        cout << "Invalid Year" << endl;
        changeYear();
    }
    else {
        this->setYear(newYear);
    }
}

void Calendar::changeMonth() {
    int newMonth;
    cout << "What month would you like to view? (1-12)" << endl;
    cin >> newMonth;

    if (!cin || newMonth < 1 || newMonth > 12) {
        cout << "Invalid Month" << endl;
        changeMonth();
    }
    else {
        this->setMonth(newMonth-1);
    }
}

void Calendar::addEvent() {
    int inputInt;
    string name;
    int year = 2024;
    int month = 0;
    int day = 1;
    int hour = 0;
    int minute = 0;

    cout << "What type of event would you like to add?" << endl
         << MEETING << ") Meeting Event" << endl
         << PERSONAL << ") Personal Event" << endl;

    cin >> inputInt;
    if (inputInt < MEETING || inputInt > PERSONAL) {
        cout << "Invalid input" << endl;
        addEvent();
        return;
    }

    cout << "What would you like to call this event?" << endl;
    cin.ignore();
    getline(cin, name);

    //add current year default
    cout << "What year is your event?" << endl;
    cin >> year;

    cout << "What month is your event? (1-12)" << endl;
    cin >> month;

    cout << "What day of the month is your event?" << endl;
    cin >> day;

    cout << "What hour is your event?" << endl;
    cin >> hour;

    cout << "What minute is your event?" << endl;
    cin >> minute;

    cout << name << year << month << day << hour << minute << endl;

    struct tm datetime;

    datetime.tm_year = year - 1900; // Number of years since 1900
    datetime.tm_mon = month - 1;
    datetime.tm_mday = day;
    datetime.tm_hour = hour;
    datetime.tm_min = minute;
    datetime.tm_sec = 0;
    // -1 uses the computer's timezone setting
    datetime.tm_isdst = -1;

    mktime(&datetime);

    switch (inputInt) {
        case MEETING: {
            string attendees;
            cout << "Who else will attend this meeting?" << endl;
            cin.ignore();
            getline(cin, attendees);
            MeetingEvent* newMeeting = new MeetingEvent(name, datetime, attendees);
            this->getOpenList()->push_back(*newMeeting);
            break;
        }
        case PERSONAL: {
            string location;
            cout << "Where will this event take place?" << endl;
            cin.ignore();
            getline(cin, location);
            PersonalEvent* newPersonal = new PersonalEvent(name, datetime, location);
            this->getOpenList()->push_back(*newPersonal);
            break;
        }
    }
}

void Calendar::deleteEvent() {
    string input;
    cout << "Enter the name of the event you would like to delete: " << endl;
    cin.ignore();
    getline(cin, input);

    this->getOpenList()->deleteEvent(input);
}

//complete this
void Calendar::editEvent() {
    string name = "";
    cout << "What event would you like to edit?" << endl;
    cin.ignore();
    getline(cin, name);

    bool validInputs = false;
    int input;
    while (validInputs == false) {
        cout << "What would you like to change?" << endl
            << NAME << ") Name" << endl
            << YEAR << ") Year" << endl
            << MONTH << ") Month" << endl
            << DAY << ") Day" << endl
            << TIME << ") Time" << endl;

        cin >> input;

        if (input < 0 || input > TIME) {
            cout << "Invalid input" << endl;
        }
        else {
            validInputs == true;
        }
    }

    Event* chosenEvent;

    switch (input) {
        case NAME:
            break;
        case YEAR:
            break;
        case MONTH:
            break;
        case DAY:
            break;
        case TIME:
            break;
    }
}
#include "calendar.h"

using namespace std;

void calendarInit() {
    if (filesystem::is_empty(filePath)) {
        string listName;

        cout << "Enter a name for your list of events: " << endl;
        getline(cin, listName);

        Calendar* openCalendar = new Calendar(listName);

    } else {
        cout << "Enter a number to open a list of events" << endl;
    }
}

Calendar::Calendar(const string &name) {
    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);
    this->setTime(timestamp);
    this->setYear(datetime.tm_year);
    this->setMonth(datetime.tm_mon);
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
}


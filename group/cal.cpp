#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

// Enum for user actions
enum Actions {
    ADD_EVENT = 1,
    SEARCH_EVENT,
    DISPLAY_MONTH,
    EXIT
};

// Abstract class for an event
class Event {
protected:
    string name;
    string date; // YYYY-MM-DD
    string time; // HH:MM
public:
    Event(string n, string d, string t) : name(n), date(d), time(t) {}
    virtual ~Event() {}
    virtual void display() const = 0;
    string getDate() const { return date; }
    string getTime() const { return time; }
    virtual int compareTo(const Event& other) const {
        return date.compare(other.date);
    }
};

// Derived class for a meeting event
class MeetingEvent : public Event {
    string organizer;
public:
    MeetingEvent(string n, string d, string t, string o) 
        : Event(n, d, t), organizer(o) {}
    void display() const override {
        cout << "Meeting: " << name << " on " << date << " at " << time
             << " organized by " << organizer << endl;
    }
};

// Derived class for a personal event
class PersonalEvent : public Event {
    string location;
public:
    PersonalEvent(string n, string d, string t, string loc) 
        : Event(n, d, t), location(loc) {}
    void display() const override {
        cout << "Personal Event: " << name << " on " << date << " at " << time
             << " at " << location << endl;
    }
};

// Node for linked list
class Node {
public:
    shared_ptr<Event> event;
    Node* next;
    Node(shared_ptr<Event> ev) : event(ev), next(nullptr) {}
};

// Day class for events
class Day {
    Node* head;
public:
    Day() : head(nullptr) {}

    void addEvent(shared_ptr<Event> event) {
        Node* newNode = new Node(event);
        if (!head || head->event->getTime() > event->getTime()) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->event->getTime() < event->getTime()) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void displayEvents() const {
        Node* current = head;
        while (current) {
            current->event->display();
            current = current->next;
        }
    }

    bool hasEvents() const { return head != nullptr; }

    ~Day() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Calendar class
class Calendar {
    vector<vector<Day> > months; // 12 months with 31 days each
    int year;
public:
    Calendar(int y) : year(y), months(12, vector<Day>(31)) {}

    void addEvent(shared_ptr<Event> event) {
        string date = event->getDate();
        int month = stoi(date.substr(5, 2)) - 1;
        int day = stoi(date.substr(8, 2)) - 1;
        months[month][day].addEvent(event);
    }

    void searchEvent(const string& date) const {
        int month = stoi(date.substr(5, 2)) - 1;
        int day = stoi(date.substr(8, 2)) - 1;
        cout << "Events on " << date << ":" << endl;
        months[month][day].displayEvents();
    }

    void displayMonth(int month) const {
        cout << "Calendar for " << year << "-" << setw(2) << setfill('0') << month + 1 << ":\n";
        cout << "Su  Mo  Tu  We  Th  Fr  Sa\n";
        time_t t = time(nullptr);
        tm timeInfo = *localtime(&t);
        timeInfo.tm_year = year - 1900;
        timeInfo.tm_mon = month;
        timeInfo.tm_mday = 1;
        mktime(&timeInfo);
        int startDay = timeInfo.tm_wday;
        int daysInMonth = (month == 1 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) ? 29 : (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11) ? 31 : 30;
        for (int i = 0; i < startDay; i++) cout << "   ";
        for (int day = 1; day <= daysInMonth; day++) {
            if (months[month][day - 1].hasEvents()) {
                cout << setw(2) << setfill('0') << day << "* ";
            } else {
                cout << setw(2) << setfill('0') << day << "  ";
            }
            if ((startDay + day) % 7 == 0) cout << endl;
        }
        cout << endl;
    }
};

// Main function
int main() {
    int year = 2024;
    Calendar calendar(year);
    while (true) {
        cout << "Choose an action: (1) Add Event (2) Search Event (3) Display Month (4) Exit\n";
        int action;
        cin >> action;
        if (action == EXIT) break;
        switch (action) {
        case ADD_EVENT: {
            string type, name, date, time, extra;
            cout << "Enter event type (Meeting/Personal): ";
            cin >> type;
            cout << "Enter event name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            cout << "Enter time (HH:MM): ";
            cin >> time;
            if (type == "Meeting") {
                cout << "Enter organizer: ";
                cin.ignore();
                getline(cin, extra);
                calendar.addEvent(make_shared<MeetingEvent>(name, date, time, extra));
            } else if (type == "Personal") {
                cout << "Enter location: ";
                cin.ignore();
                getline(cin, extra);
                calendar.addEvent(make_shared<PersonalEvent>(name, date, time, extra));
            }
            break;
        }
        case SEARCH_EVENT: {
            string date;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            calendar.searchEvent(date);
            break;
        }
        case DISPLAY_MONTH: {
            int month;
            cout << "Enter month (1-12): ";
            cin >> month;
            calendar.displayMonth(month - 1);
            break;
        }
        default:
            cout << "Invalid action!" << endl;
        }
    }
    return 0;
}

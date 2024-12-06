#ifndef CALENDAR
#define CALENDAR

#include <filesystem>
#include <iostream>
#include <string>

#include "eventlist.h"


const std::string filePath = "eventLists";

class Calendar {
    private:
        EventList* openList;
        time_t timestamp;
        int year;
        //0-11
        int month;
    public:
        Calendar(const std::string &name);
        time_t getTime() const;
        int getYear() const;
        int getMonth() const;
        void setTime(const time_t &newTime);
        void setYear(const int &newYear);
        void setMonth(const int &newMonth);
        void displayMonth() const;
};

void calendarInit();

#endif
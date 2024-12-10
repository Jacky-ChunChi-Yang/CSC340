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
        void menu();
        void initCalendar();
        time_t getTime() const;
        int getYear() const;
        int getMonth() const;
        EventList* getOpenList() const;
        void setTime(const time_t &newTime);
        void setYear(const int &newYear);
        void setMonth(const int &newMonth);
        void setOpenList(EventList* newList);
        void displayMonth() const;
        void changeYear();
        void changeMonth();
        void addEvent();
        void deleteEvent();
        void editEvent();
};

std::string getMonthName(const int month);

#include "calendar.cpp"

#endif
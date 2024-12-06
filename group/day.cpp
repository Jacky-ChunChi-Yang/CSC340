#include "day.h"

using namespace std;

//returns current day of the week as int 0-6
int getDay() {
    time_t timestamp = time(&timestamp);
    struct tm datetime = *localtime(&timestamp);

    return datetime.tm_wday;
}

//returns day of the week of timestamp as int 0-6
int getDay(const time_t &timestamp) {
    struct tm datetime = *localtime(&timestamp);

    return datetime.tm_wday;
}

//returns day of the week of struct tm as int 0-6
int getDay(const struct tm &datetime) {
    return datetime.tm_wday;
}
#include "day.h"

using namespace std;

//returns day of the week
int getDay() {
    struct tm datetime;
    time_t timestamp;
    time(&timestamp);

    return datetime.tm_wday;
}
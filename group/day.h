#ifndef DAY
#define DAY

#include <ctime>

//returns day of the week as 0-6
int getDay();
int getDay(const time_t &timestamp);
int getDay(const struct tm &datetime);

#endif
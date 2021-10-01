#include "GPSAlgorithm.h"

void UTCT2GPST(const UTCT& utct, GPST& gpst)
{
    // TODO
}

void GPST2UTCT(const GPST& gpst, UTCT& utct)
{
    // TODO
}

int UTCT2DOY(const UTCT& utct)
{
#if 0
    QDate date(utct.year, utct.month, utct.day);
    return date.dayOfYear();
#endif
    int maxDayArrayNormal[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int maxDayArrayLeapYear[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int year = utct.year;
    int month = utct.month;
    int day = utct.day;
    bool mod4 = year % 4 == 0;
    bool mod100 = year % 100 == 0;
    bool mod400 = year % 400 == 0;
    bool isLeapYear = false;
    if (mod4)
    {
        if (!mod100 || mod400)
        {
            isLeapYear = true;
        }
    }
    for (int m = 0; m < month - 1; ++m)
    {
        day += isLeapYear ? maxDayArrayLeapYear[m] : maxDayArrayNormal[m];
    }
    return day;
}

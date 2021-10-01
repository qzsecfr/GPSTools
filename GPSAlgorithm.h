#pragma once
#include <QDateTime>
#include <QDate>

struct UTCT
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double second;

    UTCT()
    {
        year = 1980;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
    }

    UTCT(const UTCT& utct)
    {
        year = utct.year;
        month = utct.month;
        day = utct.day;
        hour = utct.hour;
        minute = utct.minute;
        second = utct.second;
    }

    UTCT(const QDateTime& qdatetime)
    {
        year = qdatetime.date().year();
        month = qdatetime.date().month();
        day = qdatetime.date().day();
        hour = qdatetime.time().hour();
        minute = qdatetime.time().minute();
        second = qdatetime.time().second();
    }

    UTCT& operator=(const UTCT& utct)
    {
        year = utct.year;
        month = utct.month;
        day = utct.day;
        hour = utct.hour;
        minute = utct.minute;
        second = utct.second;
        return *this;
    }
};

struct GPST
{
    int week = 1;
    double second = 0;

    GPST& operator=(const GPST& gpst)
    {
        week = gpst.week;
        second = gpst.second;
        return *this;
    }
};

void UTCT2GPST(const UTCT& utct, GPST& gpst);

void GPST2UTCT(const GPST& gpst, UTCT& utct);

int UTCT2DOY(const UTCT& utct);
#pragma once
#include <QDateTime>
#include <QDate>
#include <QTime>

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

    QDateTime getDateTime()
    {
        QDateTime dateTime;
        dateTime.setDate(QDate(year, month, day));
        dateTime.setTime(QTime(hour, minute, second));
        return dateTime;
    }

    QDate getDate()
    {
        return QDate(year, month, day);
    }

    QTime getTime()
    {
        return QTime(hour, minute, second);
    }
};

struct GPST
{
    int week;
    double second;

    GPST()
    {
        week = 1;
        second = 0;
    }

    GPST(int week1, double second1)
    {
        week = week1;
        second = second1;
        bool valid = true;
        while (second < 0)
        {
            week--;
            second += 86400.0 * 7;
            if (week < 0)
            {
                valid = false;
                break;
            }
        }
        while (second >= 86400.0 * 7)
        {
            week++;
            second -= 86400.0 * 7;
        }
        if (!valid)
        {
            week = 1;
            second = 0;
        }
    }

    GPST& operator=(const GPST& gpst)
    {
        week = gpst.week;
        second = gpst.second;
        return *this;
    }
};

GPST UTCT2GPST(const UTCT& utct);

UTCT GPST2UTCT(const GPST& gpst);

int UTCT2DOY(const UTCT& utct);

double UTCT2MJD(const UTCT& utct);

UTCT MJD2UTCT(double mjd);

GPST MJD2GPST(double mjd);

double GPST2MJD(const GPST& gpst);
#pragma once

#include <QDateTime>
#include <QDate>
#include <QTime>

#ifndef PI
#define PI 3.1415926535897932
#endif // !PI

#ifndef D2R
#define D2R (PI / 180.0)
#endif // !D2R

#ifndef R2D
#define R2D (180.0 / PI)
#endif // !R2D

#ifndef WGS84_ELLIP_A
#define WGS84_ELLIP_A 6378137
#endif // !WGS84_ELLIP_A

#ifndef WGS84_ELLIP_B
#define WGS84_ELLIP_B 6356752.3142
#endif // !WGS84_ELLIP_B

#ifndef WGS84_FLAT
#define WGS84_FLAT (1.0 / 298.257223563)
#endif // !WGS84_FLAT

#ifndef WGS84_E2
#define WGS84_E2 0.00669437999013
#endif // !WGS84_E2


#ifndef WGS84_OMEGA
#define WGS84_OMEGA 7.2921151467e-5
#endif // !WGS84_OMEGA

#ifndef EARTH_GM
#define EARTH_GM 398600.5e+9
#endif // !EARTH_GM

#ifndef LIGHT_SPEED
#define LIGHT_SPEED 299792458.0 // m/s
#endif // !LIGHT_SPEED


#ifndef RELATIVITY_CORRECT_CONSTANT
#define RELATIVITY_CORRECT_CONSTANT -4.442807633e-10  //相对论改正常数
#endif // !RELATIVITY_CORRECT_CONSTANT

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

struct BLH
{
    // 经纬度采用度格式
    double lat;
    double lon;
    double alt;

    BLH()
    {
        lat = 0;
        lon = 0;
        alt = 0;
    }

    BLH(double lat1, double lon1, double alt1)
    {
        // 未检查数据是否合法
        lat = lat1;
        lon = lon1;
        alt = alt1;
    }

    BLH& operator=(const BLH& blh)
    {
        lat = blh.lat;
        lon = blh.lon;
        alt = blh.alt;
        return *this;
    }
};

struct XYZ
{
    double X;
    double Y;
    double Z;

    XYZ()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    XYZ(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    XYZ& operator=(const XYZ& xyz)
    {
        X = xyz.X;
        Y = xyz.Y;
        Z = xyz.Z;
        return *this;
    }

    XYZ operator+(const XYZ& xyz) const
    {
        XYZ ret;
        ret.X = X + xyz.X;
        ret.Y = Y + xyz.Y;
        ret.Z = Z + xyz.Z;
        return ret;
    }

    XYZ operator-(const XYZ& xyz) const
    {
        XYZ ret;
        ret.X = X - xyz.X;
        ret.Y = Y - xyz.Y;
        ret.Z = Z - xyz.Z;
        return ret;
    }
};
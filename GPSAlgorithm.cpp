#pragma warning(disable:26451)

#include "GPSAlgorithm.h"

GPST UTCT2GPST(const UTCT& utct)
{
    return MJD2GPST(UTCT2MJD(utct));
}

UTCT GPST2UTCT(const GPST& gpst)
{
    return MJD2UTCT(GPST2MJD(gpst));
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

double UTCT2MJD(const UTCT& utct)
{
    double year = utct.year;
    double month = utct.month;
    double day = utct.day;
    double hour = utct.hour + utct.minute / 60.0 + utct.second / 3600.0;
    if (month <= 2)
    {
        year -= 1;
        month += 12;
    }
    double JD = static_cast<int>(365.25 * year) +
        static_cast<int>(30.6001 * (month + 1)) +
        day + hour / 24.0 + 1720981.5;
    return JD - 2400000.5;
}

UTCT MJD2UTCT(double mjd)
{
    double JD = mjd + 2400000.5;
    int a = static_cast<int>(JD + 0.5);
    int b = a + 1537;
    int c = static_cast<int>((b - 122.1) / 365.25);
    int d = static_cast<int>(365.25 * c);
    int e = static_cast<int>((b - d) / 30.6001);
    double D = b - d - static_cast<int>(30.6001 * e) +
        (JD + 0.5 - static_cast<int>(JD + 0.5));
    UTCT utct;
    utct.month = e - 1 - 12 * static_cast<int>(e / 14.0);
    utct.year = c - 4715 - static_cast<int>((7 + utct.month) / 10.0);
    utct.day = static_cast<int>(D);
    double secOfDay = (D - utct.day) * 86400.0;
    utct.hour = static_cast<int>(secOfDay / 3600.0);
    utct.minute = static_cast<int>((secOfDay - utct.hour * 3600.0) / 60.0);
    utct.second = secOfDay - utct.hour * 3600.0 - utct.minute * 60.0;
    return utct;
}

GPST MJD2GPST(double mjd)
{
    GPST gpst;
    gpst.week = static_cast<int>((mjd - 44244) / 7.0);
    gpst.second = (mjd - 44244 - gpst.week * 7) * 86400.0;
    return gpst;
}

double GPST2MJD(const GPST& gpst)
{
    return 44244 + gpst.week * 7 + gpst.second / 86400.0;
}

XYZ BLH2XYZ(const BLH& blh)
{
    double sinLat = sin(blh.lat * D2R);
    double cosLat = cos(blh.lat * D2R);
    double sinLon = sin(blh.lon * D2R);
    double cosLon = cos(blh.lon * D2R);
    double N = WGS84_ELLIP_A / (sqrt(1 - WGS84_E2 * sinLat * sinLat));
    XYZ xyz;
    xyz.X = (N + blh.alt) * cosLat * cosLon;
    xyz.Y = (N + blh.alt) * cosLat * sinLon;
    xyz.Z = (N * (1 - WGS84_E2) + blh.alt) * sinLat;
    return xyz;
}

BLH XYZ2BLH(const XYZ& xyz)
{
    double X = xyz.X;
    double Y = xyz.Y;
    double Z = xyz.Z;
    double B = 0.0, L = 0.0, H = 0.0; // rad
    double dZ = WGS84_E2 * Z;
    double N = 0.0;
    double sinB = 0.0;
    double dZP = 0.0;
    int flag = 0;
    do
    {
        dZP = dZ;
        L = atan2(Y, X);
        B = atan2(Z + dZ, sqrt(X * X + Y * Y));
        sinB = (Z + dZ) / sqrt(X * X + Y * Y + (Z + dZ) * (Z + dZ));
        N = WGS84_ELLIP_A / (sqrt(1 - WGS84_E2 * sin(B) * sin(B)));
        H = sqrt(X * X + Y * Y + (Z + dZ) * (Z + dZ)) - N;
        dZ = N * WGS84_E2 * sinB;
        flag += 1;
    } while (((dZ - dZP) > 1e-8) && (flag < 10));
    BLH blh;
    blh.lat = B * R2D;
    blh.lon = L * R2D;
    blh.alt = H;
    return blh;
}

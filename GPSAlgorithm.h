#pragma once

#include "GPSDefine.h"

GPST UTCT2GPST(const UTCT& utct);

UTCT GPST2UTCT(const GPST& gpst);

int UTCT2DOY(const UTCT& utct);

double UTCT2MJD(const UTCT& utct);

UTCT MJD2UTCT(double mjd);

GPST MJD2GPST(double mjd);

double GPST2MJD(const GPST& gpst);

XYZ BLH2XYZ(const BLH& blh);

BLH XYZ2BLH(const XYZ& xyz);
#pragma once

#include "GPSDefine.h"

#include <QString>
#include <QVector>
#include <QMap>

enum RinexFileType
{
	OBSERVATION_DATA_FILE = 0,
	NAVIGATION_DATA_FILE,
	METEOROLOGICAL_DATA_FILE,
};

enum SatSystem
{
	UNKNOW = 0,
	GPS = 1,
	GLONASS = 2,
	BeiDou = 4,
	Galileo = 8,
	SBAS = 16,
	IRNSS = 32,
	QZSS = 64,

	MIX_MAIN = GPS | GLONASS | BeiDou | Galileo,
	MIX_ALL = GPS | GLONASS | BeiDou | Galileo | SBAS | IRNSS | QZSS,
};

enum TimeSystem
{
	UTC = 0,
	GPST = 1,
	GLOT = 2, // equal to UTCT
	BDT = 3,
	GALT = 4,
};

enum ObsType
{
	GPS_L1_C,
	GPS_L1_P,
	GPS_L1_D,
	GPS_L1_S,
	GPS_L2_C,
	GPS_L2_P,
	GPS_L2_D,
	GPS_L2_S,
	GPS_L5_C,
	GPS_L5_P,
	GPS_L5_D,
	GPS_L5_S,

	GLO_R1_C,
	GLO_R1_P,
	GLO_R1_D,
	GLO_R1_S,
	GLO_R2_C,
	GLO_R2_P,
	GLO_R2_D,
	GLO_R2_S,
	GLO_R3_C,
	GLO_R3_P,
	GLO_R3_D,
	GLO_R3_S,

	BDS_B1_C,
	BDS_B1_P,
	BDS_B1_D,
	BDS_B1_S,
	BDS_B2_C,
	BDS_B2_P,
	BDS_B2_D,
	BDS_B2_S,
	BDS_B3_C,
	BDS_B3_P,
	BDS_B3_D,
	BDS_B3_S,

	GAL_E1_C,
	GAL_E1_P,
	GAL_E1_D,
	GAL_E1_S,
	GAL_E8_C,
	GAL_E8_P,
	GAL_E8_D,
	GAL_E8_S,
	GAL_E7_C,
	GAL_E7_P,
	GAL_E7_D,
	GAL_E7_S,
};

struct HeaderStruct
{
	// "RINEX VERSION / TYPE" mandatory
	QString rinexVersion = "2.11"; // F9.2, 11X
	RinexFileType fileType = OBSERVATION_DATA_FILE; // A1, 19X
	int satSys = SatSystem::GPS; // A1, 19X
	// "PGM / RUN BY / DATE " mandatory
	QString program; // A20
	QString runBy; // A20
	QString fileDate; // A20
	// "MARKER NAME         " mandatory
	QString antennaMarkerName; // A60
	// "MARKER NUMBER       " optional
	QString antennaMarkerNumber; // A60
	// "OBSERVER / AGENCY   " mandatory
	QString observer; // A60
	QString agency; // A60
	// "REC # / TYPE / VERS " mandatory
	QString receiverNumber; // A20
	QString receiverType; // A20
	QString receiverVersion; // A20
	// "ANT # / TYPE        " mandatory
	QString antennaNumber; // A20
	QString antennaType; // A20
	// "APPROX POSITION XYZ " mandatory
	double approxPositionXYZ[3] = { 0, 0, 0 }; // 3F14.4
	// "ANTENNA: DELTA H/E/N" mandatory
	double antennaHEN[3] = { 0, 0, 0 }; // 3F14.4;
	// "WAVELENGTH FACT L1/2" optional
	int waveLengthL1 = 1; // I6
	int waveLengthL2 = 1; // I6
	int validSatNumFactors; // I6
	QVector<QString> satFactorPrnList; // 7(3X, A1I2)
	// "# / TYPES OF OBSERV " mandatory
	int obsTypes = 0; // I6
	QVector<QString> obsTypeList; // 9(4X, A1A1), if more than 9 obsTypes,
								  // use continuation lines, including headerLabel cols(61-80).
	// For rinex 2.X(less than extened rinex 2.11), obs types are represented as number 1-8:
	//		GPS		GLONASS		Galileo		SBAS
	// 1:	L1		G1			E2-L1-E1	L1
	// 2:	L2		G2			--			--
	// 5:	L5		--			E5a			L5
	// 6:	--		--			E6			--
	// 7:	--		--			E5b			--
	// 8:	--		--			E5a+b		--
	// obs type codes are:
	// C:	Pseudorange	GPS:		C/A, L2C
	//					GLONASS:	C/A
	//					Galileo:	All
	// P:	Pseudorange	GPS/GLO:	P code
	// L:	Carrier phase
	// D:	Doppler frequency
	// S:	Raw signal strength or SNR values
	// 
	// units are:
	// Phase:		full cycles
	// Pseudorange:	meters
	// Doppler:		Hz
	// SNR:			Receiver dependent

	// "INTERVAL            " optional
	double interval = 1;
	// "TIME OF FIRST OBS   " mandatory
	UTCT firstObsTime; // 5I6,F13.7 for year,month,day,hour,minute,second
	TimeSystem timeSystem = GPST; // 5X,A3 (GPS, GLO, GAL, etc.)
	// "TIME OF LAST OBS    " optional
	UTCT lastObsTime;
	// "RCV CLOCK OFFS APPL " optional
	int reveiverClockOffset = 0;
	// "LEAP SECONDS        " optional
	int leapSeconds = 0;
	// "# OF SATELLITES     " optional
	int satNumber = 0;
	// "PRN / # OF OBS      " optional
	QMap<QString, QVector<QString>> prnObsType;
};

struct ObsValueUnit
{
	double obsValue; // F14.3
	int LLI = 0; // 0-7 possible
				 // 0b000 or blank: normal or unknow
				 // 0b**1: Lost lock between previous and current epoch, cycle slip possible
				 // 0b*1*: Opposite wavelength factor for current epoch
				 // 0b1**: Observation under AS, noise may be increased
	int signalStrength = 0; // 0-9 possible
							// 0 or blank: dont know or dont care
							// 1: minimum possible signal strength
							// 5: threshold for good S/N ratio
							// 9: maximum possible signal strength
};

struct ObsEpochNumber
{
	UTCT epochTime; // year(1X,I2), month(1X,I2), day(1X,I2),
					// hour(1X,I2), minute(1X,I2), second(F11.7)
	int epochFlag = 0; // (2X,I1)	0: OK
					   //			1: power failure between previous and current epoch
					   //			2: start moving antenna
					   //			3: new site occupation
					   //			4: header information follows
					   //			5: external event
					   //			6: cycle slip
	int satNumber = 0; // I3
	QVector<QString> prnList; // (A1,I2)
	double receiverClockOffset; // seconds, (F12.9), optional
	QMap<QString, QMap<int, ObsValueUnit>> satObsValue; // sat prn --> obs type --> obs data
														// obs type: ObsType enum
};
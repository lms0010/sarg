#ifndef ADSBMODULE_H
#define ADSBMODULE_H

#include "module.h"
#include <vector>

class ADSBModule: public Module {
public:

    virtual      ~ADSBModule() {}

    virtual bool getObjectCount(int& numObjects) = 0;
    virtual bool getHexIdent(int index, char** hexIdent) = 0;
    virtual bool getAltitude(int index, float& altitude) = 0;
    virtual bool getGroundSpeed(int index, float& groundSpeed)  = 0;
    virtual bool getLatitude(int index, float& latitude) = 0;
    virtual bool getLongitude(int index, float& longitude) = 0;
    virtual bool getTrack(int index, float& track) = 0;
    virtual bool getCallSign(int index, char** callSign) = 0;
    virtual bool getTimeStamp(int index, float& timeStamp)  = 0;

    enum Message
    {
        MSG_TYPE,
        TRANSMISSION_TYPE,
        SESSION_ID,
        AIRCRAFT_ID,
        HEX_IDENT,
        FLIGHT_ID,
        DATE_GEN,
        TIME_GEN,
        DATE_LOG,
        TIME_LOG,
        CALLSIGN,
        ALTITUDE,
        GROUND_SPEED,
        TRACK,
        LATITUDE,
        LONGITUDE,
        VERTICAL_RATE,
        SQUAWK,
        ALERT,
        EMERGENCY,
        SPI,
        IS_ON_GROUND
    };

    struct positionMSG
    {
       char hex_ident[8];
       char callSign[20];
		int flightId;
       float latitude, longitude; //in degrees
       float altitude;            //in feet
       float groundSpeed;         //in knots
       float track;               //in degrees
       bool inUse;
       positionMSG(): latitude(0.0f), longitude(0.0f), altitude(0.0f), groundSpeed(0.0f), track(0.0f), inUse(false) {
       }

    };

protected:
    std::vector<positionMSG> visibleAircraft;







};



#endif // ADSBMODULE_H

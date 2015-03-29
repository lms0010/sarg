#ifndef ADSBMODULE_H
#define ADSBMODULE_H

#include "module.h"

class ADSBModule: public Module {
public:
    virtual      ~ADSBModule() {}

    virtual bool getHexIdent(char** hexIdent) = 0;
    virtual bool getFlightID(int& flightID) = 0;
    virtual bool getAltitude(float& altitude) = 0;
    virtual bool getGroundSpeed(int& groundSpeed) = 0;
    virtual bool getLatitude(float& lat) = 0;
    virtual bool getLongitude(float& lon) = 0;
    virtual bool getTrack(int& track) = 0;
    virtual bool getDeltaTime(int& deltaTime) = 0;

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
       char hex_ident[7];
       float latitude, longitude, altitude;
       bool inUse;
       positionMSG(): latitude(0.0f), longitude(0.0f), altitude(0.0f), inUse(false) {
       }

    } positionArray[500];





};



#endif // ADSBMODULE_H

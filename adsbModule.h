#ifndef ADSBMODULE_H
#define ADSBMODULE_H

#include "module.h"

class ADSBModule: public Module {
public:
    virtual      ~ADSBModule() {}
    virtual bool getMessageType(char** messageType) = 0;
    virtual bool getTransmissionType(int& transType) = 0;
    virtual bool getHexIdent(char** hexIdent) = 0;
    virtual bool getFlightID(int& flightID) = 0;
    virtual bool getAltitude(int& altitude) = 0;
    virtual bool getGroundSpeed(int& groundSpeed) = 0;
    virtual bool getLatitude(float& lat) = 0;
    virtual bool getLongitude(float& lon) = 0;
    virtual bool getTrack(int& track) = 0;
    virtual bool getDeltaTime(int& deltaTime) = 0;

};

#endif // ADSBMODULE_H

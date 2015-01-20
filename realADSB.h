#ifndef REALADSB_H
#define REALADSB_H

#include "adsbModule.h"

class RealADSB: public ADSBModule {
public:
    virtual         ~RealADSB();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();

    virtual bool    getMessageType(char** messageType);
    virtual bool    getTransmissionType(int& transType);
    virtual bool    getHexIdent(char** hexIdent);
    virtual bool    getFlightID(int& flightID);
    virtual bool    getAltitude(int& altitude);
    virtual bool    getGroundSpeed(int& groundSpeed);
    virtual bool    getLatitude(float& lat);
    virtual bool    getLongitude(float& lon);
    virtual bool    getTrack(int& track);
    virtual bool    getDeltaTime(int& deltaTime);


};

#endif // REALADSB_H

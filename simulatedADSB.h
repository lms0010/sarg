#ifndef SIMULATEDADSB_H
#define SIMULATEDADSB_H

#include "adsbModule.h"

class SimulatedADSB: public ADSBModule {
public:
    virtual         ~SimulatedADSB();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();

    virtual bool getObjectCount(int& numObjects);
    virtual bool getHexIdent(int index, char** hexIdent);
    virtual bool getAltitude(int index, float& altitude);
    virtual bool getGroundSpeed(int index, float& groundSpeed);
    virtual bool getLatitude(int index, float& latitude);
    virtual bool getLongitude(int index, float& longitude);
    virtual bool getTrack(int index, float& track);
    virtual bool getCallSign(int index, char** callSign);
    virtual bool getTimeStamp(int index, int& timeStamp) ;


};

#endif // SIMULATEDADSB_H

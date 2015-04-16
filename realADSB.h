#ifndef REALADSB_H
#define REALADSB_H
#include <pthread.h>

#include "adsbModule.h"

#define ADSB_HOSTNAME       "localhost"
#define ADSB_PORTNUMBER     "30003"

class RealADSB: public ADSBModule {
public:
                     RealADSB();
    virtual         ~RealADSB();
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
    virtual bool getTimeStamp(int index, int& timeStamp);

private:
    bool            errorFlag;
    pthread_t       thread;
    static void*    ADSBClientThread(void* threadid);


};

#endif // REALADSB_H

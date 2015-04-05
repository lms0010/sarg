#ifndef REALGPS_H
#define REALGPS_H

#include "gpsModule.h"

class RealGPS: public GPSModule {
 public:
    virtual         ~RealGPS();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool    getPos3(Vector3& pos);
};



#endif // REALGPS_H

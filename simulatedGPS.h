#ifndef SIMULATEDGPS_H
#define SIMULATEDGPS_H

#include "gpsModule.h"

class SimulatedGPS: public GPSModule {
 public:
    virtual         ~SimulatedGPS();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool    getPos3(Vector3& pos);
};


#endif // SIMULATEDGPS_H

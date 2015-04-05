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
    virtual bool getCurrentLatitude(float& vehicleLat);
    virtual bool getCurrentLongitude(float& vehicleLon);
    virtual bool getCurrentAltitude(float& vehicleAltitude); //where do we get altitude from?
};



#endif // REALGPS_H

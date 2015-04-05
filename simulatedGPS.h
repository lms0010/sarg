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
    virtual bool getCurrentLatitude(float& vehicleLat);
    virtual bool getCurrentLongitude(float& vehicleLon);
    virtual bool getCurrentAltitude(float& vehicleAltitude); //where do we get altitude from?
};


#endif // SIMULATEDGPS_H

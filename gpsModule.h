#ifndef GPSMODULE_H
#define GPSMODULE_H

#include "types.h"
#include "module.h"

class GPSModule: public Module {
public:
    virtual      ~GPSModule() {}
    virtual bool getCurrentLatitude(float& vehicleLat) = 0;
    virtual bool getCurrentLongitude(float& vehicleLon) = 0;
    virtual bool getCurrentAltitude(float& vehicleAltitude) = 0;
};

#endif // GPSMODULE_H

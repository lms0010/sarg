#ifndef UAVMODULE_H
#define UAVMODULE_H

#include "module.h"
#include <vector>

#define SOFTWARE_MODULES true

class Body;
class Waypoint;
class RadarModule;
class GPSModule;
class FailSafeModule;
class ADSBModule;
class WaypointModule;

class UAVModule: public Module {
private:
    std::vector<Body*>      _bodies;
    std::vector<Waypoint*>  _waypoints;

    RadarModule*            _radar;
    GPSModule*              _gps;
    FailSafeModule*         _stop;
    WaypointModule*         _waypoint;
    ADSBModule*             _adsb;

public:

                        UAVModule();
                        ~UAVModule();

    virtual bool        initialize();
    virtual bool        uninitialize();
    virtual bool        update();
    virtual const char* getLastError();

};

#endif // UAVMODULE_H

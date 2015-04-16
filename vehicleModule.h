#ifndef vehicleMODULE_H
#define vehicleMODULE_H

#include "module.h"
#include <vector>

//#define SOFTWARE_MODULES true

class ObstacleDistance;
//class Waypoint;
class RadarModule;
class AutopilotModule;
class ADSBModule;


class vehicleModule: public Module {
private:
    std::vector<ObstacleDistance*>      _obstacleDistances;
   // std::vector<Waypoint*>              _waypoints;

    RadarModule*            _radar;
    AutopilotModule*        _autopilot;
    ADSBModule*             _adsb;

public:

                        vehicleModule();
                        ~vehicleModule();

    virtual bool        initialize();
    virtual bool        uninitialize();
    virtual bool        update();
    virtual const char* getLastError();

};

#endif // vehicleMODULE_H

#ifndef WAYPOINTMODULE_H
#define WAYPOINTMODULE_H

#include "types.h"
#include "module.h"

class WaypointModule: public Module {
public:
    virtual     ~WaypointModule() {}
    virtual bool getNextWaypoint(Waypoint& point) = 0;
    virtual bool setObstructedWaypoint(const Waypoint& point) = 0;

};

#endif // WAYPOINTMODULE_H

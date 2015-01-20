#ifndef SIMULATEDWAYPOINTS_H
#define SIMULATEDWAYPOINTS_H

#include "waypointModule.h"

class SimulatedWaypoints: public WaypointModule {
public:
    virtual         ~SimulatedWaypoints();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();

    virtual bool    getNextWaypoint(Waypoint& point);
    virtual bool    setObstructedWaypoint(const Waypoint& point);

};

#endif // SIMULATEDWAYPOINTS_H

#ifndef REALWAYPOINTS_H
#define REALWAYPOINTS_H

#include "waypointModule.h"

class RealWaypoints: public WaypointModule {
public:
    virtual         ~RealWaypoints();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();

    virtual bool    getNextWaypoint(Waypoint& point);
    virtual bool    setObstructedWaypoint(const Waypoint& point);

};

#endif // REALWAYPOINTS_H

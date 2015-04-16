#ifndef AUTOPILOTMODULE_H
#define AUTOPILOTMODULE_H

#include "module.h"

class AutopilotModule: public Module {
public:
    virtual      ~AutopilotModule() {}
    virtual bool getDriveCommand(char** driveCommand) = 0;
    virtual bool getWaypoints(char** waypointsCommand) = 0;
    virtual bool getVehicleLatitude(float& vehicleLat) = 0;
    virtual bool getVehicleLongitude(float& vehicleLon) = 0;
    virtual bool getVehicleAltitude(float& vehicleAltitude) = 0;
    virtual bool getVehicleTrack(float& vehicleTrack) = 0;
};

#endif // AUTOPILOTMODULE_H

#ifndef SIMULATEDAUTOPILOT_H
#define SIMULATEDAUTOPILOT_H

#include "autopilotModule.h"

class SimulatedAutopilot: public AutopilotModule {
 public:
    virtual         ~SimulatedAutopilot();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool getDriveCommand(char** driveCommand);
    virtual bool getWaypoints(char** waypointsCommand);
    virtual bool getVehicleLatitude(float& vehicleLat);
    virtual bool getVehicleLongitude(float& vehicleLon);
    virtual bool getVehicleAltitude(float& vehicleAltitude);
    virtual bool getVehicleTrack(float& vehicleTrack);
};


#endif // SIMULATEDAUTOPILOT_H

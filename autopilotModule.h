#ifndef AUTOPILOTMODULE_H
#define AUTOPILOTMODULE_H

#include "module.h"
#include <vector>

class AutopilotModule: public Module {
public:
    virtual      ~AutopilotModule() {}
    virtual bool getDriveCommand(char** driveCommand) = 0;
    virtual bool getWaypoints(char** waypointsCommand) = 0;
    virtual bool getVehicleLatitude(float& vehicleLat) = 0;
    virtual bool getVehicleLongitude(float& vehicleLon) = 0;
    virtual bool getVehicleAltitude(float& vehicleAltitude) = 0;
    virtual bool getVehicleTrack(float& vehicleTrack) = 0;


    struct SimulatedWaypoints
    {
       float lat, lon;
       SimulatedWaypoints(): lat(0.0f), lon(0.0f){
       }

    };

  virtual bool getSimulatedWaypoints(std::vector<std::vector<SimulatedWaypoints> >*& paths)=0;
protected:
    std::vector<std::vector<SimulatedWaypoints> > simulatedPaths;

};

#endif // AUTOPILOTMODULE_H

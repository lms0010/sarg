#include "simulatedAutopilot.h"
#include <vector>


SimulatedAutopilot::~SimulatedAutopilot() {}
bool    SimulatedAutopilot::update() { return true; }
char*   SimulatedAutopilot::getLastError() { return 0; }
bool    SimulatedAutopilot::initialize() {
    std::vector<SimulatedWaypoints> path;
    SimulatedWaypoints waypoint;

    waypoint.lat = 35.1267;
    waypoint.lon = -85.8640;

    path.push_back(waypoint);
    simulatedPaths.push_back(path);

    waypoint.lat = 35.1250;
    waypoint.lon = -85.855;

    path.clear();
    path.push_back(waypoint);
    simulatedPaths.push_back(path);

    waypoint.lat = 35.255;
    waypoint.lon = -86.012;

    path.clear();
    path.push_back(waypoint);
    simulatedPaths.push_back(path);
    return true;
}
bool    SimulatedAutopilot::uninitialize() { return true; }

bool    SimulatedAutopilot::getDriveCommand(char** driveCommand){
    return true;
}
bool    SimulatedAutopilot::getWaypoints(char** waypointsCommand){
    return true;
}

bool    SimulatedAutopilot::getVehicleLatitude(float& vehicleLat){
   //vehicleLat = 35.125600; //for go west result
   // vehicleLat = 35.14560; //for go east result,  no east paths so enters fail safe
     vehicleLat = 35.1731; //for go north result
    //vehicleLat = 35.1724; //for go south result
    return true;
}

bool    SimulatedAutopilot::getVehicleLongitude(float& vehicleLon){
  // vehicleLon = -85.867000; //for go west result
  //  vehicleLon = -85.8532; //for go east result,  no east paths so enters fail safe
     vehicleLon = -85.85376; //for go north result
   // vehicleLon = -85.84485; //for go south result
    return true;
}

bool    SimulatedAutopilot::getVehicleAltitude(float& vehicleAltitude){
    vehicleAltitude = 900.0;
    return true;
}

bool    SimulatedAutopilot::getVehicleTrack(float& vehicleTrack){
    vehicleTrack = 293.0;
    return true;
}

bool SimulatedAutopilot::getSimulatedWaypoints(std::vector<std::vector<SimulatedWaypoints> >*& paths){


    paths = &simulatedPaths;

    return true;
}

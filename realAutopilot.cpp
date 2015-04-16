#include "realAutopilot.h"

RealAutopilot::~RealAutopilot() {}

bool    RealAutopilot::update() { return true; }
char*   RealAutopilot::getLastError() { return 0; }
bool    RealAutopilot::initialize() { return true; }
bool    RealAutopilot::uninitialize() { return true; }

bool  RealAutopilot::getDriveCommand(char** driveCommand){

}
bool  RealAutopilot::getWaypoints(char** waypointsCommand){

}

bool  RealAutopilot::getVehicleLatitude(float& vehicleLat){
    vehicleLat = 0; //PUT COMMAND HERE TO RETRIEVE GPS LAT
    return true;
}

bool  RealAutopilot::getVehicleLongitude(float& vehicleLon){
    vehicleLon = 0; //PUT COMMAND HERE TO RETRIEVE GPS LON
    return true;
}

bool  RealAutopilot::getVehicleAltitude(float& vehicleAltitude){
    vehicleAltitude = 0; //PUT COMMAND HERE TO RETRIEVE GPS ALT
    return true;
}

bool  RealAutopilot::getVehicleTrack(float& vehicleTrack){

}


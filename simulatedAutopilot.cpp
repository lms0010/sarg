#include "simulatedAutopilot.h"

SimulatedAutopilot::~SimulatedAutopilot() {}
bool    SimulatedAutopilot::update() { return true; }
char*   SimulatedAutopilot::getLastError() { return 0; }
bool    SimulatedAutopilot::initialize() { return true; }
bool    SimulatedAutopilot::uninitialize() { return true; }

bool    SimulatedAutopilot::getDriveCommand(char** driveCommand){
    return true;
}
bool    SimulatedAutopilot::getWaypoints(char** waypointsCommand){
    return true;
}

bool    SimulatedAutopilot::getVehicleLatitude(float& vehicleLat){
    return true;
}

bool    SimulatedAutopilot::getVehicleLongitude(float& vehicleLon){
    return true;
}

bool    SimulatedAutopilot::getVehicleAltitude(float& vehicleAltitude){
    return true;
}

bool    SimulatedAutopilot::getVehicleTrack(float& vehicleTrack){
    return true;
}

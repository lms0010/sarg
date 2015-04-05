#include "simulatedGPS.h"

SimulatedGPS::~SimulatedGPS() {}
bool    SimulatedGPS::update() { return true; }
char*   SimulatedGPS::getLastError() { return 0; }
bool    SimulatedGPS::initialize() { return true; }
bool    SimulatedGPS::uninitialize() { return true; }
bool    SimulatedGPS::getCurrentLatitude(float& vehicleLat) { return true; }
bool    SimulatedGPS::getCurrentLongitude(float& vehicleLon) { return true; }
bool    SimulatedGPS::getCurrentAltitude(float& vehicleAltitude) { return true; }//where do we get altitude from?

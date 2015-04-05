#include "realGPS.h"

RealGPS::~RealGPS() {}

bool    RealGPS::update() { return true; }
char*   RealGPS::getLastError() { return 0; }
bool    RealGPS::initialize() { return true; }
bool    RealGPS::uninitialize() { return true; }
bool    RealGPS::getCurrentLatitude(float& vehicleLat) {
    vehicleLat = 0; //PUT COMMAND HERE TO RETRIEVE GPS LAT
    return true;
}
bool    RealGPS::getCurrentLongitude(float& vehicleLon) {
    vehicleLon = 0; //PUT COMMAND HERE TO RETRIEVE GPS LON
    return true;
}
bool    RealGPS::getCurrentAltitude(float& vehicleAltitude) {
    vehicleAltitude = 0; //PUT COMMAND HERE TO RETRIEVE GPS ALT??? where do we get altitude of vehicle, ground level
    return true;
}//where do we get altitude from?

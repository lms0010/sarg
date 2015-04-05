#include "vehicleModule.h"
#include <cmath>

#ifdef SOFTWARE_MODULES
#   include "simulatedRadar.h"
#   include "simulatedGPS.h"
#   include "simulatedDrive.h"
#   include "simulatedWaypoints.h"
#   include "simulatedADSB.h"
#else
#   include "realRadar.h"
#   include "realGPS.h"
#   include "realDrive.h"
#   include "realWaypoints.h"
#   include "realADSB.h"
#endif

vehicleModule::vehicleModule() {
    //Allocate and initialize modules, depending on whether you wish to use software or actual modules

#ifdef SOFTWARE_MODULES
    _radar          = new SimulatedRadar;
    _gps            = new SimulatedGPS;
    _stop           = new SimulatedDrive;
    _waypoint       = new SimulatedWaypoints;
    _adsb           = new SimulatedADSB;

#else

    _radar          = new RealRadar;
    _gps            = new RealGPS;
    _stop           = new RealDrive;
    _waypoint       = new RealWaypoints;
    _adsb           = new RealADSB;

#endif

}

vehicleModule::~vehicleModule() {
    delete _radar;
    delete _gps;
    delete _stop;
    delete _waypoint;
    delete _adsb;
}

bool vehicleModule::initialize() {
    bool success = true;

    success &= _radar->initialize();
    success &= _gps->initialize();
    success &= _stop->initialize();
    success &= _waypoint->initialize();
    success &= _adsb->initialize();

    return success;
}

bool vehicleModule::uninitialize() {
    bool success = true;

    success &= _radar->uninitialize();
    success &= _gps->uninitialize();
    success &= _stop->uninitialize();
    success &= _waypoint->uninitialize();
    success &= _adsb->uninitialize();

    return success;
}

bool vehicleModule::update() {
    bool success = true;

    success &= _radar->update();
    success &= _gps->update();
    success &= _stop->update();
    success &= _waypoint->update();
    success &= _adsb->update();

    //ENTER COLLISION AVOIDANCE ALGORITHM*****************

    //OBJECT AVOIDANCE BASED ON RADAR HERE





    //AIRCRAFT AVOIDANCE SECTION
    int earthRadiusMiles        = 3959;
    float degrees_to_radians    = M_PI/180.0;
    float radians_to_degrees    = 180.0/M_PI;

    float x;
    float y;
    int numObjects;
    float track;
    float groundSpeed;

    _adsb->getObjectCount(numObjects);

    for(int i; i<numObjects; i++){
        _adsb->getTrack(i, track);
        _adsb->getTrack(i, groundSpeed);

        //direction unit vector for aircraft track
        x=cos(track);
        y=sin(track);

        //displacement vector (direction vector * magnitude)
       // x = x * groundSpeed * timeStamp;
        //y = y * groundSpeed * timeStamp ;

        //convert displacement vector to lat and long

       // lat = (y/earthRadiusMiles)*(radians_to_degrees);
         //radius of a circle around the earth at given lat
        // r = earthRadiusMiles*cos(Lat*degrees_to_radians);
        // lon = (x/r)*radians_to_degrees;

        //add position + displacement vector



    }








    return success;
}

const char* vehicleModule::getLastError() {
    return "ALL GOOD! :D";
}

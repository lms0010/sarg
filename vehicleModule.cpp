#include "vehicleModule.h"

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

    return success;
}

const char* vehicleModule::getLastError() {
    return "ALL GOOD! :D";
}

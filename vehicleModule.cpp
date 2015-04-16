#include "vehicleModule.h"
#include <cmath>

#ifdef SOFTWARE_MODULES
#   include "simulatedRadar.h"
#   include "simulatedAutopilot.h"
#   include "simulatedADSB.h"
#else
#   include "realRadar.h"
#   include "realAutopilot.h"
#   include "realADSB.h"
#endif

vehicleModule::vehicleModule() {
    //Allocate and initialize modules, depending on whether you wish to use software or actual modules

#ifdef SOFTWARE_MODULES
    _radar          = new SimulatedRadar;
    _autopilot      = new SimulatedAutopilot;
    _adsb           = new SimulatedADSB;

#else

    _radar          = new RealRadar;
    _autopilot      = new RealAutopilot;
    _adsb           = new RealADSB;

#endif

}

vehicleModule::~vehicleModule() {
    delete _radar;
    delete _autopilot;
    delete _adsb;
}

bool vehicleModule::initialize() {
    bool success = true;

    success &= _radar->initialize();
    success &= _autopilot->initialize();
    success &= _adsb->initialize();

    return success;
}

bool vehicleModule::uninitialize() {
    bool success = true;

    success &= _radar->uninitialize();
    success &= _autopilot->uninitialize();
    success &= _adsb->uninitialize();

    return success;
}

bool vehicleModule::update() {
    bool success = true;

    success &= _radar->update();
    success &= _autopilot->update();
    success &= _adsb->update();
#if 0
    //ENTER COLLISION AVOIDANCE ALGORITHM*****************

    //OBJECT AVOIDANCE BASED ON RADAR HERE






    //AIRCRAFT AVOIDANCE SECTION**************
    int earthRadiusMiles        = 3959;
    float degrees_to_radians    = M_PI/180.0;
    float radians_to_degrees    = 180.0/M_PI;
    float x, y;
    int numObjects;
    float aircraftTrack, aircraftGroundSpeed, aircraftLat, aircraftLon, aircraftAltitude;
    float mphConversion;
    const float knots_to_mph       = 1.15078;
    long int timeStamp =0;
    float displacementLat, displacementLon, r;
    float vehicleLat, vehicleLon, vehicleAltitude;
    float projectedAircraftLat,projectedAircraftLon;

    float r2;

    //convert 5 mile lateral min distance to lat
      const float minDistLat = (y/earthRadiusMiles)*(radians_to_degrees);
      //convert 5 mile lateral min distance to lon
      r2 = earthRadiusMiles*cos(minDistLat*degrees_to_radians);
      const float minDistLon = (x/r2)*radians_to_degrees;


    _adsb->getObjectCount(numObjects);

    for(int i; i<numObjects; i++){
        _adsb->getTrack(i, aircraftTrack);
        _adsb->getGroundSpeed(i, aircraftGroundSpeed);
        _adsb->getLatitude(i, aircraftLat);
        _adsb->getLongitude(i, aircraftLon);
        _adsb->getAltitude(i, aircraftAltitude);
        mphConversion = aircraftGroundSpeed*knots_to_mph;

        //direction unit vector for aircraft track
        x=cos(aircraftTrack);
        y=sin(aircraftTrack);

        //displacement vector (direction vector * magnitude)
          x = x * aircraftGroundSpeed * timeStamp;//FIX TIMESTAMP*****//GROUNDSPEED IS IN MPH,TIME needs to be converted to hours
          y = y * aircraftGroundSpeed * timeStamp;

        //convert displacement vector to lat and long
          displacementLat = (y/earthRadiusMiles)*(radians_to_degrees);
         //radius of a circle around the earth at given lat
          r = earthRadiusMiles*cos(displacementLat*degrees_to_radians);
          displacementLon = (x/r)*radians_to_degrees;

        //add current aircraft position (lat and lon) + displacement vector to get projected aircraft location
          projectedAircraftLat=aircraftLat + displacementLat;
          projectedAircraftLon=aircraftLon + displacementLon;

          _gps->getCurrentLatitude(vehicleLat);
          _gps->getCurrentLongitude(vehicleLon);
          _gps->getCurrentAltitude(vehicleAltitude); //can't project so area of uncertainty will be larger than for lat and lon


          float altDifference;
          const int minAltDistance = 2000;

          if(altDifference <= minAltDistance){
              if(((std::abs(projectedAircraftLat-vehicleLat)) <= minDistLat) && ((std::abs(projectedAircraftLon-vehicleLon) <= minDistLon))){
                  int latDist = projectedAircraftLat - vehicleLat;
                  int lonDist = projectedAircraftLon - vehicleLon;
                  bool collideOnLon;

                  if(std::abs(lonDist) <= std::abs(latDist))
                      collideOnLon = true;
                  else
                      collideOnLon = false;

                  if(collideOnLon){
                      if(lonDist > 0) //go west, stop, load new path, look at 1st waypoint of new path and see if it NW,SW,OR W then take it
                          lonDist=0; //***CHANGE THIS
                          //_waypoint->getNewPath();
                          //_waypoint->getNextWaypoint();
                          //if (waypointLon <= 0)
                             // _drive->getGotoNewPath(waypoint);
                          else// else go east,ne,se
                           lonDist=1; //***CHANGE THIS
                          //_waypoint->getNewPath();
                          //_waypoint->getNextWaypoint();
                          //if (waypointLon >= 0)
                             // _drive->getGotoNewPath(waypoint);
                  }
                  else {
                      if(latDist > 0) //go south
                          latDist=0; //***CHANGE THIS
                          else//else go north
                          latDist=1; //*****CHANGE THIS
                  }

              }

          }
    }
#endif

    return success;
}

const char* vehicleModule::getLastError() {
    return "ALL GOOD! :D";
}

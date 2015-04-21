#include "vehicleModule.h"
#include <cmath>
#include <iostream>
using namespace std;




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
#if 1
    //ENTER COLLISION AVOIDANCE ALGORITHM*****************

    //OBJECT AVOIDANCE BASED ON RADAR HERE






    //AIRCRAFT AVOIDANCE SECTION**************
    int earthRadiusMiles        = 3959;
    float degrees_to_radians    = M_PI/180.0;
    float radians_to_degrees    = 180.0/M_PI;
    float x, y, displacementX, displacementY;
    int numObjects;
    float aircraftTrack, aircraftGroundSpeed, aircraftLat, aircraftLon, aircraftAltitude, timeStamp;
    const float knots_to_mph = 1.15077945; //1 knot = 1.15077945 mph
    float displacementLat, displacementLon, r;
    float vehicleLat, vehicleLon, vehicleAltitude;
    float aircraftGroundSpeedmph;
    float projectedAircraftLat,projectedAircraftLon;
   bool collideOnLon;
    float r2;
 bool foundPath=false;

    //convert 5 mile lateral min distance to lat
      const float minDistLat = (5.0/earthRadiusMiles)*(radians_to_degrees);
      //convert 5 mile lateral min distance to lon
      r2 = earthRadiusMiles*cos(minDistLat*degrees_to_radians);
      const float minDistLon = (5.0/r2)*radians_to_degrees;

    std::vector<std::vector<AutopilotModule::SimulatedWaypoints> >* paths;

    _adsb->getObjectCount(numObjects);

    for(int i=0; i<numObjects; i++){
        _adsb->getTrack(i, aircraftTrack);
        _adsb->getGroundSpeed(i, aircraftGroundSpeed);
        _adsb->getLatitude(i, aircraftLat);
        _adsb->getLongitude(i, aircraftLon);
        _adsb->getAltitude(i, aircraftAltitude);
        _adsb->getTimeStamp(i,timeStamp);

        cout<<endl<<"The current aircraft lat/lon position is: <"<< aircraftLat <<","<< aircraftLon <<">" <<endl;

        //direction unit vector for aircraft track
        x=cos(aircraftTrack);
        y=sin(aircraftTrack);

        cout<<"The aircraft direction unit vector is: <"<< x <<","<< y <<">" <<endl;

        //displacement vector (direction vector * magnitude)
         aircraftGroundSpeedmph = aircraftGroundSpeed *  knots_to_mph ; //convert knots to mph
          displacementX = x * aircraftGroundSpeedmph  * timeStamp;//FIX TIMESTAMP*****//GROUNDSPEED IS IN MPH,TIME needs to be converted to hours
          displacementY = y * aircraftGroundSpeedmph  * timeStamp;

            cout<<"The time since last aircraft message received is: "<< timeStamp <<" hours"<<endl;

           cout<<"The aircraft ground speed is: "<< aircraftGroundSpeedmph  <<" mph"<<endl;
          cout<<"The aircraft displacement vector is: <"<< displacementX <<","<< displacementY<<">"<<" miles" <<endl;

        //convert displacement vector to lat and long
          displacementLat = (displacementY/earthRadiusMiles)*(radians_to_degrees);

               //radius of a circle around the earth at given lat
          r = earthRadiusMiles*cos(displacementLat*degrees_to_radians);
          displacementLon = (displacementX/r)*radians_to_degrees;
            cout<<"The displacement vector in Latitude/Longitude is: <"<< displacementLat<<","<<displacementLon<<">"<< " degrees"  <<endl;

        //add current aircraft position (lat and lon) + displacement vector to get projected aircraft location
          projectedAircraftLat=aircraftLat + displacementLat;
          projectedAircraftLon=aircraftLon + displacementLon;

          cout<<"The projected aircraft latitude/longitude is : <"<< projectedAircraftLat<<","<< projectedAircraftLon<<">" <<endl;

          _autopilot->getVehicleLatitude(vehicleLat);
           _autopilot->getVehicleLongitude(vehicleLon);
           _autopilot->getVehicleAltitude(vehicleAltitude); //can't project so area of uncertainty will be larger than for lat and lon

           cout<<"The value of vehicle latitude/longitude is : <"<< vehicleLat<<","<<vehicleLon <<">"<<endl;
          float altDifference, latDifference, lonDifference;
          const int minAltDistance = 1000;

          altDifference = std::abs(aircraftAltitude - vehicleAltitude);

         latDifference = projectedAircraftLat-vehicleLat;
         lonDifference = projectedAircraftLon-vehicleLon;
          cout<<"The altitude difference of aircraft and vehicle is "<<altDifference<<" ft"<<endl;

          if(altDifference <= minAltDistance){

                 cout<<"Aircraft detected within 1000 ft"<<endl;
                 cout<<"Lat/Lon position difference between aircraft and vehicle is: <"<< latDifference<<","<<lonDifference<<">"<<endl;
                 cout<<"Min distance Lat/Lon is: <"<< minDistLat<<","<<minDistLon<<">"<<endl;

              if((std::abs(latDifference)<= minDistLat) && (std::abs(lonDifference)<= minDistLon)){

                  cout<<"Aircraft detected within 5 miles"<<endl;

                  if(std::abs(lonDifference)<= std::abs(latDifference)){
                      collideOnLon = true;
                      cout<<"Increased potential for collision on longitudinal direction"<<endl;
                  }
                  else{
                      collideOnLon = false;
                      cout<<"Increased potential for collision on latitudinal direction"<<endl;
                  }

                  if(collideOnLon){
                      if(lonDifference > 0) {//go west, stop, load new path, look at 1st waypoint of new path and see if it NW,SW,OR W then take it
                         cout<<"Go west"<<endl;
                         _autopilot->getSimulatedWaypoints(paths);

                         cout<<"Inspecting the first waypoints from each path"<<endl;
                        for(int i=0; i< paths->size(); i++){
                            float firstWaypointLat=(*paths)[i][0].lat;
                            float firstWaypointLon=(*paths)[i][0].lon;

                            cout<<"  Current Path Index "<<i<<endl;
                            cout<<"    Waypoint lat/lon <"<<firstWaypointLat<<","<<">"<<firstWaypointLon<<endl;
                            cout<<"    Waypoint longitudinal distance relative to vehicle: "<<firstWaypointLon-vehicleLon<<endl;
                            if(firstWaypointLon-vehicleLon < 0.0f){
                                cout<<"  Found Safe Waypoint From Paths"<<endl;
                                cout<<"  Load Path Index "<<i<<". Go to Waypoint, lat/lon: <"<<firstWaypointLat<<","<<">"<<firstWaypointLon<<endl;
                                foundPath=true;
                                break;
                             }
                            else
                                cout<<"    Unsafe Waypoint"<<endl;
                         }
                         if(!foundPath)
                             cout<<"No safe paths available, enter fail safe mode: land vehicle"<<endl;
                           }
                          else {// else go east,ne,se
                            cout<<"Go east"<<endl;
                            _autopilot->getSimulatedWaypoints(paths);

                             cout<<"Inspecting the first waypoints from each path"<<endl;
                            for(int i=0; i< paths->size(); i++){
                                float firstWaypointLat=(*paths)[i][0].lat;
                                float firstWaypointLon=(*paths)[i][0].lon;

                                cout<<"  Current Path Index "<<i<<endl;
                                cout<<"    Waypoint lat/lon <"<<firstWaypointLat<<","<<firstWaypointLon<<">"<<endl;
                                cout<<"    Waypoint longitudinal distance relative to vehicle: "<<firstWaypointLon-vehicleLon<<endl;
                                if(firstWaypointLon-vehicleLon > 0.0f){
                                    cout<<"  Found Safe Waypoint From Paths"<<endl;
                                    cout<<"  Load Path Index "<<i<<". Go to Waypoint, lat/lon: <"<<firstWaypointLat<<","<<firstWaypointLon<<">"<<endl;
                                    foundPath=true;
                                    break;
                                }
                                else
                                    cout<<"    Unsafe Waypoint"<<endl;
                            }
                            if(!foundPath)
                                cout<<"No safe paths available, enter fail safe mode: land vehicle"<<endl;
                          }
                  }//end collideOnLon
                  else {

                      if(latDifference > 0) //(closer to north, go south)
                      {
                          cout<<"Go south"<<endl;
                          _autopilot->getSimulatedWaypoints(paths);

                           cout<<"Inspecting the first waypoints from each path"<<endl;
                          for(int i=0; i< paths->size(); i++){
                              float firstWaypointLat=(*paths)[i][0].lat;
                              float firstWaypointLon=(*paths)[i][0].lon;

                              cout<<"  Current Path Index "<<i<<endl;
                              cout<<"    Waypoint lat/lon <"<<firstWaypointLat<<","<<firstWaypointLon<<">"<<endl;
                              cout<<"    Waypoint latitudinal distance relative to vehicle: "<<firstWaypointLat-vehicleLat<<endl;
                              if(firstWaypointLat-vehicleLat < 0.0f){
                                  cout<<"  Found Safe Waypoint From Paths"<<endl;
                                  cout<<"  Load Path Index "<<i<<". Go to Waypoint, lat/lon: <"<<firstWaypointLat<<","<<firstWaypointLon<<">"<<endl;
                                  foundPath=true;
                                  break;
                              }
                              else
                                  cout<<"    Unsafe Waypoint"<<endl;

                          }
                          if(!foundPath)
                              cout<<"No safe paths available, enter fail safe mode: land vehicle"<<endl;
                      }
                      else//else go north
                      {
                          cout<<"Go north"<<endl;
                          _autopilot->getSimulatedWaypoints(paths);
                           cout<<"Inspecting the first waypoints from each path"<<endl;
                          for(int i=0; i< paths->size(); i++){
                              float firstWaypointLat=(*paths)[i][0].lat;
                              float firstWaypointLon=(*paths)[i][0].lon;

                              cout<<"  Current Path Index "<<i<<endl;
                              cout<<"    Waypoint lat/lon <"<<firstWaypointLat<<","<<firstWaypointLon<<">"<<endl;
                              cout<<"    Waypoint latitudinal distance relative to vehicle: "<<firstWaypointLat-vehicleLat<<endl;
                              if(firstWaypointLat-vehicleLat > 0.0f){
                                  cout<<"  Found Safe Waypoint From Paths"<<endl;
                                  cout<<"  Load Path Index "<<i<<". Go to Waypoint, lat/lon: <"<<firstWaypointLat<<","<<firstWaypointLon<<">"<<endl;
                                  foundPath=true;
                                  break;
                              }
                              else
                                  cout<<"    Unsafe Waypoint"<<endl;

                          }
                          if(!foundPath)
                              cout<<"No safe paths available, enter fail safe mode: land vehicle"<<endl;
                      }
                  }//end collideOnLat
                  //fail safe mode for no safe paths, //stop?hover in current location until plane out of warning if in close altitude...if airplane altitude is above then land vehicle??,

              }

          }
    }
#endif

    return success;
}

const char* vehicleModule::getLastError() {
    return "ALL GOOD! :D";
}

#include "simulatedADSB.h"

SimulatedADSB::~SimulatedADSB() {}
bool    SimulatedADSB::update() { return true; }
char*   SimulatedADSB::getLastError() { return 0; }
bool    SimulatedADSB::initialize() { return true; }
bool    SimulatedADSB::uninitialize() { return true; }

bool    SimulatedADSB::getObjectCount(int& numObjects) {
    numObjects = 1;
   return true; }
bool    SimulatedADSB::getHexIdent(int index, char** hexIdent) {
    *hexIdent = "A34BCA";
    return true; }
bool    SimulatedADSB::getAltitude(int index, float& altitude) {
    altitude = 800.50;
    return true; }
bool    SimulatedADSB::getGroundSpeed(int index, float& groundSpeed){
    groundSpeed = 40.06;
    return true; }
bool    SimulatedADSB::getLatitude(int index, float& latitude) {
    latitude = 35.173479;
    return true; }
bool    SimulatedADSB::getLongitude(int index, float& longitude) {
    longitude = -85.863097;
    return true; }
bool    SimulatedADSB::getTrack(int index, float& track) {
    track = 244;
    return true; }
bool    SimulatedADSB::getCallSign(int index, char** callSign){
    *callSign = "VRD721";
     return  true;}
bool    SimulatedADSB::getTimeStamp(int index, float& timeStamp) {
    timeStamp = 0.00138889; //5 secs in hours
    return true; }

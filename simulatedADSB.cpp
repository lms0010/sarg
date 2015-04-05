#include "simulatedADSB.h"

SimulatedADSB::~SimulatedADSB() {}
bool    SimulatedADSB::update() { return true; }
char*   SimulatedADSB::getLastError() { return 0; }
bool    SimulatedADSB::initialize() { return true; }
bool    SimulatedADSB::uninitialize() { return true; }

bool    SimulatedADSB::getObjectCount(int& numObjects) { return true; }
bool    SimulatedADSB::getHexIdent(int index, char** hexIdent) { return true; }
bool    SimulatedADSB::getAltitude(int index, float& altitude) { return true; }
bool    SimulatedADSB::getGroundSpeed(int index, float& groundSpeed){ return true; }
bool    SimulatedADSB::getLatitude(int index, float& latitude) { return true; }
bool    SimulatedADSB::getLongitude(int index, float& longitude) { return true; }
bool    SimulatedADSB::getTrack(int index, float& track) { return true; }
bool    SimulatedADSB::getTimeStamp(int index, int& timeStamp) { return true; }

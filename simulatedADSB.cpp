#include "simulatedADSB.h"

SimulatedADSB::~SimulatedADSB() {}
bool    SimulatedADSB::update() { return true; }
char*   SimulatedADSB::getLastError() { return 0; }
bool    SimulatedADSB::initialize() { return true; }
bool    SimulatedADSB::uninitialize() { return true; }


bool    SimulatedADSB::getHexIdent(char** hexIdent) { return true; }
bool    SimulatedADSB::getFlightID(int& flightID) { return true; }
bool    SimulatedADSB::getAltitude(float& altitude) { return true; }
bool    SimulatedADSB::getGroundSpeed(int& groundSpeed) { return true; }
bool    SimulatedADSB::getLatitude(float& lat) { return true; }
bool    SimulatedADSB::getLongitude(float& lon) { return true; }
bool    SimulatedADSB::getTrack(int& track) { return true; }
bool    SimulatedADSB::getDeltaTime(int& deltaTime) { return true; }


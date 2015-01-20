#include "realADSB.h"

RealADSB::~RealADSB() {}

bool    RealADSB::update() { return true; }
char*   RealADSB::getLastError() { return 0; }
bool    RealADSB::initialize() { return true; }
bool    RealADSB::uninitialize() { return true; }

bool    RealADSB::getMessageType(char** messageType) { return true; }
bool    RealADSB::getTransmissionType(int& transType) { return true; }
bool    RealADSB::getHexIdent(char** hexIdent) { return true; }
bool    RealADSB::getFlightID(int& flightID) { return true; }
bool    RealADSB::getAltitude(int& altitude) { return true; }
bool    RealADSB::getGroundSpeed(int& groundSpeed) { return true; }
bool    RealADSB::getLatitude(float& lat) { return true; }
bool    RealADSB::getLongitude(float& lon) { return true; }
bool    RealADSB::getTrack(int& track) { return true; }
bool    RealADSB::getDeltaTime(int& deltaTime) { return true; }


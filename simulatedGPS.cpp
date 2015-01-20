#include "simulatedGPS.h"

SimulatedGPS::~SimulatedGPS() {}
bool    SimulatedGPS::update() { return true; }
char*   SimulatedGPS::getLastError() { return 0; }
bool    SimulatedGPS::initialize() { return true; }
bool    SimulatedGPS::uninitialize() { return true; }
bool    SimulatedGPS::getPos3(Vector3& pos) { return true; }

#include "simulatedDrive.h"

SimulatedDrive::~SimulatedDrive() {}

bool    SimulatedDrive::update() { return true; }
char*   SimulatedDrive::getLastError() { return 0; }
bool    SimulatedDrive::initialize() { return true; }
bool    SimulatedDrive::uninitialize() { return true; }
bool    SimulatedDrive::stop() { return true; }

#include "simulatedRadar.h"

SimulatedRadar::~SimulatedRadar() {}
bool    SimulatedRadar::update() { return true; }
char*   SimulatedRadar::getLastError() { return 0; }
bool    SimulatedRadar::initialize() { return true; }
bool    SimulatedRadar::uninitialize() { return true; }
bool    SimulatedRadar::getNext(ObstacleDistance& obstacleDistance) { return true; }

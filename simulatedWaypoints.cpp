#include "simulatedWaypoints.h"

SimulatedWaypoints::~SimulatedWaypoints() {}

bool    SimulatedWaypoints::update() { return true; }
char*   SimulatedWaypoints::getLastError() { return 0; }
bool    SimulatedWaypoints::initialize() { return true; }
bool    SimulatedWaypoints::uninitialize() { return true; }

bool    SimulatedWaypoints::getNextWaypoint(Waypoint& point) { return true; }
bool    SimulatedWaypoints::setObstructedWaypoint(const Waypoint& point) { return true; }

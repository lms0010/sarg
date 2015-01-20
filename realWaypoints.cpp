#include "realWaypoints.h"

RealWaypoints::~RealWaypoints() {}

bool    RealWaypoints::update() { return true; }
char*   RealWaypoints::getLastError() { return 0; }
bool    RealWaypoints::initialize() { return true; }
bool    RealWaypoints::uninitialize() { return true; }

bool    RealWaypoints::getNextWaypoint(Waypoint& point) { return true; }
bool    RealWaypoints::setObstructedWaypoint(const Waypoint& point) { return true; }


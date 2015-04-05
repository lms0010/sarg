#include "realGPS.h"

RealGPS::~RealGPS() {}

bool    RealGPS::update() { return true; }
char*   RealGPS::getLastError() { return 0; }
bool    RealGPS::initialize() { return true; }
bool    RealGPS::uninitialize() { return true; }
bool    RealGPS::getPos3(Vector3& pos) { return true; }


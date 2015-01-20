#include "realRadar.h"

RealRadar::~RealRadar() { }
bool    RealRadar::update() { return true; }
char*   RealRadar::getLastError() { return 0; }
bool    RealRadar::initialize() { return true; }
bool    RealRadar::uninitialize() { return true; }
bool    RealRadar::getNextBody(Body& body) { return true; }


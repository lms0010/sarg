#include "realDrive.h"

RealDrive::~RealDrive() {}

bool    RealDrive::update() { return true; }
char*   RealDrive::getLastError() { return 0; }
bool    RealDrive::initialize() { return true; }
bool    RealDrive::uninitialize() { return true; }
bool    RealDrive::stop() { return true; }


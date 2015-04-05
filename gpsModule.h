#ifndef GPSMODULE_H
#define GPSMODULE_H

#include "types.h"
#include "module.h"

class GPSModule: public Module {
public:
    virtual      ~GPSModule() {}
    virtual bool getPos3(Vector3& pos) = 0;

};

#endif // GPSMODULE_H

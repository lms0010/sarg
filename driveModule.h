#ifndef DRIVEMODULE_H
#define DRIVEMODULE_H

#include "module.h"

class FailSafeModule: public Module {
public:
    virtual      ~FailSafeModule() {}
    virtual bool stop() = 0;

};

#endif // DRIVEMODULE_H

#ifndef SIMULATEDDRIVE_H
#define SIMULATEDDRIVE_H

#include "driveModule.h"

class SimulatedDrive: public FailSafeModule {
public:
    virtual         ~SimulatedDrive();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool    stop();

};

#endif // SIMULATEDDRIVE_H

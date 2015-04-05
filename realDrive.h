#ifndef REALDRIVE_H
#define REALDRIVE_H

#include "driveModule.h"

class RealDrive: public FailSafeModule {
public:
    virtual         ~RealDrive();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool    stop();

};

#endif // REALDRIVE_H

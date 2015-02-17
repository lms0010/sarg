#ifndef REALRADAR_H
#define REALRADAR_H
#include <pthread.h>

#include "radarModule.h"

class RealRadar: public RadarModule {
 public:
    virtual         ~RealRadar();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool    getNextBody(Body& body);
    pthread_t       thread;
};

#endif // REALRADAR_H

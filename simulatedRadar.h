#ifndef SIMULATEDRADAR_H
#define SIMULATEDRADAR_H

#include "radarModule.h"

class SimulatedRadar: public RadarModule {
 public:
    virtual         ~SimulatedRadar();
    virtual bool    update();
    virtual char*   getLastError();
    virtual bool    initialize();
    virtual bool    uninitialize();
    virtual bool    getNext(double& obstacleDistance);
};

#endif // SIMULATEDRADAR_H

#ifndef RADARMODULE_H
#define RADARMODULE_H

#include "types.h"
#include "module.h"

class RadarModule: public Module {
public:
    virtual bool  getNext(ObstacleDistance& obstacleDistance) = 0;
    virtual      ~RadarModule() {}

};

#endif // RADARMODULE_H

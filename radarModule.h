#ifndef RADARMODULE_H
#define RADARMODULE_H

#include "types.h"
#include "module.h"
#include <vector>


class RadarModule: public Module {
public:
    virtual bool  getNext(ObstacleDistance& obstacleDistance) = 0;
    virtual      ~RadarModule() {}

protected:
    std::vector<float> obstacleDistances;
};

#endif // RADARMODULE_H

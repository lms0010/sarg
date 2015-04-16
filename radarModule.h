#ifndef RADARMODULE_H
#define RADARMODULE_H

#include "module.h"
#include <vector>


class RadarModule: public Module {
public:
    virtual bool  getNext(std::vector<double>*& vector) = 0;

    virtual      ~RadarModule() {}
protected:
    std::vector<double> obstacleDistances;

};

#endif // RADARMODULE_H

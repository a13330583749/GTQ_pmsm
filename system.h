#ifndef SYSTEM_H
#define SYSTEM_H

#include "PMSM_sim.h"

namespace PanJL{
class Plant: private PMSM, private sparse_inverter{

public:
    Plant(double vdc, double inv_c):sparse_inverter(vdc, inv_c){}
    std::vector<double> updata(std::vector<int>);
};
}

#endif
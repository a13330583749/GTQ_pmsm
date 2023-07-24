#ifndef SYSTEM_H
#define SYSTEM_H

#include "PMSM.h"
#include "inverter.h"
namespace PanJL{
class Plant: public PMSM, public sparse_inverter{

public:
    Plant(const double& vdc, const double& inv_c):sparse_inverter(vdc, inv_c){}
    Plant(const sparse_inverter rhs):sparse_inverter(rhs){}
    std::vector<double> updata(std::vector<int>, const double&);
    const double get_wr(){return state_varibles.wr;}
    void set_TL(const double& tl){TL = tl;}
};
}

#endif
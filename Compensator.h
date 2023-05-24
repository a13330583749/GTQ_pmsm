#ifndef COMPENSATOR_H
#define COMPENSATOR_H

#include <vector>
#include "PMSM.h"
#include "inverter.h"
namespace PanJL{
class Compensator: public PMSM, public sparse_inverter
{
public:
    double ele_pre;
    double wr_pre;
    double u0_pre;
    std::vector<double> Iabc_pre;
    const std::vector<double> get_Udq(const std::vector<int>& virtual_voltages, const double& ele_theta);

private:
    void Compensator_updata(const double& ele, const double& wr, const double& u0, const std::vector<int>& Iabc, const double& times);
    const double& get_ele_pre(){return ele_pre;};
    const double& get_wr_pre(){return wr_pre;};
    const double& get_u0_pre(){return u0_pre;};
    const std::vector<double>& get_Iabc_pre(){return Iabc_pre;};
};
}


#endif
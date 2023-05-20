#include "PMSM_sim.h"
namespace PanJL{
void sparse_inverter::set_igbt(const std::vector<int>& inputs)
{
    // 在这里可知u[1-5]代表的各个数值
    Sc1 = inputs[0];
    Sc2 = inputs[1];
    Sta = inputs[2];
    Stb = inputs[3];
    Stc = inputs[4];
}

double sparse_inverter::u0_differential_equation(const double& ia, const double& ib, const double& ic)
{
    return -1/(2*C) * ( (1-Sm(Sta)*Sm(Sta))*ia + (1-Sm(Stb)*Sm(Stb))*ib + (1-Sm(Stc)*Sm(Stc))*ic );
}

void sparse_inverter::updata_u0(const double& ia, const double& ib, const double& ic, const double& times)
{
    double du0 = u0_differential_equation(ia, ib, ic);
    u0 += du0 * times;   
}

}
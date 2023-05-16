#include "PMSM_sim.h"
namespace PanJL{
void sparse_inverter::set_igbt(const int& sc1, const int& sc2, const int& sta, const int& stb, const int& stc)
{
    Sc1 = sc1;
    Sc2 = sc2;
    Sta = sta;
    Stb = stb;
    Stc = stc;
}

double sparse_inverter::u0_differential_equation(const double& ia, const double& ib, const double& ic)
{
    return -1/(2*C) * ( (1-Sm(Sta)*Sm(Sta))*ia + (1-Sm(Stb)*Sm(Stb))*ib + (1-Sm(Stc)*Sm(Stc))*ic );
}

void sparse_inverter::updata_u0(const double& ia, const double& ib, const double& ic)
{
    double du0 = u0_differential_equation(ia, ib, ic);
    u0 += du0 * Ts;   
}

}
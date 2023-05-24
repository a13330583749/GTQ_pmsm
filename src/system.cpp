#include "../PMSM_sim.h"
namespace PanJL{
std::vector<double> Plant::updata(std::vector<int>inputs, const double& times)
{
    double ud, uq;
    set_igbt(inputs);
    auto ua = Uabc(get_Sta());
    auto ub = Uabc(get_Stb());
    auto uc = Uabc(get_Stc());
    auto ualpha = abc2alpha(ua, ub, uc);
    auto ubeta = abc2beta(ua, ub, uc);
    ud = alphabeta2d(ualpha, ubeta, get_ele_theta());
    uq = alphabeta2q(ualpha, ubeta, get_ele_theta());
    //逆变器在PMSM之前才不会相互影响
    auto Iabc = out_iabc();
    updata_u0(Iabc[0], Iabc[1], Iabc[2], times);
    ode45(ud, uq, times);
    return out_iabc();
}

}
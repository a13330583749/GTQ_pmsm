#include "../PMSM_sim.h"
namespace PanJL{
std::vector<double> Plant::updata(std::vector<int>inputs, const double& times)
{
    double ud, uq;
    auto Iabc = out_iabc();
    updata_u0(Iabc[0], Iabc[1], Iabc[2], times);
    set_igbt(inputs);
    auto ua = Uabc(get_Sta());
    auto ub = Uabc(get_Stb());
    auto uc = Uabc(get_Stc());
    auto u_u = abc2u(ua, ub, uc);
    auto u_v = abc2v(ua, ub, uc);
    auto u_w = abc2w(ua, ub, uc);
    auto ualpha = abc2alpha(u_u, u_v, u_w);
    auto ubeta = abc2beta(u_u, u_v, u_w);
    ud = alphabeta2d(ualpha, ubeta, get_ele_theta());
    uq = alphabeta2q(ualpha, ubeta, get_ele_theta());
    //逆变器在PMSM之前才不会相互影响
    
    
    ode45(ud, uq, times);
    return out_iabc();
}

}
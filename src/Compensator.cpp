#include "../PMSM_sim.h"
namespace PanJL
{
void Compensator::Compensator_updata(const double& ele, const double& wr, const double& u0, const std::vector<int>& Iabc, const double& times)
{
    u0_pre = u0_differential_equation(Iabc[0], Iabc[1], Iabc[2]) * times + u0;
    auto Udq = get_Udq()
}

const std::vector<double> Compensator::get_Udq(const std::vector<int>& virtual_voltages,const double& ele_theta)
{
    double ua = virtual_voltages[0] * Vdc / 2 - u0;
    double ub = virtual_voltages[1] * Vdc / 2 - u0;
    double uc = virtual_voltages[2] * Vdc / 2 - u0;
    auto ualpha = abc2alpha(ua, ub, uc);
    auto ubeta  = abc2beta (ua, ub, uc);
    return std::vector<double>{(ualpha, ubeta, ele_theta), alphabeta2q(ualpha, ubeta, ele_theta)};
}

}
#include "../PMSM_sim.h"
namespace PanJL{

struct PMSM_state_varibles PMSM::PMSM_differential_equation(double& ud, double& uq, 
                                               const struct PMSM_state_varibles& states) 
{
    struct PMSM_state_varibles result;
    result.Id = (-Rs * states.Id + states.wr * Pn * Lq  * states.Iq + ud)/ Ld;
    result.Iq = (-Rs * states.Iq - states.wr * Pn * Ld  * states.Id
                    - states.wr * Pn * F + uq)/Lq;
    result.wr = (1.5 * Pn * F * states.Iq - TL - Bm * states.wr) / J;
    result.theta_ele = Pn * states.wr;
    return result;
}   

void PMSM::ode45(double& ud, double& uq, const double& times)
{
    double DT = times/ ODE45_M;
    struct PMSM_state_varibles temp = state_varibles;
    for(int _=0; _< ODE45_M; _++){
        auto k1 = PMSM_differential_equation(ud, uq, temp);
        auto k2 = PMSM_differential_equation(ud, uq, temp + (k1 *(DT/2.0)) );
        auto k3 = PMSM_differential_equation(ud, uq, temp + (k2 *(DT/2.0)) );
        auto k4 = PMSM_differential_equation(ud, uq, temp + (k3 * DT) );
        temp = temp + (k1 + (k2 * 2) + (k3 * 2) + k4) * (DT / 6.0);
    }
    state_varibles = temp;
}


bool PMSM::init_PMSM(const double& ld, const double& lq, const double& f, const double& bm,
                    const double& rs, const double& tl, const int& pn, const double& j)
{
    Ld = ld;
    Lq = lq;
    F = f;
    Rs = rs;
    TL = tl;
    Pn =pn;
    J = j;
    Bm = bm;
    return 1;
}

const std::vector<double> PMSM::out_iabc()
{
    std::vector<double> Iabc(3);
    double Ialpha = dq2alpha(state_varibles.Id, state_varibles.Iq, state_varibles.theta_ele);
    double Ibeta  = dq2beta(state_varibles.Id, state_varibles.Iq, state_varibles.theta_ele);
    Iabc[0] = alphabeta2a(Ialpha, Ibeta);
    Iabc[1] = alphabeta2b(Ialpha, Ibeta);
    Iabc[2] = alphabeta2c(Ialpha, Ibeta);
    return Iabc;
}

void PMSM::set_state_PMSM(const double& id_, const double& iq_, const double& wr_, const double& theta_ele_)
{
    state_varibles.wr = wr_;
    state_varibles.Id = id_;
    state_varibles.Iq = iq_;
    state_varibles.theta_ele = theta_ele_;
}

std::vector<double> const PMSM::get_Iabc()
{
    double Ialpha = dq2alpha(state_varibles.Id, state_varibles.Iq, state_varibles.theta_ele);
    double Ibeta = dq2beta(state_varibles.Id, state_varibles.Iq, state_varibles.theta_ele);
    return std::vector<double>{alphabeta2a(Ialpha, Ibeta), alphabeta2b(Ialpha, Ibeta), alphabeta2c(Ialpha, Ibeta)};
}

void PMSM::set_parameter_pmsm(const double ld, const double lq, const double f, const double rs)
{
    Ld = ld;
    Lq = lq;
    F = f;
    Rs = rs;
}
}
#include "../PMSM_sim.h"
namespace PanJL{

struct PMSM_state_varibles PMSM_state_dvaribles::operator*(const double& samlpe_times)
{
    struct PMSM_state_varibles increments;
    increments.Id = dId * samlpe_times;
    increments.Iq = dIq * samlpe_times;
    increments.theta_ele = dtheta_ele * samlpe_times;
    increments.wr = dwr * samlpe_times;
    return increments;
}

struct PMSM_state_dvaribles& PMSM_state_dvaribles::operator*(const int& times)
{
    // struct PMSM_state_varibles increments;
    dId = dId * times;
    dIq = dIq * times;
    dtheta_ele = dtheta_ele * times;
    dwr = dwr * times;
    return *this;
}

struct PMSM_state_dvaribles& PMSM_state_dvaribles::operator+(const struct PMSM_state_dvaribles& rhs)
{
    dId += rhs.dId;
    dIq += rhs.dIq;
    dwr += rhs.dwr;
    dtheta_ele += rhs.dtheta_ele;
    return *this;
}

struct PMSM_state_varibles PMSM_state_varibles::operator+(const struct PMSM_state_varibles& rhs)
{
    struct PMSM_state_varibles result;    
    result.Id = rhs.Id + Id;
    result.Iq = rhs.Iq + Iq;
    result.wr = rhs.wr + wr;
    result.theta_ele = rhs.theta_ele + theta_ele;
    return result;
}

// void PMSM_state_varibles::incremental_updates(struct PMSM_state_varibles&& rhs)
// {
//     Id += rhs.Id;
//     Iq += rhs.Iq;
//     theta_ele += rhs.theta_ele;
//     wr += rhs.wr;
// }

struct PMSM_state_dvaribles PMSM::PMSM_differential_equation(double& ud, double& uq, 
                                               const struct PMSM_state_varibles& states) 
{
    struct PMSM_state_dvaribles result;
    result.dId = (-Rs * states.Id + states.wr * Pn * Lq + ud)/ Ld;
    result.dIq = (-Rs * states.Iq - states.wr * Pn * Ld 
                    - states.wr * Pn * F + uq)/Lq;
    result.dwr = (1.5 * Pn * F * states.Iq - TL - Bm * states.wr) / J;
    result.dtheta_ele = Pn * states.wr;
    return result;
}   

void PMSM::ode45(double& ud, double& uq, const double& times)
{
    double DT = times/ ODE45_M;
    struct PMSM_state_varibles& temp = state_varibles;
    for(int _=0; _< ODE45_M; _++){
        auto k1 = PMSM_differential_equation(ud, uq, temp);
        auto k2 = PMSM_differential_equation(ud, uq, temp + (k1 *(DT/2)) );
        auto k3 = PMSM_differential_equation(ud, uq, temp + (k2 *(DT/2)) );
        auto k4 = PMSM_differential_equation(ud, uq, temp + (k3 * DT) );
        temp = temp + (k1 + (k2 * 2) + (k3 * 2) + k4) * (DT / 6.0);
    }
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


z
}
#include "../PMSM_sim.h"
namespace PanJL
{
// void IRLS_parameter_identify::update(const std::vector<double>& Idq, const std::vector<double>& Udq,
//                         const double& we, const double& Ts)
    void Identifier::renew(const std::vector<double>& Iabc,const std::vector<int>&inputs, const double& Ts,
                 const double& we, const double& Vdc, const double&theta_ele)
    {
        std::vector<double> Idq_{};
        auto Ialpha = abc2alpha(Iabc[0], Iabc[1], Iabc[2]);
        auto Ibeta  = abc2beta(Iabc[0], Iabc[1], Iabc[2]);
        auto Id     = alphabeta2d(Ialpha, Ibeta, theta_ele);
        auto Iq     = alphabeta2q(Ialpha, Ibeta, theta_ele);
        Idq_.push_back(Id);
        Idq_.push_back(Iq);
        double Ua = inputs[0] * Vdc / 2;
        double Ub = inputs[1] * Vdc / 2;
        double Uc = inputs[2] * Vdc / 2;
        auto Uu = abc2u(Ua, Ub, Uc);
        auto Uv = abc2u(Ua, Ub, Uc);
        auto Uw = abc2u(Ua, Ub, Uc);
        auto Ualpha = abc2alpha(Uu, Uv, Uw);
        auto Ubeta  = abc2beta(Uu, Uv, Uw);
        auto Ud = alphabeta2d(Ualpha, Ubeta, theta_ele);
        auto Uq = alphabeta2q(Ualpha, Ubeta, theta_ele);
    }    
}
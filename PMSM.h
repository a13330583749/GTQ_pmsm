#ifndef PMSM_H
#define PMSM_H

#include <vector>
namespace PanJL{
struct PMSM_state_varibles
{
    double Id;
    double Iq;
    double wr;
    double theta_ele;
    //play a trick, the result is operator* of 'struct PMSM_state_dvaribles'
    struct PMSM_state_varibles operator+(const struct PMSM_state_varibles& rhs);
};

struct PMSM_state_dvaribles
{
    double dId;
    double dIq;
    double dwr;
    double dtheta_ele;
    struct PMSM_state_varibles operator*(const double& samlpe_times);
    struct PMSM_state_dvaribles& operator*(const int& times);
    struct PMSM_state_dvaribles& operator+(const struct PMSM_state_dvaribles&rhs);
};

class PMSM
{
private:
    double Lq;
    double Ld;
    double F; //电机磁链
    double Rs;

    double TL; //转矩
    // [Id; Iq; 转速; 电角度]
    struct PMSM_state_varibles state_varibles;    

    double J; //转动惯量
    double Pn; //极对数
    double Bm;
    struct PMSM_state_dvaribles PMSM_differential_equation(double& ud, double& uq, 
                         const   struct PMSM_state_varibles& states);
public:
    PMSM() = default;
    int init_PMSM(const double& ld, const double& lq, const double& f, const double& Bm,
                    const double& rs, const double& tl, const double& pn, const double& j);
    int set_state_PMSM(double id_, double iq_, double wr_, double theta_ele_);
    void ode45(double& ud, double& uq, const double& times);
    struct PMSM_state_varibles get_PMSM_state_varibles()  {return state_varibles;}
    const double& get_ele_theta(){return state_varibles.theta_ele;}
    const std::vector<double> out_iabc();
    const double& get_id(){return state_varibles.Id;}
    const double& get_iq(){return state_varibles.Iq;}
};
}
#endif
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
    // play a trick, the result is operator* of 'struct PMSM_state_dvaribles'
    // struct PMSM_state_varibles operator+(const struct PMSM_state_varibles& rhs);
    PMSM_state_varibles():wr(0){}


    PMSM_state_varibles operator+(const PMSM_state_varibles& rhs) const {
        PMSM_state_varibles result;
        result.Id = rhs.Id + Id;
        result.Iq = rhs.Iq + Iq;
        result.wr = rhs.wr + wr;
        result.theta_ele = rhs.theta_ele + theta_ele;
        return result;
    }

    PMSM_state_varibles operator*(const double& samlpe_times) const {
        PMSM_state_varibles increments;
        increments.Id = Id * samlpe_times;
        increments.Iq = Iq * samlpe_times;
        increments.theta_ele = theta_ele * samlpe_times;
        increments.wr = wr * samlpe_times;
        return increments;
    }
};

// struct PMSM_state_dvaribles
// {
//     double dId;
//     double dIq;
//     double dwr;
//     double dtheta_ele;
//     struct PMSM_state_varibles operator*(const double& samlpe_times);
//     struct PMSM_state_dvaribles operator*(const int& times);
//     const struct PMSM_state_dvaribles operator+(const struct PMSM_state_dvaribles&rhs);
// };

class PMSM
{
protected:
    double Lq;
    double Ld;
    double F; //电机磁链
    double Rs;

    double TL; //转矩
    // [Id; Iq; 转速; 电角度]
      

    double J; //转动惯量
    int Pn; //极对数
    double Bm;

protected:
    // struct PMSM_state_dvaribles PMSM_differential_equation(double& ud, double& uq, 
    //                 const struct PMSM_state_varibles& states);
    struct PMSM_state_varibles PMSM_differential_equation(double& ud, double& uq, 
                                            const struct PMSM_state_varibles& states);
    void ode45(double& ud, double& uq, const double& times);
    struct PMSM_state_varibles state_varibles;  
public:
    inline const double& get_id(){return state_varibles.Id;}
    inline const double& get_iq(){return state_varibles.Iq;}
    inline const double& get_wr(){return state_varibles.wr;}
    inline const double& get_ele_theta(){return state_varibles.theta_ele;}
    std::vector<double> const get_Iabc();

public:
    PMSM()= default;
    bool init_PMSM(const double& ld, const double& lq, const double& f, const double& Bm,
                    const double& rs, const double& tl, const int& pn, const double& j);
    void set_state_PMSM(const double& id_, const double& iq_, const double& wr_, const double& theta_ele_);
    void set_parameter_pmsm(const double ld, const double lq, const double f, const double rs);
    struct PMSM_state_varibles& get_PMSM_state_varibles()  {return state_varibles;}
    const std::vector<double> out_iabc();
};
}
#endif
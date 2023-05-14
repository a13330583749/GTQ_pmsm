#include "PMSM_sim.h"
namespace PanJL{
struct PMSM_state_varibles
{
    double Id;
    double Iq;
    double wr;
    double theta_ele;
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

    void PMSM_differential_equation(double ud, double uq);
public:
    PMSM() = default;
    int init_PMSM(double ld, double lq, double f, double rs, double tl, double pn, double j){};
    int set_state_PMSM(double id_, double iq_, double wr_, double theta_ele_){};
    int ode45(double ud, double uq);
    struct PMSM_state_varibles get_PMSM_state_varibles()    {return state_varibles;}
};
}
#include "PMSM_sim.h"

namespace PanJL{
void FCSMPCer::predict_i_updata(const double& ualpha, const double& ubeta, const double& times)
{
    // std::vector<double> Idq_predict(2);
    auto ud = alphabeta2d(ualpha, ubeta, get_ele_theta());
    auto uq = alphabeta2q(ualpha, ubeta, get_ele_theta());
    double did = (-Rs * get_id() + get_wr() * Pn * Lq + ud)/ Ld;
    double diq = (-Rs * get_iq() - get_wr() * Pn * Ld 
                    - get_wr() * Pn * F + uq)/Lq;
    Idq_predict[0] = did * times + get_id();
    Idq_predict[1] = diq * times + get_iq(); 
}


std::vector<int> FCSMPCer::controller(const double &Id_ref, const double &Iq_ref, const double &theta_ele,
                                        const std::vector<double> &Iabc, const double &wr, const double& times,
                                         const double& u0_input)
{
    /*  这一部分是使用长时域的时候会需要到，先放在这里，由于时用到的是单步的计算，所以直接在dq轴中进行控制
    double Ialpha = dq2alpha(Id_ref, Iq_ref, theta_ele);
    double Ibeta  = dq2beta(Id_ref, Iq_ref, theta_ele);
    */
    std::vector<int> result_vir_output{0,0,0};
    double result_value = DBL_MAX ;
    updata_pmsm_model(Iabc, wr, theta_ele, u0_input);
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            for (int k = -1; k < 2; k++){
                // The alpha&beta of the parameter can be optimized here to establish direct contact with abc
                predict_i_updata(abc2alpha(i*Vdc/2,j*Vdc/2,k*Vdc/2), abc2beta(i*Vdc/2,j*Vdc/2,k*Vdc/2), times);
                if( result_value > ((Id_ref - Idq_predict[0])*(Id_ref - Idq_predict[0]) +  (Iq_ref - Idq_predict[1])*(Iq_ref - Idq_predict[1]))){
                    result_vir_output = {i, j, k};
                    result_value > ((Id_ref - Idq_predict[0])*(Id_ref - Idq_predict[0]) +  (Iq_ref - Idq_predict[1])*(Iq_ref - Idq_predict[1]));
                }
            }
        }
    }
    return result_vir_output;
}

void FCSMPCer::updata_pmsm_model(const std::vector<double>& Iabc, const double& wr,const double& theta_ele, const double& u0_)
{
    get_PMSM_state_varibles().Id = abc2alpha(Iabc[0], Iabc[1], Iabc[2]);
    get_PMSM_state_varibles().Iq = abc2alpha(Iabc[0], Iabc[1], Iabc[2]);
    get_PMSM_state_varibles().theta_ele = theta_ele;
    get_PMSM_state_varibles().wr = wr;
    u0 = u0_;
}

FCSMPCer::FCSMPCer(double vdc, double c): Plant(vdc, c)
{
    Idq_predict.reserve(2);
}

std::vector<int> FCSMPCer::Voltage_output_mapping(const std::vector<int>& controller_outputs)
{
    
}

}
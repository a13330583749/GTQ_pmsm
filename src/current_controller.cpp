#include "../PMSM_sim.h"

namespace PanJL{
void FCSMPCer::predict_i_updata(const double& ualpha, const double& ubeta, const double& times)
{
    // std::vector<double> Idq_predict(2);
    auto ud = alphabeta2d(ualpha, ubeta, get_ele_theta());
    auto uq = alphabeta2q(ualpha, ubeta, get_ele_theta());
    double did = (-Rs * get_id() + get_wr() * Pn * Lq + ud)/ Ld;
    double diq = (-Rs * get_iq() - get_wr() * Pn * Ld 
                    - get_wr() * Pn * F + uq)/ Lq;
    Idq_predict[0] = (did * times) + get_id();
    Idq_predict[1] = (diq * times) + get_iq(); 
}


std::vector<std::vector<int>> FCSMPCer::controller(const double &Id_ref, const double &Iq_ref, const double &theta_ele,
                                        const std::vector<double> &Iabc, const double &wr, const double& times,
                                         const double& u0_input)
{
    /*  这一部分是使用长时域的时候会需要到，先放在这里，由于时用到的是单步的计算，所以直接在dq轴中进行控制
    double Ialpha = dq2alpha(Id_ref, Iq_ref, theta_ele);
    double Ibeta  = dq2beta(Id_ref, Iq_ref, theta_ele);
    */
    std::vector<std::vector<int>> ptr;
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
                    result_value = ((Id_ref - Idq_predict[0])*(Id_ref - Idq_predict[0]) +  (Iq_ref - Idq_predict[1])*(Iq_ref - Idq_predict[1]));
                }
            }
        }
    }
    
    // std::cout << result_vir_output[0] << " "<< result_vir_output[1] << " "<< result_vir_output[2] << std::endl;
    // 电压输出映射
    if(result_vir_output[0] + result_vir_output[1] + result_vir_output[2] == 0){
        // use the medium voltage vector
        if(result_vir_output[0] + result_vir_output[1] != 0){
            flag = false;
            // ptr->push_back(outputs_mapping_mediem.at((result_vir_output)));
            return outputs_mapping_mediem.at((result_vir_output));
        }else{ // ues zero voltage vector
            flag = true;
            //ptr = std::make_shared<std::vector<std::vector<int>>>(std::initializer_list<std::vector<int>>{{1, 1, 1, 1, 1}});
            return std::vector<std::vector<int>>(std::initializer_list<std::vector<int>>{{1, 1, 1, 1, 1}});
        }
    }else{
        flag = true;
        auto it = std::find(result_vir_output.begin(), result_vir_output.end(),  0);
        if( it == result_vir_output.end()){ // 使用长矢量
            // ptr = std::make_shared<std::vector<std::vector<int>>>
                // (outputs_mapping_positive.at((result_vir_output)));
                return outputs_mapping_positive.at((result_vir_output));
        }else{ // 使用短矢量
            ptr = outputs_mapping_positive.at((result_vir_output));

            // v 1
            if( ptr[0] == std::vector<int>{0,1,1,0,0}){
                if( Iabc[0] * u0 < 0){
                    // ptr = std::make_shared<std::vector<std::vector<int>>>
                    // (outputs_mapping_negative.at((result_vir_output)));
                    return outputs_mapping_negative.at((result_vir_output));
                }else
                    return ptr;
            }
            // v 2
            if( ptr[0] == std::vector<int>{1,0,1,1,0} ){
                if( Iabc[2] * u0 < 0){
                    // ptr = std::make_shared<std::vector<std::vector<int>>>
                    return outputs_mapping_negative.at((result_vir_output));
                }else
                    return ptr;
            }
            // v 3
            if( ptr[0] == std::vector<int>{0,1,0,1,0} ){
                if( Iabc[1] * u0 < 0){
                    // ptr = std::make_shared<std::vector<std::vector<int>>>
                    return outputs_mapping_negative.at((result_vir_output));
                }else
                    return ptr;
            }
            // v 4
            if( ptr[0] == std::vector<int>{0,1,0,1,0} ){
                if( Iabc[0] * u0 < 0){
                    //ptr = std::make_shared<std::vector<std::vector<int>>>
                    return outputs_mapping_negative.at((result_vir_output));
                }else
                    return ptr;
            }
            // v 5
            if( ptr[0] == std::vector<int>{0,1,0,0,1} ){
                if( Iabc[2] * u0 < 0){
                    // ptr = std::make_shared<std::vector<std::vector<int>>>
                    return outputs_mapping_negative.at((result_vir_output));
                }else
                    return ptr;
            }
            // v 6
            if( ptr[0] == std::vector<int>{1,0,1,0,1} ){
                if( Iabc[1] * u0 < 0){
                    //ptr = std::make_shared<std::vector<std::vector<int>>>
                    return outputs_mapping_negative.at((result_vir_output));
                }else
                    return ptr;
            }

        }
    }
    return ptr;
}

void FCSMPCer::updata_pmsm_model(const std::vector<double>& Iabc, const double& wr,const double& theta_ele, const double& u0_)
{
    auto Ialpha = abc2alpha(Iabc[0], Iabc[1], Iabc[2]);
    auto Ibeta  = abc2beta(Iabc[0], Iabc[1], Iabc[2]);
    state_varibles.Id = alphabeta2d(Ialpha, Ibeta, theta_ele);
    state_varibles.Iq = alphabeta2q(Ialpha, Ibeta, theta_ele);
    state_varibles.theta_ele = theta_ele;
    state_varibles.wr = wr;
    u0 = u0_;
}

// PredictionHorizon:必须使用常量表达式（编译时就可以确定结果），否则可以动态矩阵Eigen::MatrixXd
// 使用论文中的表达方式表达
// 有一点就是还是不考虑使用延迟补偿的方法，还要继续的用k时刻的值
std::vector<int> FCSMPCer::sda_output_u1(const double& Id_ref, const double& Iq_ref)
{
    // 首先进行矩阵的建立和初始化工作
    // Phi: Φ
    Eigen::Matrix<double, FCSMPCer::PredictionHorizon * PanJL::rankA, PredictionHorizon * PanJL::rankA> Phi;
    

}

}
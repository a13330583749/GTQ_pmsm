#include "../PMSM_sim.h"

namespace PanJL{
void FCSMPCer::predict_i_updata(const double& ualpha, const double& ubeta, const double& times)
{
    // std::vector<double> Idq_predict(2);
    auto ud = alphabeta2d(ualpha, ubeta, get_ele_theta());
    auto uq = alphabeta2q(ualpha, ubeta, get_ele_theta());
    double did = (-Rs * get_id() + get_wr() * Pn * Lq * get_iq() + ud)/ Ld;
    double diq = (-Rs * get_iq() - get_wr() * Pn * Ld * get_id()
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
    std::vector<std::vector<int>> ptr;  // 返回值结果
    std::vector<int> result_vir_output{0,0,0};  // 最后优化的结果就放在这个地方
    updata_pmsm_model(Iabc, wr, theta_ele, u0_input);  // 将控制器中的电机最新状态更新
    auto Ialpha = abc2alpha(Iabc[0], Iabc[1], Iabc[2]);
    auto Ibeta  = abc2beta(Iabc[0], Iabc[1], Iabc[2]);
    // 使用短时域
    switch (Long_horizon_sda_flag)
    {
    case 1: // 选择使用SDA控制方案
        Solvingalgorithms.a = wr;
        Solvingalgorithms.c = theta_ele;
        Solvingalgorithms.Id = alphabeta2d(Ialpha, Ibeta, theta_ele);
        Solvingalgorithms.Iq = alphabeta2d(Ialpha, Ibeta, theta_ele);
        Solvingalgorithms.Iq_ref = Iq_ref;
        result_vir_output = Solvingalgorithms.updata();     
        break;

    case 2:{ // 选择使用无拍差的控制方案
        // 获得无拍差电压
        auto Id     = alphabeta2d(Ialpha, Ibeta, theta_ele);
        auto Iq     = alphabeta2q(Ialpha, Ibeta, theta_ele);
        double ud_ref = Rs * Id + Ld * (Id_ref - Id) / Ts - Pn * wr * Lq * Iq;
        double uq_ref = Rs * Iq + Lq * (Iq_ref - Iq) / Ts + Pn * wr * (Ld * Id + F);
        // 变换到αβ轴无拍差电压
        auto u_alpha_ref = dq2alpha(ud_ref, uq_ref, theta_ele);
        auto u_beta_ref  = dq2beta (ud_ref, uq_ref, theta_ele);
        auto u_theta = std::atan(u_beta_ref/u_alpha_ref);
        int section_judge = -1;  // 扇区判断
        if(u_alpha_ref > 0){
            if(u_theta < -PI/6)
                section_judge = 6;
            else if(u_theta > PI/6)
                section_judge = 2;
            else
                section_judge = 1;
        }else{
            if(u_theta < -PI/6)
                section_judge = 3;
            else if(u_theta > PI/6) 
                section_judge = 5;
            else
                section_judge = 4;
        }
        double Magnitude = std::sqrt(ud_ref * ud_ref + uq_ref * uq_ref);
        if(Magnitude > Vdc / 2){
            switch (section_judge)
            {
            case 1:
                return std::vector<std::vector<int>>{{1,1,1,0,0}};
            case 2:
                return std::vector<std::vector<int>>{{1,1,1,1,0}};
            case 3:
                return std::vector<std::vector<int>>{{1,1,0,1,0}};
            case 4:
                return std::vector<std::vector<int>>{{1,1,0,1,1}};
            case 5:
                return std::vector<std::vector<int>>{{1,1,0,0,1}};
            case 6:
                return std::vector<std::vector<int>>{{1,1,1,0,1}};
            default:
                std::cerr << "Ummm, the u_deadbeat is fault.\n\r";
                break;
            }
        }else if(Magnitude < Vdc/6)
            return std::vector<std::vector<int>>{{1,1,1,1,1}};
        else {
            switch (section_judge)
            {
            case 1:
                result_vir_output = {1,0,0};
                break;
            case 2:
                result_vir_output = {1,1,0};
                break;
            case 3:
                result_vir_output = {0,1,0};
                break;
            case 4:
                result_vir_output = {0,1,1};
                break;
            case 5:
                result_vir_output = {0,0,1};
                break;
            case 6:
                result_vir_output = {1,0,1};
                break;
            default:
                std::cerr << "Ummm, the u_deadbeat is fault.\n\r";
                break;
            }
        }
        break; // deadbeat control end
    }
    default: 
        { // 默认使用单矢量的控制方案
        double result_value = DBL_MAX ;     // 最优值用于单步的判断 
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
        break;
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
            // 中点电压映射
            // v1
            if( result_vir_output == std::vector<int>{1,0,0} || result_vir_output == std::vector<int>{0,-1,-1}){
                if( Iabc[0] * u0 > 0){
                    return std::vector<std::vector<int>>{{0,1,1,0,0}};
                }else
                    return std::vector<std::vector<int>>{{1,0,1,0,0}};
            }
            // v2
            if( result_vir_output == std::vector<int>{1,1,0} || result_vir_output == std::vector<int>{0,0,-1}){
                if( Iabc[2] * u0 < 0){
                    // ptr = std::make_shared<std::vector<std::vector<int>>>
                    return std::vector<std::vector<int>>{{0,1,1,1,0}};
                }else
                    return std::vector<std::vector<int>>{{1,0,1,1,0}};;
            }
            // v 3
            if( result_vir_output == std::vector<int>{0,1,0} || result_vir_output == std::vector<int>{-1,0,-1} ){
                if( Iabc[1] * u0 > 0){
                    // ptr = std::make_shared<std::vector<std::vector<int>>>
                    return std::vector<std::vector<int>>{{0,1,0,1,0}};
                }else
                    return std::vector<std::vector<int>>{{1,0,0,1,0}};
            }
            // v4
            if( result_vir_output == std::vector<int>{0,1,1} || result_vir_output == std::vector<int>{-1,0,0}){
                if( Iabc[0] * u0 < 0){
                    //ptr = std::make_shared<std::vector<std::vector<int>>>
                    return std::vector<std::vector<int>>{{0,1,0,1,1}};
                }else
                    return std::vector<std::vector<int>>{{1,0,0,1,1}};
            }
            // v 5
            if(result_vir_output == std::vector<int>{0,0,1} || result_vir_output == std::vector<int>{-1,-1,0}){
                if( Iabc[2] * u0 > 0){
                    // ptr = std::make_shared<std::vector<std::vector<int>>>
                    return std::vector<std::vector<int>>{{0,1,0,0,1}};
                }else
                    return std::vector<std::vector<int>>{{1,0,0,0,1}};
            }
            // v 6
            if(result_vir_output == std::vector<int>{1,0,1} || result_vir_output == std::vector<int>{0,-1,0}){
                if( Iabc[1] * u0 < 0){
                    //ptr = std::make_shared<std::vector<std::vector<int>>>
                    return std::vector<std::vector<int>>{{0,1,1,0,1}};
                }else
                    return std::vector<std::vector<int>>{{1,0,1,0,1}};
            }
            else
                return std::vector<std::vector<int>>{{1,1,1,1,1}};

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

// // PredictionHorizon:必须使用常量表达式（编译时就可以确定结果），否则可以动态矩阵Eigen::MatrixXd
// // 使用论文中的表达方式表达
// // 有一点就是还是不考虑使用延迟补偿的方法，还要继续的用k时刻的值
// std::vector<int> FCSMPCer::sda_output_u1(const double& Id_ref, const double& Iq_ref)
// {
//     // 首先进行矩阵的建立和初始化工作
//     // Phi: Φ
//     Eigen::Matrix<double, FCSMPCer::PredictionHorizon * rankA, PredictionHorizon * rankA> Phi;
    

// }

}
#ifndef CURRENT_CONTROLLER_H
#define CURRENT_CONTROLLER_H

#define ONESTEPFCSMPC true
#include "system.h"
namespace PanJL{
#ifdef ONESTEPFCSMPC
// 这里需要继承，需要使用PMSM的模型参数
class FCSMPCer: public Plant
{
private:

    // 建立ualpha 和 ubeta的联系
    // const std::unordered_map<std::vector<int>, std::vector<double>> Uabc2alphabeta = {
    //     {std::vector<int>{0,0,0}, }
    // };


    std::vector<double> Idq_predict;
    //这个采用单步预测，直接输出预测得到的电流
    //因为不使用无传感器的控制策略，所以暂时不用对于转速和电角度进行预测
    void predict_i_updata(const double& ualpha, const double& ubeta, const double& times);
    void updata_pmsm_model(const std::vector<double>& Iabc, const double& wr,const double& theta_ele,  const double& u0_);

public:
    FCSMPCer(double vdc, double c);   
    // std::vector<double> get_i_alpha_beta(const std::vector<double>& Iabc, const double& wr, const double& ele_theta);
    std::vector<int> controller(const double& Id_ref, const double& Iq_ref, const double& theta_ele,
                                const std::vector<double>& Iabc, const double& wr, const double& times,
                                const double& u0_input);
    
    std::vector<int> Voltage_output_mapping(const std::vector<int>& controller_outputs);

private:
    const std::unordered_map<std::vector<int>, std::vector<int>> outputs_mapping_positive = {
    // 长矢量
        {std::vector<int>{1,-1,-1}, std::vector<int>{1,1,1,0,0}},
        {std::vector<int>{1,1,1}, std::vector<int>{1,1,1,1,0}},
        {std::vector<int>{-1,1,-1}, std::vector<int>{1,1,0,1,0}},
        {std::vector<int>{-1,1,1}, std::vector<int>{1,1,0,1,1}},
        {std::vector<int>{-1,-1,1}, std::vector<int>{1,1,0,0,1}},
        {std::vector<int>{1,-1,1}, std::vector<int>{1,1,1,0,1}},
    // v_small 1
        {std::vector<int>{1,0,0}, std::vector<int>{0,1,1,0,0}},
        {std::vector<int>{0,-1,-1}, std::vector<int>{0,1,1,0,0}},
    // v_small 2
        {std::vector<int>{1,1,0}, std::vector<int>{1,0,1,1,0}},
        {std::vector<int>{0,0,-1}, std::vector<int>{1,0,1,1,0}},
    // v_small 3
        {std::vector<int>{0,1,0}, std::vector<int>{0,1,0,1,0}},
        {std::vector<int>{-1,-1,0}, std::vector<int>{0,1,0,1,0}},
    // v_small 4
        {std::vector<int>{0,1,0}, std::vector<int>{0,1,0,1,0}},
        {std::vector<int>{-1,-1,0}, std::vector<int>{0,1,0,1,0}},
    // v_small 5
        {std::vector<int>{0,1,0}, std::vector<int>{0,1,0,0,1}},
        {std::vector<int>{-1,0,-1}, std::vector<int>{0,1,0,0,1}},
    // v_small 6
        {std::vector<int>{0,0,-1}, std::vector<int>{1,0,1,0,1}},
        {std::vector<int>{1,1,0}, std::vector<int>{1,0,1,0,1}},
    };
    const std::unordered_map<std::vector<int>, std::vector<int>> outputs_mapping_negative = {
    // 长矢量
        {std::vector<int>{1,-1,-1}, std::vector<int>{1,1,1,0,0}},
        {std::vector<int>{1,1,1}, std::vector<int>{1,1,1,1,0}},
        {std::vector<int>{-1,1,-1}, std::vector<int>{1,1,0,1,0}},
        {std::vector<int>{-1,1,1}, std::vector<int>{1,1,0,1,1}},
        {std::vector<int>{-1,-1,1}, std::vector<int>{1,1,0,0,1}},
        {std::vector<int>{1,-1,1}, std::vector<int>{1,1,1,0,1}},
    // v_small 1
        {std::vector<int>{1,0,0}, std::vector<int>{0,1,1,0,0}},
        {std::vector<int>{0,-1,-1}, std::vector<int>{0,1,1,0,0}},
    // v_small 2
        {std::vector<int>{1,1,0}, std::vector<int>{1,0,1,1,0}},
        {std::vector<int>{0,0,-1}, std::vector<int>{1,0,1,1,0}},
    // v_small 3
        {std::vector<int>{0,1,0}, std::vector<int>{0,1,0,1,0}},
        {std::vector<int>{-1,-1,0}, std::vector<int>{0,1,0,1,0}},
    // v_small 4
        {std::vector<int>{0,1,0}, std::vector<int>{0,1,0,1,0}},
        {std::vector<int>{-1,-1,0}, std::vector<int>{0,1,0,1,0}},
    // v_small 5
        {std::vector<int>{0,1,0}, std::vector<int>{0,1,0,0,1}},
        {std::vector<int>{-1,0,-1}, std::vector<int>{0,1,0,0,1}},
    // v_small 6
        {std::vector<int>{0,0,-1}, std::vector<int>{1,0,1,0,1}},
        {std::vector<int>{1,1,0}, std::vector<int>{1,0,1,0,1}},
    };
};

#endif
}
#endif
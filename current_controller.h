#ifndef CURRENT_CONTROLLER_H
#define CURRENT_CONTROLLER_H

#define ONESTEPFCSMPC true
#include "system.h"
#include <unordered_map>
namespace PanJL{
#ifdef ONESTEPFCSMPC
// 这里需要继承，需要使用PMSM的模型参数

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};
using MySet = std::unordered_map<std::vector<int>, std::vector<int>>;
class FCSMPCer: public Plant
{
private:

    // 建立ualpha 和 ubeta的联系
    // const std::unordered_map<std::vector<int>, std::vector<double>> Uabc2alphabeta = {
    //     {std::vector<int>{0,0,0}, }
    // };
    // if flag is true, control is once, else(false) control two times
    bool flag;//need one or two times control
    std::vector<double> Idq_predict;
    //这个采用单步预测，直接输出预测得到的电流
    //因为不使用无传感器的控制策略，所以暂时不用对于转速和电角度进行预测
    void predict_i_updata(const double& ualpha, const double& ubeta, const double& times);
    void updata_pmsm_model(const std::vector<double>& Iabc, const double& wr,const double& theta_ele,  const double& u0_);

public:
    FCSMPCer(double vdc, double c): Plant(vdc, c), flag(true){Idq_predict.resize(2);}   
    // std::vector<double> get_i_alpha_beta(const std::vector<double>& Iabc, const double& wr, const double& ele_theta);
    std::shared_ptr<std::vector<std::vector<int>>> controller(const double& Id_ref, const double& Iq_ref, const double& theta_ele,
                                const std::vector<double>& Iabc, const double& wr, const double& times,
                                const double& u0_input);
    
    std::vector<int> Voltage_output_mapping(const std::vector<int>& controller_outputs);

private:
    // positive voltage vector of small/ long
    const std::unordered_map<std::vector<int>, std::vector<int>, VectorHash> outputs_mapping_positive = {
    // 长矢量
        {std::vector<int>{1,-1,-1}, std::vector<int>{1,1,1,0,0}},
        {std::vector<int>{1,1,-1}, std::vector<int>{1,1,1,1,0}},
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
    // negative voltage vector of small/ long
    const std::unordered_map<std::vector<int>, std::vector<int>, VectorHash> outputs_mapping_negative = {
    // 长矢量
        {std::vector<int>{1,-1,-1}, std::vector<int>{1,1,1,0,0}}, // V1
        {std::vector<int>{1,1,-1}, std::vector<int>{1,1,1,1,0}},  // V2
        {std::vector<int>{-1,1,-1}, std::vector<int>{1,1,0,1,0}}, // V3
        {std::vector<int>{-1,1,1}, std::vector<int>{1,1,0,1,1}},  // V4
        {std::vector<int>{-1,-1,1}, std::vector<int>{1,1,0,0,1}}, // V5
        {std::vector<int>{1,-1,1}, std::vector<int>{1,1,1,0,1}},  // V6
    // v_small 1
        {std::vector<int>{1,0,0}, std::vector<int>{1,0,1,0,0}},
        {std::vector<int>{0,-1,-1}, std::vector<int>{1,0,1,0,0}},
    // v_small 2
        {std::vector<int>{1,1,0}, std::vector<int>{0,1,1,1,0}},
        {std::vector<int>{0,0,-1}, std::vector<int>{0,1,1,1,0}},
    // v_small 3
        {std::vector<int>{0,1,0}, std::vector<int>{1,0,0,1,0}},
        {std::vector<int>{-1,-1,0}, std::vector<int>{1,0,0,1,0}},
    // v_small 4
        {std::vector<int>{0,1,0}, std::vector<int>{1,0,0,1,0}},
        {std::vector<int>{-1,-1,0}, std::vector<int>{1,0,0,1,0}},
    // v_small 5
        {std::vector<int>{0,1,0}, std::vector<int>{1,0,0,0,1}},
        {std::vector<int>{-1,0,-1}, std::vector<int>{1,0,0,0,1}},
    // v_small 6
        {std::vector<int>{0,0,-1}, std::vector<int>{0,1,1,0,1}},
        {std::vector<int>{1,1,0}, std::vector<int>{0,1,1,0,1}},
    };

    const std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, VectorHash > outputs_mapping_mediem = {
        {std::vector<int>{1,0,-1}, std::vector<std::vector<int>>{{1,1,1,0,0},{1,1,1,1,0}}},// section 1
        {std::vector<int>{0,1,-1}, std::vector<std::vector<int>>{{1,1,1,1,0},{1,1,0,1,0}}},// section 2
        {std::vector<int>{-1,1,0}, std::vector<std::vector<int>>{{1,1,0,1,0},{1,1,0,1,1}}},// section 3
        {std::vector<int>{-1,0,1}, std::vector<std::vector<int>>{{1,1,0,1,1},{1,1,0,0,1}}},// section 4
        {std::vector<int>{0,-1,1}, std::vector<std::vector<int>>{{1,1,0,0,1},{1,1,1,0,1}}},// section 5
        {std::vector<int>{1,-1,0}, std::vector<std::vector<int>>{{1,1,1,0,1},{1,1,1,0,0}}},// section 6
    };
};

#endif
}
#endif
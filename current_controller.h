#ifndef CURRENT_CONTROLLER_H
#define CURRENT_CONTROLLER_H

#define ONESTEPFCSMPC true
#include "system.h"
#include <unordered_map>
#include <memory>
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
    bool Long_horizon_sda_flag;  // 是否使用长时域
    //这个采用单步预测，直接输出预测得到的电流
    //因为不使用无传感器的控制策略，所以暂时不用对于转速和电角度进行预测
    void predict_i_updata(const double& ualpha, const double& ubeta, const double& times);
    void updata_pmsm_model(const std::vector<double>& Iabc, const double& wr,const double& theta_ele,  const double& u0_);
    const static int PredictionHorizon = 4; // 预测时域：对于SDA算法，或者multiplestep FCS-MPC使用

public:
    FCSMPCer(double vdc, double c): Plant(vdc, c), flag(true){Idq_predict.resize(2);}   
    std::vector<std::vector<int>> controller(const double& Id_ref, const double& Iq_ref, const double& theta_ele,
                                const std::vector<double>& Iabc, const double& wr, const double& times,
                                const double& u0_input);

    std::vector<int> Voltage_output_mapping(const std::vector<int>& controller_outputs);
    // true is one time, and false is two times
    inline bool get_flag_control_times() const{return flag;}

    // 球型译码器算法：sda_output_u1
    // FCSMPCer已经包含的元素：Ts, 预测时域
    // 电机的具体运行参数已经在updata_pmsm_model()函数中更新，因此可以直接在state_varibles中调用
    // 不考虑无感控制的情况，因此不需要传递实际的参数；
    // 可能还需要权值矩阵，因此在private成员变量中加入权值矩阵，因此也不需要传递具体的参数
    // 首先使用单位权重矩阵，
    // 为了算出|Δu|，还需要保留上一个时刻的virtual_u0
    // updata_pmsm_model()中：包含了Idq,wr,theta_ele
    
    std::vector<int> sda_output_u1(const double& Id_ref, const double& Iq_ref);

private:
    // positive voltage vector of small/ long
    std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, VectorHash> outputs_mapping_positive = {
    // 长矢量
        {std::vector<int>{1,-1,-1}, std::vector<std::vector<int>>{{1,1,1,0,0}}}, // V1
        {std::vector<int>{1,1,-1},  std::vector<std::vector<int>>{{1,1,1,1,0}}},  // V2
        {std::vector<int>{-1,1,-1}, std::vector<std::vector<int>>{{1,1,0,1,0}}}, // V3
        {std::vector<int>{-1,1,1},  std::vector<std::vector<int>>{{1,1,0,1,1}}},  // V4
        {std::vector<int>{-1,-1,1}, std::vector<std::vector<int>>{{1,1,0,0,1}}}, // V5
        {std::vector<int>{1,-1,1},  std::vector<std::vector<int>>{{1,1,1,0,1}}},  // V6
    // v_small 1
        {std::vector<int>{1,0,0}, std::vector<std::vector<int>>{{0,1,1,0,0}}},
        {std::vector<int>{0,-1,-1}, std::vector<std::vector<int>>{{0,1,1,0,0}}},
    // v_small 2
        {std::vector<int>{1,1,0}, std::vector<std::vector<int>>{{1,0,1,1,0}}},
        {std::vector<int>{0,0,-1}, std::vector<std::vector<int>>{{1,0,1,1,0}}},
    // v_small 3
        {std::vector<int>{0,1,0}, std::vector<std::vector<int>>{{0,1,0,1,0}}},
        {std::vector<int>{-1,0,-1}, std::vector<std::vector<int>>{{0,1,0,1,0}}},
    // v_small 4
        {std::vector<int>{0,1,1}, std::vector<std::vector<int>>{{0,1,0,1,0}}},
        {std::vector<int>{-1,0,0}, std::vector<std::vector<int>>{{0,1,0,1,0}}},
    // v_small 5
        {std::vector<int>{0,0,1}, std::vector<std::vector<int>>{{0,1,0,0,1}}},
        {std::vector<int>{-1,-1,0},std::vector<std::vector<int>>{{0,1,0,0,1}}},
    // v_small 6
        {std::vector<int>{0,-1,0}, std::vector<std::vector<int>>{{1,0,1,0,1}}},
        {std::vector<int>{1,0,1}, std::vector<std::vector<int>>{{1,0,1,0,1}}},

        {std::vector<int>{0,0,0}, std::vector<std::vector<int>>{{1,0,1,1,1}}},
        {std::vector<int>{1,1,1}, std::vector<std::vector<int>>{{1,0,1,1,1}}},
        {std::vector<int>{-1,-1,-1}, std::vector<std::vector<int>>{{1,0,1,1,1}}},
    };
    // negative voltage vector of small/ long
    std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, VectorHash> outputs_mapping_negative = {
    // 长矢量
        {std::vector<int>{1,-1,-1}, std::vector<std::vector<int>>{{1,1,1,0,0}}}, // V1
        {std::vector<int>{1,1,-1},  std::vector<std::vector<int>>{{1,1,1,1,0}}},  // V2
        {std::vector<int>{-1,1,-1}, std::vector<std::vector<int>>{{1,1,0,1,0}}}, // V3
        {std::vector<int>{-1,1,1},  std::vector<std::vector<int>>{{1,1,0,1,1}}},  // V4
        {std::vector<int>{-1,-1,1}, std::vector<std::vector<int>>{{1,1,0,0,1}}}, // V5
        {std::vector<int>{1,-1,1},  std::vector<std::vector<int>>{{1,1,1,0,1}}},  // V6
    // v_small 1
        {std::vector<int>{1,0,0},   std::vector<std::vector<int>>{{1,0,1,0,0}}},
        {std::vector<int>{0,-1,-1}, std::vector<std::vector<int>>{{1,0,1,0,0}}},
    // v_small 2
        {std::vector<int>{1,1,0},   std::vector<std::vector<int>>{{0,1,1,1,0}}},
        {std::vector<int>{0,0,-1},  std::vector<std::vector<int>>{{0,1,1,1,0}}},
    // v_small 3
        {std::vector<int>{0,1,0},   std::vector<std::vector<int>>{{1,0,0,1,0}}},
        {std::vector<int>{-1,0,-1}, std::vector<std::vector<int>>{{1,0,0,1,0}}},
    // v_small 4
        {std::vector<int>{0,1,1},   std::vector<std::vector<int>>{{1,0,0,1,0}}},
        {std::vector<int>{-1,0,0}, std::vector<std::vector<int>>{{1,0,0,1,0}}},
    // v_small 5
        {std::vector<int>{0,0,1},   std::vector<std::vector<int>>{{1,0,0,0,1}}},
        {std::vector<int>{-1,-1,0}, std::vector<std::vector<int>>{{1,0,0,0,1}}},
    // v_small 6
        {std::vector<int>{0,-1,0},  std::vector<std::vector<int>>{{0,1,1,0,1}}},
        {std::vector<int>{1,0,1},   std::vector<std::vector<int>>{{0,1,1,0,1}}},
    };

    std::unordered_map<std::vector<int>, std::vector<std::vector<int>>, VectorHash > outputs_mapping_mediem = {
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
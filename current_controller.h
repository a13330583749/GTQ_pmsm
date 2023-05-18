#ifndef CURRENT_CONTROLLER_H
#define CURRENT_CONTROLLER_H

#define ONESTEPFCSMPC true
#include "PMSM.h"
namespace PanJL{
#ifdef ONESTEPFCSMPC
// 这里有一个需不需要继承的问题，需要使用PMSM的模型参数
class FCSMPCer: public PMSM
{
private:
    // 其实这个电流都是已知量了，只要知道了ABC电流和电角度因此这个状态变流也不需要
    std::vector<double> predict_current;
    //这个采用单步预测，直接输出预测得到的电流
    //因为不使用无传感器的控制策略，所以暂时不用对于转速和电角度进行预测
    std::vector<double> predict_i(const double& ud, const double& uq, const double& times);

public:
    std::vector<double> get_i_alpha_beta(const std::vector<double>& Iabc, const double& wr, const double& ele_theta);
    std::vector<int> controller(const double& Id_ref, const double& Iq_ref, const double& theta_ele);

};

#endif
}
#endif
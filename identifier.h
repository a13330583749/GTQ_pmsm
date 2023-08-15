// 这个类用于继承辨识器具体算法，将测试程序的接口和实际辨识算法结合
// 属于是胶水类
#ifndef Identifier_h
#define Identifier_h
#include <./IRLS.h>
#include <PMSM_sim.h>
namespace PanJL{

class Identifier: public IRLS_parameter_identify
{
public:
    // std::vector<double>& Idq;
    // std::vector<double>& Udq;
    // void update(const std::vector<double>& Idq, const std::vector<double>& Udq,
    //                     const double& we, const double& Ts);

    // 注意这里使用的是点角速度，所有main传参的时候需要注意
    void renew(const std::vector<double>& Iabc,const std::vector<int>& inputs, const double& Ts,
                const double& we, const double& Vdc, const double&theta_ele);
    void init(const std::vector<double>& Iabc,const std::vector<int>& inputs, const double& Ts,
                const double& we, const double& Vdc, const double&theta_ele);
    Identifier() = default;
};
}


#endif
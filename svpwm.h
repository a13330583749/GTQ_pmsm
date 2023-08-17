#ifndef SVPWM_H
#define SVPWM_H

#include <cmath>
#include <vector>
// 该类参考自袁雷老师的《现代永磁同步电机控制原理及MATLAB仿真》
namespace PanJL{
class SVPWM
{
    double Vdc;   // 调制电压
    double Tpwm;  // PWM的周期
public:
    // 用于输出扇区和各个扇区的时间  
    // 直接从public的接口来取得时间就可以了
    double Tcmp1;
    double Tcmp2;
    double Tcmp3;
    int sector;
    // 各个时间的计算时间
    void calculation(const double& Valpha, const double& Vbeta);
    // Tcmp123转化为开关序列Sabc
    // @PWM_value:pwm的值
    std::vector<int> Tcmp_to_Sabc(const double& PWM_value);
    SVPWM(const double& Vdc_, const double& T_pwm):Vdc(Vdc_),Tpwm(T_pwm){}
};

}
#endif
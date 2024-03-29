#ifndef SVPWM_H
#define SVPWM_H

#include <cmath>
#include <vector>
// 该类参考自袁雷老师的《现代永磁同步电机控制原理及MATLAB仿真》
// 先完成两电平的调制技术，关于三电平的调制技术之后再继续完善
// Vdc就还是先用一样的来弄
namespace PanJL{
extern const double Vdc;
class SVPWM
{
    double Vdc;   // 调制电压
    double Tpwm;  // PWM的周期
    // 符号函数，输出开关函数
    int signal(const double& value, const double& PWM_value){
        if(PWM_value - value >= 0)
            return 1;
        return 0;
    }


public:
    // 用于输出扇区和各个扇区的时间  
    // 直接从public的接口来取得时间就可以了
    // 备扇区时间切换点Tcmp1,Tcmp2,Tcmp3
    double Tcmp1;
    double Tcmp2;
    double Tcmp3;
    int sector;
    // 各个时间的计算时间，计算得到的结果可以直接保存在成员变量Tcmp1,Tcmp2,Tcmp3中
    void calculation(const double& Valpha, const double& Vbeta);
    // 得到各个Tcmp123转化为开关序列Sabc
    // @PWM_value:pwm的值
    std::vector<int> Tcmp_to_Sabc(const double& PWM_value);
    SVPWM(const double& Vdc_, const double& T_pwm):Vdc(Vdc_),Tpwm(T_pwm){}

    std::vector<double> Sabc_to_Uabc(const std::vector<int>& Sabc);
};

class PWMSignalGenerator
{
private:
    double Tpwm;
public:
    PWMSignalGenerator(double T_pwm) : Tpwm(T_pwm) {}
    double PWM_value(double t)
    {
        // 归一化到一个周期中
        // fmod可以实现对于浮点数的取余
        double triangle_wave = fmod(t, Tpwm);

        if(triangle_wave < Tpwm/2.0)
            return triangle_wave;
        else
            return Tpwm - triangle_wave;
    }
};
}
#endif
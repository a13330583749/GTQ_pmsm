// 最小二乘递推算法用于电机参数辨识
#ifndef IRLS_H
#define IRLS_H
namespace PanJL{

// 这里直接就声明进入更新了，不再设置传入这四个变量
// 在更新的时候仅仅传入电流、电压参数
extern double Ld_estimated;
extern double Lq_estimated;
extern double Rs_estimated;
extern double F_estimated;

class IRLS_parameter_identify
{

};
}

#endif
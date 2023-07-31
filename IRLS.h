// 最小二乘递推算法用于电机参数辨识
#ifndef IRLS_H
#define IRLS_H
//eigen核心部分
#include <Eigen/Core>
//稠密矩阵的代数运算（逆、特征值等）
#include <Eigen/Dense>
namespace PanJL{

// 这里直接就声明进入更新了，不再设置传入这四个变量
// 在更新的时候仅仅传入电流、电压参数
extern double Ld_estimated;
extern double Lq_estimated;
extern double Rs_estimated;
extern double F_estimated;
// 最小二乘法辨识参数：


const static int rankA = 2;
class IRLS_parameter_identify
{
private:
    Eigen::Matrix<double, rankA, rankA> P;
};
}

#endif
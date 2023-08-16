// 最小二乘递推算法用于电机参数辨识
#ifndef IRLS_H
#define IRLS_H
//eigen核心部分
#include <Eigen/Core>
//稠密矩阵的代数运算（逆、特征值等）
#include <Eigen/Dense>
#include <functional>
#include <vector>
#include <iostream>
namespace PanJL{

// 这里直接就声明进入更新了，不再设置传入这四个变量
// 在更新的时候仅仅传入电流、电压参数
extern double Ld_estimated;
extern double Lq_estimated;
extern double Rs_estimated;
extern double F_estimated;
// 最小二乘法辨识参数：
extern const double F_;


class IRLS_parameter_identify
{
protected:
    double Id_last_moment;
    double Iq_last_moment;
private:
    std::function<Eigen::Matrix<double, 2, 2>(const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts)> get_K;
    std::function<Eigen::Matrix<double, 2,  2>(const std::vector<double>& Idq, const std::vector<double>& Udq,
                                                    const double& we, const double& Ts)> get_Rho;
    std::function<Eigen::Vector2<double>(const std::vector<double>& Udq, const double& we)> get_Y;
    std::function<Eigen::Vector2<double>(const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts, const Eigen::Matrix<double, 2, 2>& K_)> get_theta;
    // 更新P矩阵
    void updata_P(const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts, const Eigen::Matrix<double, 2, 2>& K_);
    double lambda; // 遗忘因子
public:
    // 作为对外接口，返回的结果直接存放在Rs_estimated Ls_estimated中了
    void update(const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts);
    Eigen::Matrix<double, 2, 2> P;
    IRLS_parameter_identify();
};
}

#endif
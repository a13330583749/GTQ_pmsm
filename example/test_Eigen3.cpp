// 本测试用例用于计算：sphere decoding algorithm所需要的矩阵
// eigen核心部分
#include <iostream>
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆、特征值等）
#include <Eigen/Dense>
#include <functional>
#include "../PMSM_sim.h"
const static int predictive_N = 4;
// const static int rankA = 2;

// 打算这个类作为SDA的电流控制器的友元类提高计算上的帮助
// 这个类主要采用Eigen作为运算单元，而不是使用一般的计算方式
class myClass
{
public:
    double a; // a := state_varibles.wr
    double c; // b := state_varibles.theta_ele
    const Eigen::Matrix<double, rankA, rankA> B = 
     Eigen::Matrix<double, rankA, rankA>{{PanJL::Ts/Ld_, 0}, {0, PanJL::Ts/Lq_}};

    // Clarke变换所需要的矩阵
    const Eigen::Matrix<double, 2, 3> Clarke_Matrix
     = 2 / 3.0 * Eigen::Matrix<double, 2, 3>{{1, -0.5, -0.5}, {0, std::sqrt(3)/2.0, -std::sqrt(3)/2.0}};
    
    // 端电压变换为相电压：
    const Eigen::Matrix<double, 3, 3> T_ground2phase 
     =  Eigen::Matrix<double, 3, 3>{{2, -1, -1}, {-1, 2, -1}, {-1, -1, 2}} / 3.0;

    // 想了想还是得返回矩阵，进行坐标变换还是得使用原来的那些办法
    // 见readme中的方法二
    // 因为park矩阵需要实时获得
    // 而clack矩阵是不会变的

    // Park变换所需要的矩阵
    std::function<Eigen::Matrix<double, 2, 2>()> Park_Matrix;
    
    std::function<Eigen::Matrix<double, rankA, rankA>()> A;
    // Γ
    std::function<Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>()> get_Gamma;
    // Φ
    std::function<Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>()> get_Phi;
    // γ  3代表abc三相电的输入
    std::function<Eigen::Matrix<double, rankA * predictive_N, 3 * predictive_N>()> get_gamma;
    myClass() = default;
    myClass(double A_, double C) : a(A_), c(C)
    {
        // 注意这里的B矩阵是对于SPMSM的，对于有凸性的电机来说。这里的B矩阵需要变换

        this->Park_Matrix = [this]() -> Eigen::Matrix<double, 2, 2>
        {
            Eigen::Matrix<double, 2, 2> T;
            T << std::cos(this->c), std::sin(this->c), -std::sin(this->c), std::cos(this->c);
            return T;
        };

        this->A = [this]() -> Eigen::Matrix<double, 2, 2>
        {
            double A11 = 1 - Rs_ * PanJL::Ts / Ld_;
            double A12 = Pn_ * a * PanJL::Ts;
            double A21 = -a * Pn_ * PanJL::Ts;
            double A22 = 1 - Rs_ * PanJL::Ts / Lq_;
            Eigen::Matrix<double, rankA, rankA> result;
            result << A11, A12, A21, A22;
            return result;
        };
        // 得到：Γ
        this->get_Gamma = [this]() -> Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>
        {
            Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> result;
            result.setZero();
            for (int i = 0; i < predictive_N; i++)
            {
                result.block(i * rankA, i * rankA, rankA, rankA) = this->MatrixPower(this->A(), i);
            }
            return result;
        };
        // 得到Φ：
        this->get_Phi = [this]() -> Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N>
        {
            Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> rhi;
            rhi.setZero();
            for (int i = 0; i < predictive_N; i++){ // 行
                for (int j = 0; j <= i; j++){ // 列
                    rhi.block(i * rankA, j * rankA, rankA, rankA) =
                        Eigen::Matrix<double, rankA, rankA>::Identity() * this->MatrixPower(this->A(), i - j);
                }
            }
            return rhi;
        };
        // 得到γ：
        this->get_gamma = [this]() -> Eigen::Matrix<double, rankA * predictive_N, 3 * predictive_N>
        {
            Eigen::Matrix<double, rankA * predictive_N, 3 * predictive_N> gamma;
            gamma.setZero();
            for (int i = 0; i < predictive_N; i++){ // 行
                for (int j = 0; j <= i; j++){ // 列
                    gamma.block(i * rankA, j * 3, rankA, 3) =
                        PanJL::Vdc / 2.0 *
                        B * this->MatrixPower(this->A(), i - j - 1) * (this->Park_Matrix() * this->Clarke_Matrix )  * T_ground2phase;
                }
            }
            return gamma;
        };

    }

    Eigen::Matrix<double, rankA, rankA> MatrixPower(const Eigen::Matrix<double, rankA, rankA> &matrix, const int &n)
    {
        if(n <= 0)
            return Eigen::Matrix<double, rankA, rankA>::Identity();
        Eigen::Matrix<double, rankA, rankA> result = Eigen::Matrix<double, rankA, rankA>::Identity();
        for (int i = 0; i < n; ++i)
            result *= matrix;
        return result;
    }

    // Eigen::Matrix<double, 3, 3> MatrixPower3(const Eigen::Matrix<double, 3, 3> &matrix, const int &n)
    // {
    //     if(n <= 0)
    //         return Eigen::Matrix<double, rankA, rankA>::Identity();
    //     Eigen::Matrix<double, rankA, rankA> result = Eigen::Matrix<double, rankA, rankA>::Identity();
    //     for (int i = 0; i < n; ++i)
    //         result *= matrix;
    //     return result;
    // }

};

void test1()
{
    myClass obj(2.0, 1.2);
    std::cout << obj.A() << std::endl;
    std::cout << obj.A() * obj.A() << std::endl;
    std::cout << "--------------------" << std::endl;
}

// 用于测试矩阵的连乘
void test2()
{
    myClass obj(2.0, 1.2);
    std::cout << obj.MatrixPower(obj.A(), 2) << std::endl;
    std::cout << "--------------------" << std::endl;
}

void test3()
{
    myClass x(2.0, 1.2);
    Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> rhi;
    rhi.setZero();
    for (int i = 0; i < predictive_N; i++)
    { // 行
        for (int j = 0; j <= i; j++)
        { // 列
            rhi.block(i * rankA, j * rankA, rankA, rankA) =
                Eigen::Matrix<double, rankA, rankA>::Identity() * x.MatrixPower(x.A(), i - j);
        }
    }
    std::cout << rhi << std::endl;
    std::cout << "--------------------" << std::endl;
}

void test4()
{
    myClass x(2.0, 1.2);
    std::cout << x.Park_Matrix() << std::endl;
    std::cout << "*********************" << std::endl;
    std::cout << x.get_Gamma() << std::endl;
    std::cout << "*********************" << std::endl;
    std::cout << x.get_Phi() << std::endl;
    std::cout << "*********************" << std::endl;
    std::cout << x.get_gamma() << std::endl;
    std::cout << "*********************" << std::endl;
    x.a = 1.0;
    x.c = 3.4;
    std::cout << x.get_gamma() << std::endl;
    std::cout << "*********************" << std::endl;
}

int main(int argc, char **argv)
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
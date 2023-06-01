// 本测试用例用于计算：sphere decoding algorithm所需要的矩阵
//eigen核心部分
#include <iostream>
#include <Eigen/Core>
//稠密矩阵的代数运算（逆、特征值等）
#include <Eigen/Dense>
#include <functional>
#include "../PMSM_sim.h"
const static int predictive_N = 4;
// const static int rankA = 2;

class myClass
{
public:
    double a; // a := state_varibles.wr
    double c;
    std::function<Eigen::Matrix<double, rankA, rankA>()> A;
    myClass() = default;
    myClass(double A_, double C):a(A_), c(C)
    {
        this->A = [this]() -> Eigen::Matrix<double, 2, 2>
        {
            double A11 = 1 - Rs_ * PanJL::Ts / Ld_;
            double A12 = Pn_ * a * PanJL::Ts;
            double A21 = -a * Pn_ * PanJL::Ts;
            double A22 = 1 - Rs_ * PanJL::Ts / Lq_;
            Eigen::Matrix<double, rankA, rankA> result;
            result << A11 , A12 , A21 , A22;
            return result;
        };
    }

    Eigen::Matrix<double, rankA, rankA> MatrixPower(const Eigen::Matrix<double, rankA, rankA>& matrix, const int& n){
        Eigen::Matrix<double, rankA, rankA> result = Eigen::Matrix<double, rankA, rankA>::Identity();
            for (int i = 0; i < n; ++i)
                result *= matrix;
        return result;
    }

    Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> get_Gamma()
    {
        Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> result;
        result.setZero();
        for(int i=0; i<predictive_N; i++){
            result.block(i*rankA, i*rankA, rankA, rankA) = this->MatrixPower(this->A(), i);
        }
        return result;
    }
};



void test1()
{
    myClass obj(2.0,1.2);
    std::cout << obj.A() << std::endl;
    std::cout << obj.A() * obj.A() << std::endl;
    std::cout << "--------------------" << std::endl;
}

// 用于测试矩阵的连乘
void test2()
{
    myClass obj(2.0,1.2);
    std::cout << obj.MatrixPower(obj.A(), 2) << std::endl;
    std::cout << "--------------------" << std::endl;
}

void test3()
{
    myClass x(2.0,1.2);
    Eigen::Matrix<double, rankA * predictive_N, rankA * predictive_N> rhi;
    rhi.setZero();
    for(int i=0; i< predictive_N; i++){ // 行
        for(int j=0; j<=i; j++){   // 列
            rhi.block(i*rankA, j*rankA, rankA, rankA) = 
             Eigen::Matrix<double, rankA, rankA>::Identity() * x.MatrixPower(x.A(), i-j);
        }
    }
    std::cout << rhi << std::endl;
    std::cout << "--------------------" << std::endl;
}

int main(int argc, char **argv)
{
    test1();
    test2();
    test3();
    return 0;
}
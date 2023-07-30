#ifndef PMSM_sim
#define PMSM_sim
#include <utility>
#include <iostream>
#include "system.h"
#include "speed_controller.h"
#include "current_controller.h"
// #include "Compensator.h"
#include <cmath>
// #include <climits>
#include <cfloat>
#include <memory>
#include <algorithm>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include "commincation.h"
#include <fstream>
#include <functional>
//eigen核心部分
#include <Eigen/Core>
//稠密矩阵的代数运算（逆、特征值等）
#include <Eigen/Dense>
#include "./sda.h"
namespace PanJL {
#define SparseInverter true

// Vdc先放在这里，不知道会不会有什么类中成员的事情
extern const double Vdc;
extern const double Ts;
extern const int ODE45_M;

// pmsm参数：
extern const double Ld_;
extern const double Lq_;
extern const double F_;
extern const double Rs_;
extern double TL_;
extern const double Bm_;
extern const double J_;
extern const int Pn_;
extern const double PI;


extern double Ld_estimated;
extern double Lq_estimated;
extern double Rs_estimated;
extern double F_estimated;

// SDA 算法的维度
// 用于输出映射时使用
struct inputs {
    std::vector<std::vector<int>> inputs_real;
    std::vector<int> inputs_vitruals;
};

// Lambda functions for coordinate transformations
const auto abc2alpha = [](double a, double b, double c) -> double {
    return 2.0 * (a - 0.5 * b - 0.5 * c) / 3.0;
};

const auto abc2beta = [](double a, double b, double c) -> double {
    return 2.0 * (std::sqrt(3)) / 2.0 * (b - c) / 3.0;
};

const auto alphabeta2a = [](double alpha, double beta) -> double {
    return  beta;
};

const auto alphabeta2b = [](double alpha, double beta) -> double {
    return  (-0.5 * alpha + (std::sqrt(3.0)) / 2.0 * beta);
};

const auto alphabeta2c = [](double alpha, double beta) -> double {
    return  (-0.5 * alpha - (std::sqrt(3.0)) / 2.0 * beta);
};

const auto alphabeta2d = [](double alpha, double beta, double theta) -> double {
    return std::cos(theta) * alpha + std::sin(theta) * beta;
};

const auto alphabeta2q = [](double alpha, double beta, double theta) -> double {
    return -std::sin(theta) * alpha + std::cos(theta) * beta;
};

const auto dq2alpha = [](double d, double q, double theta) -> double {
    return std::cos(theta) * d - std::sin(theta) * q;
};

const auto dq2beta = [](double d, double q, double theta) -> double {
    return std::sin(theta) * d + std::cos(theta) * q;
};

// 将abc变换为uvw
const auto abc2u = [](const double& a, const double& b, const double& c) -> double{
    return (1.0 / 3.0 * (2.0 * a - b - c ));
};

const auto abc2v = [](const double& a, const double& b, const double& c) -> double{
    return (1.0 / 3.0 * (- a + 2.0 * b - c ));
};

const auto abc2w = [](const double& a, const double& b, const double& c) -> double{
    return (1.0 / 3.0 * (- a - b + 2.0 * c ));
};

} // namespace PanJL

#endif
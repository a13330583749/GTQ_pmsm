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
#include "./identifier.h"
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

extern const std::function<double(double, double, double)> abc2alpha;
extern const std::function<double(double, double, double)> abc2beta;
extern const std::function<double(double, double)> alphabeta2a;
extern const std::function<double(double, double)> alphabeta2b;
extern const std::function<double(double, double)> alphabeta2c;
extern const std::function<double(double, double, double)> alphabeta2d;
extern const std::function<double(double, double, double)> alphabeta2q;
extern const std::function<double(double, double, double)> dq2alpha;
extern const std::function<double(double, double, double)> dq2beta;
extern const std::function<double(double, double, double)> abc2u;
extern const std::function<double(double, double, double)> abc2v;
extern const std::function<double(double, double, double)> abc2w;
// Lambda functions for coordinate transformations


} // namespace PanJL

#endif
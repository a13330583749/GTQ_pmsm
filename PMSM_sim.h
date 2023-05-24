#ifndef PMSM_sim
#define PMSM_sim
#include <utility>
#include <iostream>
#include "system.h"
#include "speed_controller.h"
#include "current_controller.h"
#include "Compensator.h"
#include <cmath>
// #include <climits>
#include <cfloat>
#include <memory>
#include <algorithm>
const auto abc2alpha = [](double a, double b, double c)->double{return 2.0 * (a - 0.5 *b - 0.5 * c) / 3.0;};
const auto abc2beta = [](double a, double b, double c)->double{return 2.0 * (std::sqrt(3))/ 2.0 * (b -  c) / 3.0 ;};
const auto alphabeta2a = [](double alpha, double beta)->double{return 2.0 /3.0 * alpha;};
const auto alphabeta2b = [](double alpha, double beta)->double{return 2.0 /3.0 * (-0.5 * alpha + (std::sqrt(3.0))/ 2.0 * beta );};
const auto alphabeta2c = [](double alpha, double beta)->double{return 2.0 /3.0 * (-0.5 * alpha - (std::sqrt(3.0))/ 2.0 * beta );};
const auto alphabeta2d = [](double alpha, double beta, double theta)->double{return std::cos(theta) * alpha + std::sin(theta) * beta;};
const auto alphabeta2q = [](double alpha, double beta, double theta)->double{return -std::sin(theta) * alpha + std::cos(theta) * beta;};
const auto dq2alpha = [](double d, double q, double theta)->double{return std::cos(theta) * d - std::sin(theta) * q;};
const auto dq2beta = [](double d, double q, double theta)->double{return std::sin(theta) * d - std::cos(theta) * q;};

// const auto abc2d = [](const double&a, const double&b, const double& c, const double& theta)
//                     {}

    // pmsm参数：
const double Ld_ = 7e-3;
const double Lq_ = 7e-3;
const double F_ = 0.125;
const double Rs_ = 2.98;
const double TL_ = 0;
const double Bm_ = 1.1e-4;
const double J_ = 4.7e-5;
const int Pn_ = 2;

namespace PanJL{
#define SparseInverter ture

const double Ts = 25e-6;
const int ODE45_M = 5;
    // const double DT = Ts/ODE45_M;

struct inputs
{
    std::vector<std::vector<int>> inputs_real;
    std::vector<int> inputs_vitruals;
};



}
#endif
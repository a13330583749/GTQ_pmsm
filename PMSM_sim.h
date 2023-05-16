#ifndef PMSM_sim
#define PMSM_sim
#include <utility>
#include <iostream>
#include "PMSM.h"
#include "inverter.h"
#include "speed_controller.h"
#include <cmath>
const auto abc2alpha = [](double a, double b, double c){return 2 * (a - 0.5 *b - 0.5 * c) / 3;};
const auto abc2beta = [](double a, double b, double c){return 2 * (std::sqrt(3))/ 2 * (b -  c) / 3 ;};
const auto alphabeta2a = [](double alpha, double beta){return 2 /3 * alpha;};
const auto alphabeta2b = [](double alpha, double beta){return 2 /3 * (-0.5 * alpha + (std::sqrt(3))/ 2 * beta );};
const auto alphabeta2c = [](double alpha, double beta){return 2 /3 * (-0.5 * alpha - (std::sqrt(3))/ 2 * beta );};
const auto alphabeta2d = [](double alpha, double beta, double theta){return std::cos(theta) * alpha + std::sin(theta) * beta;};
const auto alphabeta2q = [](double alpha, double beta, double theta){return -std::sin(theta) * alpha + std::cos(theta) * beta;};
const auto dq2alpha = [](double d, double q, double theta){return std::cos(theta) * d - std::sin(theta) * q;};
const auto dq2beta = [](double d, double q, double theta){return std::sin(theta) * d - std::cos(theta) * q;};

// const auto abc2d = [](const double&a, const double&b, const double& c, const double& theta)
//                     {}

namespace PanJL{
    #define SparseInverter ture

    const double Ts = 25e-6;
    const int ODE45_M = 5;
    // const double DT = Ts/ODE45_M;
}
#endif
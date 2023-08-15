#include "../PMSM_sim.h"

namespace PanJL {
    // Vdc先放在这里，不知道会不会有什么类中成员的事情
    const double Vdc = 100;
    const double Ts = 50e-6;
    const int ODE45_M = 5;

    // pmsm参数：
    const double Ld_ = 7e-3;
    const double Lq_ = 7e-3;
    const double F_ = 0.125;
    const double Rs_ = 2.98;
    double TL_ = 0;
    const double Bm_ = 1.1e-4;
    const double J_ = 4.7e-5;
    const int Pn_ = 2;

    double Ld_estimated = 0.7* Ld_;
    double Lq_estimated = 0.7* Lq_;
    double Rs_estimated = 1.3* Rs_;
    double F_estimated  =  F_;

    const double PI = 3.1415926536;

    const std::function<double(double, double, double)> abc2alpha = [](double a, double b, double c) -> double {
        return 2.0 * (a - 0.5 * b - 0.5 * c) / 3.0;
};

    const std::function<double(double, double, double)> abc2beta = [](double a, double b, double c) -> double {
        return 2.0 * (std::sqrt(3)) / 2.0 * (b - c) / 3.0;
    };

    const std::function<double(double, double)> alphabeta2a = [](double alpha, double beta) -> double {
        return  beta;
    };

    const std::function<double(double, double)> alphabeta2b = [](double alpha, double beta) -> double {
        return  (-0.5 * alpha + (std::sqrt(3.0)) / 2.0 * beta);
    };

    const std::function<double(double, double)> alphabeta2c = [](double alpha, double beta) -> double {
        return  (-0.5 * alpha - (std::sqrt(3.0)) / 2.0 * beta);
    };

    const std::function<double(double, double, double)> alphabeta2d = [](double alpha, double beta, double theta) -> double {
        return std::cos(theta) * alpha + std::sin(theta) * beta;
    };

    const std::function<double(double, double, double)> alphabeta2q = [](double alpha, double beta, double theta) -> double {
        return -std::sin(theta) * alpha + std::cos(theta) * beta;
    };

    const std::function<double(double, double, double)> dq2alpha = [](double d, double q, double theta) -> double {
        return std::cos(theta) * d - std::sin(theta) * q;
    };

    const std::function<double(double, double, double)> dq2beta = [](double d, double q, double theta) -> double {
        return std::sin(theta) * d + std::cos(theta) * q;
    };

    // 将abc变换为uvw
    const std::function<double(double, double, double)> abc2u = [](double a, double b, double c) -> double{
        return (1.0 / 3.0 * (2.0 * a - b - c ));
    };

    const std::function<double(double, double, double)> abc2v = [](double a, double b, double c) -> double{
        return (1.0 / 3.0 * (- a + 2.0 * b - c ));
    };

    const std::function<double(double, double, double)> abc2w = [](double a, double b, double c) -> double{
        return (1.0 / 3.0 * (- a - b + 2.0 * c ));
    };
}

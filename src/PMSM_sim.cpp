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
    double Rs_estimated = 0.7* Rs_;
    double F_estimated  = 0.7* F_;

    const double PI = 3.1415926536;
}

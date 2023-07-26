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

    const double PI = 3.1415926536;
}

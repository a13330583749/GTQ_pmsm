#include "../PMSM_sim.h"

const double J = 4.7e-05;
const double Pn = 2;
const double Lq = 7e-3;
const double Ld = 7e-3;
const double F = 0.125;
const double Rs = 2.98;
const double TL = 0;
const double Bm = 1.1e-04;



int main()
{
    PanJL::PMSM a;
    int x = a.init_PMSM(Ld, Lq, F, Bm, Rs, TL, Pn, J);
    PanJL::sparse_inverter b(100, 1e-4);
    auto abc2alpha = [](double a, double b, double c){return 2 * (a - 0.5 *b - 0.5 * c) / 3;};
    std::cout << abc2alpha(100, 0, 0) << "   " <<abc2alpha(1000, 0, 0) << std::endl ;
    return 0;
}

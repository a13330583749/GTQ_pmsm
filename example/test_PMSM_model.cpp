#include "../PMSM_sim.h"
#include "../system.h"

// const double J = 4.7e-05;
// const double Pn = 2;
// const double Lq = 7e-3;
// const double Ld = 7e-3;
// const double F = 0.125;
// const double Rs = 2.98;
// const double TL = 0;
// const double Bm = 1.1e-04;
// const int Pn = 1;


int main()
{
    PanJL::PMSM a;
    int x= -1;
    if(x = a.init_PMSM(Ld_, Lq_, F_, Bm_, Rs_, TL_, Pn_, J_) < 0)
        exit(0);
    PanJL::sparse_inverter b(100, 1e-4);
    auto abc2alpha = [](double a, double b, double c){return 2 * (a - 0.5 *b - 0.5 * c) / 3;};
    std::cout << abc2alpha(100, 0, 0) << "   " <<abc2alpha(1000, 0, 0) << std::endl ;

    PanJL::Plant plant(b);
    plant.init_PMSM(Ld_, Lq_, F_, Bm_, Rs_, TL_, Pn_, J_);
    std::vector<int> inputs{1,0,0,1,1};
    for(int i_=0; i_< 10000; i_++){
        plant.updata(inputs, PanJL::Ts);
        std::cout << " wr = "<<plant.get_wr() << std::endl ;
    }

    PanJL::FCSMPCer ctrl(100, 0);
    ctrl.init_PMSM(Ld_, Lq_, F_, Bm_, Rs_, TL_, Pn_, J_);
    // ctrl.controller(1.0, 2.0);
    return 0;
}

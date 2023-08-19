#include "../PMSM_sim.h"
#include <fcntl.h>
#include <fstream>
#include <fcntl.h>

const double V = 50;
const double simulation_time = 1.0;
const double omega = 300 * PanJL::PI;

int main(int argc, char* argv[])
{
    double Valpha, Vbeta;
    PanJL::SVPWM svpwm(PanJL::Vdc, 1e-4);
    for (double_t i = 0.0; i < simulation_time; i = i + PanJL::Ts)
    {
        Valpha = std::cos(omega * i);
        Vbeta  = std::cos(omega * i - PanJL::PI/ 2.0);
    }
    
}
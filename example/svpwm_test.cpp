#include "../PMSM_sim.h"
#include <fcntl.h>
#include <fstream>
#include <fcntl.h>
#include <fstream>

const double simulation_time = 1.0;
const double omega = 5 * 2 * PanJL::PI; // Valpha和Vbeta的频率
const double fpwm  = 2e-6;

int main(int argc, char* argv[])
{
    double Valpha, Vbeta, PWM_value;
    PanJL::SVPWM svpwm(PanJL::Vdc, fpwm);
    PanJL::PWMSignalGenerator PWM(fpwm);
    std::vector<int> Sabc;
    std::vector<double> Uabc;

    std::ofstream dataFile("../data/svpwm.txt");
    for (double_t i = 0.0; i < simulation_time; i = i + PanJL::Ts/20)
    {
        Valpha = 40  * std::cos(omega * i);
        Vbeta  = 40  * std::cos(omega * i - PanJL::PI/ 2.0);
        svpwm.calculation(Valpha, Vbeta);
        PWM_value = PWM.PWM_value(i);
        Sabc = svpwm.Tcmp_to_Sabc(PWM_value);
        Uabc = svpwm.Sabc_to_Uabc(Sabc);

        dataFile << i << " " << Uabc[0] << " " << Uabc[1] << " " << Uabc[2] << " " 
             << svpwm.Tcmp1 << " " << svpwm.Tcmp2 << " " << svpwm.Tcmp3 << " "
             << Sabc[0] << " " << Sabc[1] << " " << Sabc[2] << "\n";
    }
    dataFile.close();
    std::system("python3 ../example/python/svpwm.py");
}
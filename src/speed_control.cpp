#include "../PMSM_sim.h"
namespace PanJL{
double Speed_controller::updata(const double e)
{
    Increaments += e;
    auto outputs = Kp * e + Ki * Increaments * Ts + Kd * (e - error);
    error = e;
    return outputs;
}

Speed_controller::Speed_controller(const double& kp, const double& ki, const double& kd)
    :Kp(kp), Ki(ki), Kd(kd), Increaments(0), error(0){}

Speed_controller::Speed_controller(const double& kp, const double& ki, const double& kd, const double& increaments)
    :Kp(kp), Ki(ki), Kd(kd), Increaments(increaments), error(0){}
}
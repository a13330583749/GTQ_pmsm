#include "PMSM_sim.h"
namespace PanJL{
double speed_controller::updata(const double e)
{
    Increaments += e;
    auto outputs = Kp * e + Ki * Increaments * Ts + Kd * (e - error);
    error = e;
    return outputs;
}

speed_controller::speed_controller(const double& kp, const double& ki, const double& kd)
    :Kp(kp), Ki(ki), Kd(kd), Increaments(0), error(0){}

speed_controller::speed_controller(const double& kp, const double& ki, const double& kd, const double& increaments)
    :Kp(kp), Ki(ki), Kd(kd), Increaments(increaments), error(0){}
}
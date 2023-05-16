#include "PMSM_sim.h"
namespace PanJL{
double speed_controller::updata(const double& e)
{
    Increaments += e;
    auto outputs = Kp * e + Ki * Increaments * Ts + Kd * (e - error);
    error = e;
    return outputs;
}

}
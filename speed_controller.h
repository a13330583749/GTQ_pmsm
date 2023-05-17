#ifndef SPEED_CONTROLLER_H
#define SPEED_CONTROLLER_H
namespace PanJL{
class speed_controller
{
private:
    double Increaments;
    double Kp;
    double Ki;
    double Kd;
    double error;
public:
    speed_controller(const double& kp, const double& ki, const double& kd);
    speed_controller(const double& kp, const double& ki, const double& kd, const double& increaments);
    ~speed_controller() = default;

    double updata(const double e);
};


}
#endif
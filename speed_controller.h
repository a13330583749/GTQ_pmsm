#ifndef SPEED_CONTROLLER_H
#define SPEED_CONTROLLER_H
namespace PanJL{
class Speed_controller
{
private:
    
    double Kp;
    double Ki;
    double Kd;
    double Increaments;
    double error;
public:
    Speed_controller(const double& kp, const double& ki, const double& kd);
    Speed_controller(const double& kp, const double& ki, const double& kd, const double& increaments);
    ~Speed_controller() = default;

    double updata(const double e);
};


}
#endif
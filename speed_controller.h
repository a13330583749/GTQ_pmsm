#ifndef SPEED_CONTROLLER_H
#define SPEED_CONTROLLER_H
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
    double updata(const double& e);
};

speed_controller::speed_controller(const double& kp, const double& ki, const double& kd)
    :Kp(kp), Ki(ki), Kd(kd), error(0){}

speed_controller::speed_controller(const double& kp, const double& ki, const double& kd, const double& increaments)
    :Kp(kp), Ki(ki), Kd(kd), Increaments(increaments), error(0){}


#endif
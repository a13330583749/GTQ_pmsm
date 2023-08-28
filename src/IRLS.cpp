#include <./IRLS.h>
namespace PanJL
{
IRLS_parameter_identify::IRLS_parameter_identify()
{
    Iq_last_moment = 0;
    Id_last_moment = 0;
    P << 4 , 0 , 0 , 4;
    lambda = 1;
    this->get_Rho = [this](const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts) -> Eigen::Matrix<double, 2,  2>
    {
        Eigen::Matrix<double, 2,  2> result;
        result << Idq[1], Idq[0] * we + (Idq[1] - this->Iq_last_moment)/ Ts,
                  Idq[0], ((Idq[0] - this->Id_last_moment)/ Ts - Idq[1] * we);
        return result.transpose();
    };

    this->get_K = [this](const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts) -> Eigen::Matrix<double, 2, 2>
    {
        Eigen::Matrix<double, 2, 2> eyes;
        eyes << 1.0, 0.0,
            0.0, 1.0;
        return this->P * this -> get_Rho(Idq, Udq, we, Ts) 
            *(this->lambda * eyes + get_Rho(Idq, Udq, we, Ts).transpose() * this->P * get_Rho(Idq, Udq, we, Ts)).inverse();
    };

    // std::function<Eigen::Vector2<double>(const double& Ud, const double& Uq)> get_Y
    this -> get_Y = [this](const std::vector<double>& Udq, const double& we) -> Eigen::Vector2<double>
    {
        Eigen::Matrix<double,2 ,1> result;
        result << (Udq[1] - we * F_), Udq[0];
        return result;
    };

    this->get_theta = [this](const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts, const Eigen::Matrix<double, 2, 2>& K_) -> Eigen::Vector2<double>
    {
        Eigen::Vector2<double> Theta;
        Eigen::Vector2<double> result;
        // 这里对应了matlab中的get_theta，因为是直接就输入到了这里
        Theta << Rs_estimated, Ld_estimated;
        result = Theta + K_ * (this -> get_Y(Udq, we) - this->get_Rho(Idq, Udq, we, Ts).transpose() *  Theta);
        return result;
    };
}

void IRLS_parameter_identify::updata_P(const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts, const Eigen::Matrix<double, 2, 2>& K_)
{
    this->P = (this->P - K_ * this->get_Rho(Idq, Udq, we, Ts).transpose() * this->P) * (1 / this->lambda);    
}

void IRLS_parameter_identify::update(const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts)
{
    // 1. 更新K，但是之前的步骤是不是相互依赖，所以不行了，得想其他的办法才好
    auto K = this->get_K(Idq, Udq, we, Ts);
    // 2. 更新P
    updata_P(Idq, Udq, we, Ts, K);
    // std::cout << this->P << std::endl;
    // 3.获得最新的更新结果
    auto result = this->get_theta(Idq, Udq, we, Ts, K);
    Rs_estimated = result[0];
    Ld_estimated = result[1];
    Lq_estimated = result[1];
}
}
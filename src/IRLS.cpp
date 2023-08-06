#include <../IRLS.h>
namespace PanJL
{
IRLS_parameter_identify::IRLS_parameter_identify()
{
    P = Eigen::MatrixXd::Identity(rankA, rankA);
    lambda = 0.98;
    this->get_Rho = [this](const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts) -> Eigen::Matrix<double, rankA,  3>
    {
        Eigen::Matrix<double, rankA,  3> result;
        result << Idq[1], Idq[0] * we + (Idq[1] - this->Iq_last_moment)/ Ts,
                  Idq[0], (Idq[0] - this->Id_last_moment)/ Ts - Idq[1] * we;
        return result;
    };

    this->get_K = [this](const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts) -> Eigen::Vector2<double>
    {
        Eigen::MatrixXd eyes(2, 2);
        eyes << 1, 0,
            0, 1;
        return this->P * this -> get_Rho(Idq, Udq, we, Ts) 
            *(this->lambda * eyes + get_Rho(Idq, Udq, we, Ts).transpose() * this->P * get_Rho(Idq, Udq, we, Ts)).inverse();
    };

    // std::function<Eigen::Vector2<double>(const double& Ud, const double& Uq)> get_Y
    this -> get_Y = [this](const std::vector<double>& Udq, const double& we) -> Eigen::Vector2<double>
    {
        Eigen::Vector2<double> result;
        result << (Udq[1] - we * F_), Udq[0];
        return result;
    };

    this->get_theta = [this](const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts) -> Eigen::Vector2<double>
    {
        Eigen::Vector2<double> Theta;
        Eigen::Vector2<double> result;
        Theta << Rs_estimated, Ld_estimated;
        result = Theta + this->get_K(Idq, Udq, we, Ts) * ();

        return result;
    };
}

void IRLS_parameter_identify::updata_P(const std::vector<double>& Idq, const std::vector<double>& Udq,
                        const double& we, const double& Ts)
{
    this->P = (this->P - this->get_K(Idq, Udq, we, Ts) * this->get_Rho(Idq, Udq, we, Ts).transpose() * this->P) / this->lambda;
}

void IRLS_parameter_identify::update(const std::vector<double>& Iabc, const std::vector<double>& U)
{

}



}
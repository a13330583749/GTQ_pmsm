#include <../IRLS.h>
namespace PanJL
{
IRLS_parameter_identify::IRLS_parameter_identify()
{
    P = Eigen::MatrixXd::Identity(rankA, rankA);
    lambda = 0.98;
    this->get_Rho = [this](const std::vector<double>& Idq, const std::vector<std::vector<int>>& Udq,
                        const double& we, const double& Ts) -> Eigen::Matrix<double, rankA,  3>
    {
        Eigen::Matrix<double, rankA,  3> result;
        result << Idq[1], Idq[0] * we + (Idq[1] - this->Iq_last_moment)/ Ts,
                  Idq[0], (Idq[0] - this->Id_last_moment)/ Ts - Idq[1] * we;
        return result;
    };

    this->get_K = [this](const std::vector<double>& Idq, const std::vector<std::vector<int>>& Udq,
                        const double& we, const double& Ts) -> Eigen::Vector2<double>
    {
        Eigen::MatrixXd eyes(2, 2);
        eyes << 1, 0,
            0, 1;
        return this->P * this -> get_Rho(Idq, Udq, we, Ts) 
            *(this->lambda * eyes + get_Rho(Idq, Udq, we, Ts).transpose() * this->P * get_Rho(Idq, Udq, we, Ts)).inverse();
    };


    // this->get_theta = [this]() -> Eigen::Vector2<double>
    // {
    //     Eigen::Vector2<double> Theta;
    //     Theta << Rs_estimated, Ld_estimated;

    // };
}
void IRLS_parameter_identify::update(const std::vector<double>& Iabc, const std::vector<std::vector<int>>& U)
{

}

}
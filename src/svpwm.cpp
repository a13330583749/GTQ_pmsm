#include "../PMSM_sim.h"
namespace PanJL{
void SVPWM::calculation(const double& Valpha, const double& Vbeta)
{
    // Parameters statement
    double Vref1 = Vbeta;
    double Vref2 = (std::sqrt(3) * Valpha - Vbeta) / 2;
    double Vref3 = (-std::sqrt(3) * Valpha - Vbeta) / 2;

    // Sector calculation
    if(Vref1>0)
        this->sector = 1;
    if(Vref2>0)
        this->sector = this->sector + 2;
    if(Vref3>0)
        this->sector = this->sector + 4;
    
    // X Y Z calculation
    double X = std::sqrt(3) * Vbeta * (this->Tpwm) / (this->Vdc);
    double Y = (this->Tpwm) / (this->Vdc) * (3/2 * Valpha + std::sqrt(3)/2 * Vbeta);
    double Z = (this->Tpwm) / (this->Vdc) * (-3/2 * Valpha + std::sqrt(3)/2 * Vbeta);
    double T1, T2;

    // Duty ratio calculation
    switch (this->sector)
    {
    case 1:
        /* code */
        T1 = Z;
        T2 = Y;
        break;
    case 2:
        T1 = Y;
        T2 = -X;
        break;
    case 3:
        T1 = -Z;
        T2 = X;
        break;
    case 4:
        T1 = -X;
        T2 = Z;
        break;
    case 5:
        T1 = X;
        T2 = -Y;
    default:
        T1 = -Y;
        T2 = -Z;
        break;
    }

    // 防止过调制处理
    if(T1 + T2 > Tpwm){
        T1 = T1/ (T1 + T2);
        T2 = T2/ (T1 + T2);
    }

    double ta = (Tpwm - (T1 + T2))/ 4.0;
    double tb = ta + T1/2.0;
    double tc = tb + T2/2.0;

    // Duty ratio calculation
    switch (this->sector)
    {
    case 1:
        this->Tcmp1 = tb;
        this->Tcmp2 = ta;
        this->Tcmp3 = tc;
        break;
    case 2:
        this->Tcmp1 = ta;
        this->Tcmp2 = tc;
        this->Tcmp3 = tb;
        break;
    case 3:
        this->Tcmp1 = ta;
        this->Tcmp2 = tb;
        this->Tcmp3 = tc;
        break;
    case 4:
        this->Tcmp1 = tc;
        this->Tcmp2 = tb;
        this->Tcmp3 = ta;
        break;
    case 5:
        this->Tcmp1 = tc;
        this->Tcmp2 = ta;
        this->Tcmp3 = tb;
        break;
    case 6:
        this->Tcmp1 = tb;
        this->Tcmp2 = tc;
        this->Tcmp3 = ta;
        break;
    default:
        std::cerr << "时间序列出错";
        break;
    }

}

std::vector<int> SVPWM::Tcmp_to_Sabc(const double& PWM_value)
{
    int Sa = signal(Tcmp1, PWM_value);
    int Sb = signal(Tcmp2, PWM_value);
    int Sc = signal(Tcmp3, PWM_value);
    std::vector<int> result{Sa, Sb, Sc};
    return result;
}

std::vector<double> SVPWM::Sabc_to_Uabc(const std::vector<int>& Sabc)
{
    double Ua = Vdc / 3.0 * (2*Sabc[0] - Sabc[1] - Sabc[2]);
    double Ub = Vdc / 3.0 * (2*Sabc[1] - Sabc[0] - Sabc[2]);
    double Uc = Vdc / 3.0 * (2*Sabc[2] - Sabc[1] - Sabc[0]);
    return std::vector<double>{Ua, Ub, Uc};
}
}
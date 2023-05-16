#ifndef INVERTER_H
#define INVERTER_H

#include <functional>
namespace PanJL{

class sparse_inverter
{
private:
    int Sc1;
    int Sc2;
    int Sta;
    int Stb;
    int Stc;
    double Vdc;
    double u0;
    double u0_differential_equation(const double&, const double&, const double&);
    double C;

public:
    std::function<int(int)> Sm = [this](int Sabc){return Sc1 * Sabc + (Sabc - 1) * Sc2;};
    std::function<double(int)> Uabc = [this](int Sabc) -> double {return Sm(Sabc) * Vdc / 2 - Sm(Sabc) * Sm(Sabc) * u0;};
    sparse_inverter(double vdc, double c):Vdc(vdc), C(c){}
    void set_igbt(const int&, const int&, const int&, const int&, const int&);
    void updata_u0(const double&, const double&, const double&);
};

}

#endif
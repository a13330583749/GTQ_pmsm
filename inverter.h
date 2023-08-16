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

    
    
    double C;
protected:
    double Vdc;
    double u0;
    double u0_differential_equation(const double&, const double&, const double&);
    void updata_u0(const double&, const double&, const double&, const double& times);
public:
    std::function<int(int)> Sm = [this](int Sabc){return this->Sc1 * Sabc + (Sabc - 1) * this->Sc2;};
    // 这里有一个间接的调用Sm(Sabc)，其中使用再一次的调用
    // 注意这里调用的函数只是针对直流侧的电压，还没有转化为交流测的电压
    std::function<double(int)> Uabc = [this](int Sabc) -> double {return Sm(Sabc) * this->Vdc / 2 - Sm(Sabc) * Sm(Sabc) * this->u0;};
    sparse_inverter(double vdc, double c): C(c), Vdc(vdc), u0(0){}
    void set_igbt(const std::vector<int>&);
    inline const int& get_Sta(){return Sta;}
    inline const int& get_Stb(){return Stb;}
    inline const int& get_Stc(){return Stc;}
    const inline double& get_u0(){return u0;}
};

}

#endif
#include "../PMSM_sim.h"
#include "../system.h"
#include <fstream>
#include <fcntl.h>
#include <chrono>
extern const double PanJL::Ld_;
extern const double PanJL::Lq_;
extern const double PanJL::F_;
extern const double PanJL::Rs_;
// extern double PanJL::TL_;
extern const double PanJL::Bm_;
extern const double PanJL::J_;
extern const int PanJL::Pn_;
extern const double PanJL::Vdc;

int main(int argc, char *argv[])
{
    const double wr_ref = 100; // 设定速度；
    double KP, KI, KD;
    switch (argc) {
        case 1: {
            KP = 10;
            KI = 300;
            KD = 0;
            break;
        }
        case 2: {
            KP = std::atof(argv[1]);
            KI = 300;
            KD = 0;
            break;
        }
        case 3: {
            KP = std::atof(argv[1]);
            KI = std::atof(argv[2]); // Fixed the index from 1 to 2
            KD = 0;
            break;
        }
        case 4: {
            KP = std::atof(argv[1]);
            KI = std::atof(argv[2]); // Fixed the index from 1 to 2
            KD = std::atof(argv[3]);
            break;
        }
        default: {
            std::cerr << "filename + KP + KI" << std::endl;
            return 1; // Exiting with an error code
        }
    }
 
    std::ofstream outputFile("../data/sda_pmsm.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    PanJL::Plant plant(PanJL::Vdc, 750e-6);
    
    // 创建电流控制器并选择是否使用SDA
    PanJL::FCSMPCer current_trl(PanJL::Vdc, 0);
    current_trl.set_Long_horizon_sda_flag(true);

    PanJL::Speed_controller speed_pid(KP, KI, KD, 0);
    plant.init_PMSM(PanJL::Ld_, PanJL::Lq_, PanJL::F_, PanJL::Bm_, PanJL::Rs_, PanJL::TL_, PanJL::Pn_, PanJL::J_);
    plant.set_state_PMSM(0, 0, 0, 0);// 设置wr, id, iq, ele_theta
    current_trl.init_PMSM(PanJL::Ld_, PanJL::Lq_, PanJL::F_, PanJL::Bm_, PanJL::Rs_, PanJL::TL_, PanJL::Pn_, PanJL::J_);
    std::vector<std::vector<int>> inputs;

    double Iq_ref{0};

    // 获取程序开始执行的时间点
    auto start = std::chrono::high_resolution_clock::now();
    for (int i_ = 0; i_ < 1 / PanJL::Ts; i_++)
    {
        Iq_ref = speed_pid.updata(wr_ref - plant.get_wr());
        inputs = current_trl.controller(0, Iq_ref, plant.get_ele_theta(), plant.get_Iabc(), plant.get_wr(), PanJL::Ts, plant.get_u0());
        if (current_trl.get_flag_control_times())
        {
            plant.updata(inputs[0], PanJL::Ts);
        }
        else
        {
            plant.updata(inputs[0], PanJL::Ts / 2.0);
            plant.updata(inputs[1], PanJL::Ts / 2.0);
        }
        outputFile << plant.get_wr() << "," << plant.get_u0() << std::endl;
        if (i_ == static_cast<int>(1 / PanJL::Ts / 2))
        {
            plant.set_TL(1.1);    
        }
        
    }
    // 获取程序执行结束的时间点
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Program execution time: " << duration.count() << " milliseconds" << std::endl;
    outputFile.close();

    std::system("python3 ../example/python/sda_pmsm.py");
    // ctrl.controller(1.0, 2.0);
    return 0;
}
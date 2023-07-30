#include "../PMSM_sim.h"
#include "../system.h"
#include <fstream>
#include <fcntl.h>
#include <chrono>
#define kp  3
#define ki  0.02//(20000 * PanJL::Ts)
#define kd  0

extern const double PanJL::Ld_;
extern const double PanJL::Lq_;
extern const double PanJL::F_;
extern const double PanJL::Rs_;
extern double PanJL::TL_;
extern const double PanJL::Bm_;
extern const double PanJL::J_;
extern const int PanJL::Pn_;

int main()
{
    std::ofstream outputFile("data.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    PanJL::Plant plant(100, 750e-6);
    PanJL::FCSMPCer current_trl(100, 0);
    PanJL::Speed_controller speed_pid(kp, ki, kd, 0);
    plant.init_PMSM(PanJL::Ld_, PanJL::Lq_, PanJL::F_, PanJL::Bm_, PanJL::Rs_, PanJL::TL_, PanJL::Pn_, PanJL::J_);
    plant.set_state_PMSM(0, 0, 0, 0);

    // 设定不匹配参数：
    double Rs_plant = PanJL::Rs_ * 0.7;


    current_trl.init_PMSM(PanJL::Ld_, PanJL::Lq_, PanJL::F_, PanJL::Bm_, PanJL::Rs_, PanJL::TL_, PanJL::Pn_, PanJL::J_);
    std::vector<std::vector<int>> inputs;

    
    double Iq_ref{0};
    double wr_ref = 100;
     // 获取程序开始执行的时间点
    auto start = std::chrono::high_resolution_clock::now();
    // 仿真时间1s
    for(int i_=0; i_< 1.0/ PanJL::Ts; i_++){
        Iq_ref = speed_pid.updata(wr_ref - plant.get_wr());
        inputs = current_trl.controller(0, Iq_ref, plant.get_ele_theta(), plant.get_Iabc(), plant.get_wr(), PanJL::Ts, plant.get_u0());
        // plant.updata(inputs, PanJL::Ts);
        // std::cout << " wr = "<<plant.get_wr() << std::endl ;
        if(current_trl.get_flag_control_times()){
            plant.updata(inputs[0], PanJL::Ts);
        }else{
            plant.updata(inputs[0], PanJL::Ts/2.0);
            plant.updata(inputs[1], PanJL::Ts/2.0);
        }
        outputFile << plant.get_wr() << "," << plant.get_u0() << std::endl;

    }
    // 获取程序执行结束的时间点
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Program execution time: " << duration.count() << " milliseconds" << std::endl;
    outputFile.close();

    std::system("python3 ../example/python/onestep_without_delay.py");
    // ctrl.controller(1.0, 2.0);
    return 0;
}
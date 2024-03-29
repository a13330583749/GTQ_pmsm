#include "../PMSM_sim.h"
// #include "../system.h"
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

extern double PanJL::Ld_estimated;
extern double PanJL::Lq_estimated;
extern double PanJL::F_estimated;
extern double PanJL::Rs_estimated;

int main(int argc, char *argv[])
{
    const double wr_ref = 100; // 设定速度；
    // 设置速度环P,I,D参数
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
 
    std::ofstream outputFile("../data/irls.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    
    
    // 创建电流控制器并选择控制策略
    PanJL::FCSMPCer current_trl(PanJL::Vdc, 0);
    current_trl.set_control_method(2);
    // 创建速度控制器
    PanJL::Speed_controller speed_pid(KP, KI, KD, 0);
    // 创建对象
    PanJL::Plant plant(PanJL::Vdc, 750e-6);
    plant.init_PMSM(PanJL::Ld_, PanJL::Lq_, PanJL::F_, PanJL::Bm_, PanJL::Rs_, PanJL::TL_, PanJL::Pn_, PanJL::J_);
    plant.set_state_PMSM(0, 0, 0, 0);// 设置wr, id, iq, ele_theta
    if(current_trl.init_PMSM(PanJL::Ld_estimated, PanJL::Lq_estimated, PanJL::F_estimated, 
                            PanJL::Bm_, PanJL::Rs_estimated, PanJL::TL_, PanJL::Pn_, PanJL::J_) < 1);
        // std::cerr << "initial fail\n\r";
    // 创建辨识器
    PanJL::Identifier compensator;
    
    std::vector<std::vector<int>> inputs;
    std::vector<int> vir_Udq;
    double Iq_ref{0};
    bool compensator_flag = true;
    // 获取程序开始执行的时间点
    auto start = std::chrono::high_resolution_clock::now();
    for (int i_ = 0; i_ < 1.0 / PanJL::Ts; i_++) //1代表仿真时间为1second
    {
        Iq_ref = speed_pid.updata(wr_ref - plant.get_wr());
        inputs = current_trl.controller(0, Iq_ref, plant.get_ele_theta(), plant.get_Iabc(), plant.get_wr(), PanJL::Ts, plant.get_u0(), vir_Udq);
        if (current_trl.get_flag_control_times())
        {
            plant.updata(inputs[0], PanJL::Ts);
        }
        else
        {
            plant.updata(inputs[0], PanJL::Ts / 2.0);
            plant.updata(inputs[1], PanJL::Ts / 2.0);
        }
        // 进行参数辨识：
        if (static_cast<double>(i_) > 0.3/PanJL::Ts){
            if(compensator_flag){
                //辨识器初始化
                compensator_flag = false;
                compensator.init(plant.get_Iabc(), vir_Udq, PanJL::Ts, plant.get_wr() * PanJL::Pn_, 
                            PanJL::Vdc, plant.get_ele_theta(), plant.get_u0());    
            }
            else{
                // 参数辨识
                compensator.renew(plant.get_Iabc(), vir_Udq, PanJL::Ts, plant.get_wr() * PanJL::Pn_, 
                            PanJL::Vdc, plant.get_ele_theta(), plant.get_u0());
                // 更新控制器的参数
                current_trl.set_parameter_pmsm(PanJL::Ld_estimated,PanJL::Lq_estimated, PanJL::F_estimated, PanJL::Rs_estimated);
            }
        }
        outputFile << plant.get_wr() << "," << plant.get_u0() <<
            "," << PanJL::Ld_estimated << "," << PanJL::Rs_estimated <<std::endl;
        // if (i_ == static_cast<int>(1 / PanJL::Ts / 2))
        // {
        //     plant.set_TL(1.1);    
        // }    
    }
    // 获取程序执行结束的时间点
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Program execution time: " << duration.count() << " milliseconds" << std::endl;
    outputFile.close();

    std::system("python3 ../example/python/irls.py");
    // ctrl.controller(1.0, 2.0);
    return 0;
}
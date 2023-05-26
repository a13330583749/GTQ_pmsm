#include "../PMSM_sim.h"
#include "../system.h"
#include <fstream>
#include <fcntl.h>
#include <chrono>

#define kp  3
#define ki  0.02//(20000 * PanJL::Ts)
#define kd  0

PanJL::u_message SpeedPIDCallback(const PanJL::feedback_message& feedback) {
    double wr_ref = feedback.plant_wr; // 获取反馈消息中的 wr_ref
    double Iq_ref = speed_pid.update(wr_ref - plant.get_wr()); // 调用 speed_pid.update() 计算 Iq_ref
    // 调用 current_trl.controller() 获取控制信息
    u_message result = current_trl.controller(0, Iq_ref, plant.get_ele_theta(), plant.get_Iabc(), plant.get_wr(), PanJL::Ts, plant.get_u0());
    return result;
}

int main()
{
    // 假设服务器是在8888号端口上运行的
    PanJL::CONTROLLER controller(8888);

    std::ofstream outputFile("data_tcp.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    PanJL::Plant plant(100, 750e-6);
    PanJL::FCSMPCer current_trl(100, 0);
    PanJL::Speed_controller speed_pid(kp, ki, kd, 0);

    // PanJL::CallbackFunction 
    while (true)
    {
        PanJL::feedback_message feedback{
            
        }
    }
    

}
#include "../PMSM_sim.h"
#include "../system.h"
#include <fstream>
#include <fcntl.h>
#include <chrono>

#define kp  3
#define ki  0.02//(20000 * PanJL::Ts)
#define kd  0
#define wr_ref 100

// 这是整一个控制过程
class MyClass {
public:
    static PanJL::u_message CallbackFunction(const PanJL::feedback_message& message, 
        PanJL::FCSMPCer* current_trl, PanJL::Speed_controller* speed_pid) {
        // 使用 res、speed_pid 和 current_trl 进行处理

        // 调用成员函数
        double Iq_ref = speed_pid->updata(wr_ref - message.plant_wr);
        std::vector<std::vector<int>> inputs = current_trl->controller
            (0, Iq_ref, message.plant_ele_theta, message.plant_Iabc, 
            message.plant_wr, PanJL::Ts, message.plant_u0);

        // 创建并返回 u_message 对象
        PanJL::u_message result(current_trl->get_flag_control_times(), inputs);
        return result;
    }
};


int main()
{
    // 假设服务器是在8888号端口上运行的
    PanJL::CONTROLLER controller(8888);

    std::ofstream outputFile("data_tcp.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    // 创建对象的实例
    PanJL::FCSMPCer current_trl_instance(100, 0);
    PanJL::Speed_controller speed_pid_instance(kp, ki, kd, 0);
    current_trl_instance.init_PMSM(Ld_, Lq_, F_, Bm_, Rs_, TL_, Pn_, J_);

    controller.current_trl = &current_trl_instance;
    controller.speed_pid = &speed_pid_instance;
    controller.RegisterCallback(MyClass::CallbackFunction);

    controller.Start();
}
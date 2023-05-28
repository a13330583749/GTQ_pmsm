#include "../PMSM_sim.h"
#include <chrono>
#include <fstream>
#include <fcntl.h>
class MyPlant{
public:
    static PanJL::feedback_message CallbackFunction(const PanJL::u_message& u_messages, 
        PanJL::Plant* plant){
            if(u_messages.flag)
                plant->updata(u_messages.outputs[0], PanJL::Ts);
            else{
                plant->updata(u_messages.outputs[0], PanJL::Ts/2.0);
                plant->updata(u_messages.outputs[1], PanJL::Ts/2.0);
            }
            // std::cout << plant->get_wr() << " /n";
            PanJL::feedback_message feedback_messages;
            feedback_messages.Id_ref = 0;
            feedback_messages.plant_ele_theta = plant->get_ele_theta();
            feedback_messages.plant_Iabc = plant->get_Iabc();
            feedback_messages.plant_u0 = plant->get_u0();
            feedback_messages.plant_wr = plant->get_wr();
            
            //  << plant->get_wr() << std::endl;
            return feedback_messages;
        }
};

int main()
{
    std::ofstream outputFile("tcp.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    // 创建对象实例
    PanJL::Plant plant_instant(100, 750e-6);
    plant_instant.init_PMSM(Ld_, Lq_, F_, Bm_, Rs_, TL_, Pn_, J_);
    plant_instant.set_state_PMSM(0, 0, 0, 0);
    PanJL::PLANT_COM client("127.0.0.1", 8888);
    client.ptr_plant = &plant_instant;
    client.reserve = &outputFile;
    
    client.RegisterCallback(MyPlant::CallbackFunction);
    client.set_sim_time(1.0);
    // 启动客户端
    // 获取程序开始执行的时间点
    auto start = std::chrono::high_resolution_clock::now();
    client.Start();
    // 获取程序执行结束的时间点
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Program execution time: " << duration.count() << " milliseconds" << std::endl;
    std::system("python3 ../pyplot.py");
}
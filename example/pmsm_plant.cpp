#include "../PMSM_sim.h"

class MyPlant{
public:
    static PanJL::feedback_message CallbackFunction(const PanJL::u_message& u_messages, 
        PanJL::FCSMPCer* plant){
            if(u_messages.flag)
                plant->updata(u_messages.outputs[0], PanJL::Ts);
            else{
                plant->updata(u_messages.outputs[0], PanJL::Ts/2.0);
                plant->updata(u_messages.outputs[1], PanJL::Ts/2.0);
            }
            std::cout << plant->get_wr() << " /n";
            PanJL::feedback_message feedback_messages;
            feedback_messages.Id_ref = 0;
            feedback_messages.plant_ele_theta = plant->get_ele_theta();
            feedback_messages.plant_Iabc = plant->get_Iabc();
            feedback_messages.plant_u0 = plant->get_u0();
            feedback_messages.plant_wr = plant->get_wr();
            return feedback_messages;
        }
};

int main()
{
    // 创建对象实例
    PanJL::Plant plant_instant(100, 750e-6);
    // 启动客户端
    PanJL::PLANT_COM client("127.0.0.1", 8888);
    client.Start();
}
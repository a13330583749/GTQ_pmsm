#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
namespace PanJL{

// 对象向控制器发送的系统状态
struct feedback_message{
    double Id_ref;
    double plant_wr;
    double plant_ele_theta;
    double plant_u0;
    ::std::vector<double> plant_Iabc;
    
    feedback_message(const double& id_ref, const double& wr, const double& ele_theta,
        const double& u0,const ::std::vector<double>& Iabc):Id_ref(id_ref), plant_wr(wr),
        plant_ele_theta(ele_theta), plant_u0(u0), plant_Iabc(Iabc){}
    feedback_message() = default;
};

// 控制器向对象发送的控制信息
struct u_message{
    bool flag;
    ::std::vector<::std::vector<int>> outputs;
    u_message(const bool& times, const ::std::vector<::std::vector<int>>& u):flag(times),outputs(u){}
    u_message() = default;
};

typedef ::std::function<u_message(const feedback_message&, PanJL::FCSMPCer* current_trl,
 PanJL::Speed_controller* speed_pid)> CallbackFunctionCONTROLLER;

typedef ::std::function<feedback_message(const u_message&, PanJL::Plant* Plant)> CallbackFunctionPLANT;
class CONTROLLER {
public:
    CONTROLLER(int port);
    void Start();
    void RegisterCallback(CallbackFunctionCONTROLLER callback) {m_callbackfunction = callback;}
    // 添加成员变量指针
    PanJL::FCSMPCer* current_trl;
    PanJL::Speed_controller* speed_pid;
    
private:
    int m_port;
    int m_socket;
    void Bind();
    void Listen();
    void Accept();
    CallbackFunctionCONTROLLER m_callbackfunction;
    void HandleClient(int clientSocket);  
    ::std::vector<char> SerializeUMessage(const u_message& message);
};

class PLANT_COM {
public:
    PLANT_COM(const std::string& serverIP, int serverPort);
    void Start();
    void RegisterCallback(CallbackFunctionPLANT callback) {plant_m_callbackfunction = callback;}
    PanJL::Plant* ptr_plant;
    const inline void set_sim_time(const double& times){time = times;};
    ::std::ofstream* reserve;

private:
    std::string m_serverIP;
    int m_serverPort;
    CallbackFunctionPLANT plant_m_callbackfunction;
    ::std::vector<char> SerializeFeedbackMessage(const feedback_message& message);
    double time;

};

}
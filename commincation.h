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
    ::std::vector<::std::vector<int>> outputs;
    u_message(const ::std::vector<::std::vector<int>>& u):outputs(u){}
};

typedef ::std::function<u_message(const feedback_message&)> CallbackFunction;
class CONTROLLER {
public:
    CONTROLLER(int port);
    void Start();
    void RegisterCallback(CallbackFunction callback) {m_callbackfunction = callback;}
    
private:
    int m_port;
    int m_socket;
    void Bind();
    void Listen();
    void Accept();
    CallbackFunction m_callbackfunction;
    void HandleClient(int clientSocket);  
};

class EchoClient {
public:
    EchoClient(const std::string& serverIP, int serverPort);
    void Start();
    
private:
    std::string m_serverIP;
    int m_serverPort;
};

}
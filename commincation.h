#pragma once

#include <iostream>
#include <string>
namespace PanJL{


class EchoServer {
public:
    EchoServer(int port);
    void Start();
    
private:
    int m_port;
    int m_socket;
    void Bind();
    void Listen();
    void Accept();
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
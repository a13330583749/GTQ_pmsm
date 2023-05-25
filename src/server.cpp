
#include "../PMSM_sim.h"
namespace PanJL{
    
EchoServer::EchoServer(int port)
    : m_port(port), m_socket(0) {}

void EchoServer::Start() {
    Bind();
    Listen();
    Accept();
}

void EchoServer::Bind() {
    // 创建套接字并绑定端口
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(m_port);
    bind(m_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

void EchoServer::Listen() {
    // 监听端口
    listen(m_socket, 5);
    std::cout << "服务器已启动，正在监听端口 " << m_port << std::endl;
}

void EchoServer::Accept() {
    while (true) {
        // 接受客户端连接
        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(m_socket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        std::cout << "客户端已连接，地址: " << inet_ntoa(clientAddress.sin_addr) << ", 端口: " << ntohs(clientAddress.sin_port) << std::endl;

        // 处理客户端请求
        HandleClient(clientSocket);
        
        // 关闭客户端套接字
        close(clientSocket);
    }
}

void EchoServer::HandleClient(int clientSocket) {
    char buffer[1024];
    while (true) {
        // 接收客户端消息
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            break;
        }

        // 发送相同的消息回客户端
        send(clientSocket, buffer, bytesRead, 0);
    }
}

}



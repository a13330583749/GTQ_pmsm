
#include "../PMSM_sim.h"
namespace PanJL{

EchoClient::EchoClient(const std::string& serverIP, int serverPort)
    : m_serverIP(serverIP), m_serverPort(serverPort) {}

void EchoClient::Start() {
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 连接服务器
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(m_serverIP.c_str());
    serverAddress.sin_port = htons(m_serverPort);
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    std::cout << "已连接到服务器 " << m_serverIP << ":" << m_serverPort << std::endl;

    // 发送和接收消息
    std::string message;
    while (true) {
        std::cout << "请输入要发送的消息（输入\"quit\"退出）: ";
        std::getline(std::cin, message);

        if (message == "quit") {
            break;
        }

        // 发送消息
        send(clientSocket, message.c_str(), message.length(), 0);

        // 接收回复
        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            break;
        }

        std::cout << "收到回复: " << std::string(buffer, bytesRead) << std::endl;
    }

    // 关闭套接字
    close(clientSocket);
}

}

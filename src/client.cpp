
#include "../PMSM_sim.h"
namespace PanJL{

PLANT_COM::PLANT_COM(const std::string& serverIP, int serverPort)
    : m_serverIP(serverIP), m_serverPort(serverPort) {}

void PLANT_COM::Start() {
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 连接服务器
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(m_serverIP.c_str());
    serverAddress.sin_port = htons(m_serverPort);
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    std::cout << "已连接到服务器 " << m_serverIP << ":" << m_serverPort << std::endl;
    // 接收数据大小
    size_t dataSize;
    ssize_t bytesReceived;
    // 发送和接收消息
    std::string message;
    while (true) {
        bytesReceived = recv(clientSocket, reinterpret_cast<char*>(&dataSize), sizeof(size_t), 0);
        if (bytesReceived != sizeof(size_t)) {
            std::cerr << "接收数据大小失败" << std::endl;
            break;
        }
        // 分配缓冲区以接收数据
        std::vector<char> serializedData(dataSize);

        // 接收数据
        bytesReceived = recv(clientSocket, serializedData.data(), serializedData.size(), 0);

        if (bytesReceived != serializedData.size()) {
            std::cerr << "接收数据失败" << std::endl;
            break;
        }
        // 解析标志 flag
        PanJL::u_message result;
        char flagByte = serializedData[0];
        result.flag = (flagByte == 1);

        // 解析 outputs
        size_t offset = 1;
        while (offset < serializedData.size()) {
            std::vector<int> row;
            for (size_t i = 0; i < sizeof(int); ++i) {
                int value;
                memcpy(&value, serializedData.data() + offset, sizeof(int));
                row.push_back(value);
                offset += sizeof(int);
            }
            result.outputs.push_back(row);
        }
        
        // 进行对对象的更新


    }

    // 关闭套接字
    close(clientSocket);
}

}

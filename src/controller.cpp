
#include "../PMSM_sim.h"
namespace PanJL{
    
CONTROLLER::CONTROLLER(int port)
    : m_port(port), m_socket(0) {}

void CONTROLLER::Start() {
    Bind();
    Listen();
    std::cout << "Listen()结束 " << std::endl;
    Accept();
}

void CONTROLLER::Bind() {
    // 创建套接字并绑定端口
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(m_port);
    bind(m_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

void CONTROLLER::Listen() {
    // 监听端口
    listen(m_socket, 5);
    std::cout << "服务器已启动，正在监听端口 " << m_port << std::endl;
}

::std::vector<char> CONTROLLER::SerializeUMessage(const u_message& message) {
    ::std::vector<char> serializedData;
    
    // 将标志 flag 序列化为字节序列
    char flagByte = message.flag ? 1 : 0;
    serializedData.push_back(flagByte);
    
    // 获取 outputs 的维度信息
    char numDimensions = static_cast<char>(message.outputs.size());
    serializedData.push_back(numDimensions);
    for (const auto& row : message.outputs) {
        char dimensionSize = static_cast<char>(row.size());
        serializedData.push_back(dimensionSize);
    }
    
    // 将 outputs 序列化为字节序列
    for (const auto& row : message.outputs) {
        for (int value : row) {
            char* valueBytes = reinterpret_cast<char*>(&value);
            serializedData.insert(serializedData.end(), valueBytes, valueBytes + sizeof(int));
        }
    }
    // std::cout << "message.outputs.size() = " << message.outputs.size() << std::endl;
    return serializedData;
}

void CONTROLLER::Accept() {
    while (true) {
        // 接受客户端连接
        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(m_socket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        std::cout << "客户端已连接，地址: " << inet_ntoa(clientAddress.sin_addr) << ", 端口: " << ntohs(clientAddress.sin_port) << std::endl;

        // 处理客户端请求
        HandleClient(clientSocket);

    }
}

void CONTROLLER::HandleClient(int clientSocket) {
    char buffer[1024];
    while (true) {
        // 接收客户端消息
        // std::cout << "开始接受反馈信息";
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            break;
        }

        // 确保接收到的数据足够解析为 feedback_message
        if (bytesRead < sizeof(feedback_message)) {
            ::std::cerr << "接收到的数据长度不足，无法解析为 feedback_message 对象" << std::endl;
            break;
        }

        // 将 buffer 转换为 feedback_message 对象
        feedback_message message;
        char* ptr = buffer;

        // 解析 Id_ref
        memcpy(&message.Id_ref, ptr, sizeof(double));
        ptr += sizeof(double);      

        // 解析 plant_wr
        memcpy(&message.plant_wr, ptr, sizeof(double));
        ptr += sizeof(double);

        // 解析 plant_ele_theta
        memcpy(&message.plant_ele_theta, ptr, sizeof(double));
        ptr += sizeof(double);

        memcpy(&message.plant_u0, ptr, sizeof(double));
        ptr += sizeof(double);
        
        //解析Iabc
        size_t IabcSize = bytesRead - (ptr - buffer);
        size_t numElements = IabcSize / sizeof(double);
        message.plant_Iabc.resize(numElements);
        memcpy(message.plant_Iabc.data(), ptr, IabcSize);
        // std::cout << "   解析完成，当前的速度为：" << message.plant_wr << std::endl;

        if (m_callbackfunction) {
            // 调用回调函数获取 result
            u_message result = m_callbackfunction(message, current_trl, speed_pid);
            // 将 result 序列化为字节序列
            std::vector<char> serializedData = SerializeUMessage(result);
            // 发送序列化后的字节序列回客户端
            // 首先发送序列化后的数据大小（以字节为单位）
            size_t dataSize = serializedData.size();
            ssize_t bytesSent = send(clientSocket, reinterpret_cast<char*>(&dataSize), sizeof(size_t), 0);
            if (bytesSent != sizeof(size_t)) {
                std::cerr << "发送数据大小失败" << std::endl;
                break;
            }
            // 然后发送序列化后的数据
            bytesSent = send(clientSocket, serializedData.data(), serializedData.size(), 0);
            if (bytesSent != serializedData.size()) {
                std::cerr << "发送数据失败" << std::endl;
                break;
            }
        }

    }
    close(clientSocket);
}

}
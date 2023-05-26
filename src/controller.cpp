
#include "../PMSM_sim.h"
namespace PanJL{
    
CONTROLLER::CONTROLLER(int port)
    : m_port(port), m_socket(0) {}

void CONTROLLER::Start() {
    Bind();
    Listen();
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

::std::vector<char> SerializeUMessage(const u_message& u) {
    ::std::vector<char> buffer;

    // 将 outputs 的大小作为前缀写入 buffer
    size_t numOutputs = u.outputs.size();
    buffer.insert(buffer.end(), reinterpret_cast<const char*>(&numOutputs), reinterpret_cast<const char*>(&numOutputs) + sizeof(size_t));

    // 将 outputs 的数据写入 buffer
    for (const auto& output : u.outputs) {
        // 将每个内部向量的大小作为前缀写入 buffer
        size_t numElements = output.size();
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(&numElements), reinterpret_cast<const char*>(&numElements) + sizeof(size_t));

        // 将内部向量的数据写入 buffer
        buffer.insert(buffer.end(), reinterpret_cast<const char*>(output.data()), reinterpret_cast<const char*>(output.data()) + numElements * sizeof(int));
    }

    return buffer;
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

        memcmp(&message.plant_u0, ptr, sizeof(double));
        ptr += sizeof(double);
        
        //解析Iabc
        size_t IabcSize = bytesRead - (ptr - buffer);
        size_t numElements = IabcSize / sizeof(double);
        message.plant_Iabc.resize(numElements);
        memcpy(message.plant_Iabc.data(), ptr, IabcSize);

        if(m_callbackfunction){
            u_message result = m_callbackfunction(message);
            
            // 将 u_message 对象序列化为字节序列
            std::vector<char> serializedData = SerializeUMessage(result);

            // 发送序列化后的字节序列回客户端
            send(clientSocket, serializedData.data(), serializedData.size(), 0);

        }
        // 发送相同的消息回客户端
        send(clientSocket, buffer, bytesRead, 0);
    }
}

}




#include "../PMSM_sim.h"
namespace PanJL{

PLANT_COM::PLANT_COM(const std::string& serverIP, int serverPort)
    : m_serverIP(serverIP), m_serverPort(serverPort) {}

std::vector<char> PLANT_COM::SerializeFeedbackMessage(const feedback_message& message) {
    std::vector<char> serializedData;
    size_t dataSize = sizeof(double) * 4 + sizeof(size_t) + message.plant_Iabc.size() * sizeof(double);
    serializedData.resize(dataSize);

    char* ptr = serializedData.data();

    // 序列化 Id_ref
    memcpy(ptr, &message.Id_ref, sizeof(double));
    ptr += sizeof(double);

    // 序列化 plant_wr
    memcpy(ptr, &message.plant_wr, sizeof(double));
    ptr += sizeof(double);

    // 序列化 plant_ele_theta
    memcpy(ptr, &message.plant_ele_theta, sizeof(double));
    ptr += sizeof(double);

    // 序列化 plant_u0
    memcpy(ptr, &message.plant_u0, sizeof(double));
    ptr += sizeof(double);

    // 序列化 plant_Iabc
    size_t IabcSize = message.plant_Iabc.size() * sizeof(double);
    memcpy(ptr, message.plant_Iabc.data(), IabcSize);

    return serializedData;
}


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
    int i = 0;

    // 首先需要先发送一次数据才对
    /*
        feedback_message(const double& id_ref, const double& wr, const double& ele_theta,
        const double& u0,const ::std::vector<double>& Iabc):Id_ref(id_ref), plant_wr(wr),
        plant_ele_theta(ele_theta), plant_u0(u0), plant_Iabc(Iabc){}*/
    PanJL::feedback_message first_message{0, ptr_plant->get_wr(), ptr_plant->get_ele_theta(),
        ptr_plant->get_u0(), ptr_plant->get_Iabc()};
    std::vector<char> serializedFeedback = SerializeFeedbackMessage(first_message);
    send(clientSocket, serializedFeedback.data(), serializedFeedback.size(), 0);
    while (i < time / PanJL::Ts) {
        // std::cout << "i =  " << i  << " 等待接受数据 "<< std::endl;

        bytesReceived = recv(clientSocket, reinterpret_cast<char*>(&dataSize), sizeof(size_t), 0);
        // std::cout << "接受数据完毕 " << std::endl;
        if (bytesReceived != sizeof(size_t)) {
            std::cout << "接收数据大小失败, bytesReceived = " << bytesReceived << std::endl;
            exit(0);
        }
        // 分配缓冲区以接收数据

        std::vector<char> serializedData(dataSize);
        // 接收数据
        bytesReceived = recv(clientSocket, serializedData.data(), serializedData.size(), 0);
        // std::cout << "接受数据  "<< std::endl;
        if (bytesReceived != serializedData.size()) {
            std::cerr << "接收数据失败" << std::endl;
            break;
        }


        // 解析标志 flag
        PanJL::u_message result;
        char flagByte = serializedData[0];
        result.flag = (flagByte == 1);

        // std::cout << "flag =  " << result.flag << std::endl; 
        // 解析 outputs
        size_t offset = 2;
        size_t numDimensions = serializedData[1];
        result.outputs.resize(numDimensions);
        offset += numDimensions;
        for (size_t dim = 0; dim < numDimensions; ++dim) {
            int dimensionSize = serializedData[dim + 2];
            size_t dimSize = static_cast<size_t>(dimensionSize);  // 将 dimensionSize 转换为 size_t 类型
            for (size_t i = 0; i < dimSize; ++i) {
                int value;
                memcpy(&value, serializedData.data() + offset, sizeof(int));  // 使用正确的 offset
                result.outputs[dim].push_back(value);
                offset += sizeof(int);  // 更新偏移量
            }
        }
        // 进行对对象的更新
        PanJL::feedback_message fdback_message = plant_m_callbackfunction(result, ptr_plant);
        serializedFeedback = SerializeFeedbackMessage(fdback_message);
        // 发送序列化后的字节序列回服务器
        send(clientSocket, serializedFeedback.data(), serializedFeedback.size(), 0);
        i++;

        *reserve << std::to_string(fdback_message.plant_wr) << std::endl;
    }

    // 关闭套接字
    close(clientSocket);
}

}

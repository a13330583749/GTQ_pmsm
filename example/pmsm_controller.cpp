#include "../PMSM_sim.h"
#include "../system.h"
#include <fstream>
#include <fcntl.h>
#include <chrono>

#define kp  3
#define ki  0.02//(20000 * PanJL::Ts)
#define kd  0

int main()
{
    // 假设服务器是在8888号端口上运行的
    PanJL::CONTROLLER controller(8888);

    std::ofstream outputFile("data_tcp.txt", std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }
}
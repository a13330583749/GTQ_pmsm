#include "../PMSM_sim.h"

int main() {
    // 启动服务器
    PanJL::EchoServer server(8888);
    server.Start();

    return 0;
}

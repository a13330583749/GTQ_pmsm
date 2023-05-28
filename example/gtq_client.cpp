#include "../PMSM_sim.h"

int main() {
    // 启动客户端
    PanJL::PLANT_COM client("127.0.0.1", 8888);
    client.Start();

    return 0;
}

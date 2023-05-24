#include <iostream>
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io;
    boost::asio::serial_port port(io); // 创建串口对象

    try {
        port.open("/dev/ttyUSB0"); // 打开串口设备
        port.set_option(boost::asio::serial_port_base::baud_rate(115200)); // 设置波特率
        port.set_option(boost::asio::serial_port_base::character_size(8)); // 设置数据位
        port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none)); // 设置奇偶校验位
        port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one)); // 设置停止位

        std::string message = "Hello, world!";
        boost::asio::write(port, boost::asio::buffer(message)); // 发送数据

        std::cout << "Data sent: " << message << std::endl;

        port.close();
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

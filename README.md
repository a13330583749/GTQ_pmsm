# GTQ_pmsm
使用C++的PMSM仿真

预计目标：
1. 完成单步FCS-MPC控制；
2. 加入延迟补偿
3. 加入通讯协议，完成半实物仿真
4. 加入SDA算法
5. 加入速度观测器
6. 将逆变器模型更换了中点型钳位三电平逆变器，PWM的仿真支持
7. ....
---

完成TCP的通讯，主要的德debug时间在字节序的地方，因为使用了`vector<vector<int>>`的数据结构，所以在传递的时候就出现了问题，主要自己是怎么放的，怎么解析，这个过程自己要清楚。

使用图片的结果，需要使用33.44分钟。

![](TCP.png "图片title")


---

在MCU与PC通讯的时候需要把防火墙关闭。

---

在wsl2中使用串口与控制器（单片机）通讯

教程：https://learn.microsoft.com/zh-cn/windows/wsl/connect-usb

1. 首先需要在Windows下安装USBIPD-WIN，在Linux 中安装 USBIP 工具和硬件数据库。
2. 在管理员模式的powershell下`usbipd wsl list `查看现在和Windows连接的串口设备
3. 输入`usbipd wsl attach --busid <busid>`来将设备切换到wsl2中。
4. 就可以在wsl2中输入lsusb查看usb设备了。（你应会看到刚刚附加的设备，并且能够使用常规 Linux 工具与之交互。 根据你的应用程序，你可能需要配置 udev 规则以允许非根用户访问设备。）


使用`#include <boost/asio.hpp>`进行串口通讯


2023/05/23 潘继良

---

现在还在弄第一部分

这个仿真之前用于matlab中已经成功运行，因为使用了syms工具箱和为了之后在实物平台可以的测试，使用C++重新写，同时复习、实践c++中的知识点。

2023/05/18 潘继良



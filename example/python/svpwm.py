import numpy as np
import matplotlib.pyplot as plt

# 读取数据文件
data = np.loadtxt('../data/svpwm.txt')

# 提取数据列
time = data[:, 0]
Ua = data[:, 1]
Ub = data[:, 2]
Uc = data[:, 3]
Tcmp1 = data[:, 4]
Tcmp2 = data[:, 5]
Tcmp3 = data[:, 6]
Sa = data[:, 7]
Sb = data[:, 8]
Sc = data[:, 9]

# 绘制图形
plt.figure(figsize=(10, 8))

plt.subplot(2, 1, 1)
plt.plot(time, Ua, label='Ua')
plt.plot(time, Ub, label='Ub')
plt.plot(time, Uc, label='Uc')
plt.xlabel('Time')
plt.ylabel('Voltage')
plt.legend()

plt.subplot(2, 1, 2)
plt.plot(time, Tcmp1, label='Tcmp1')
plt.plot(time, Tcmp2, label='Tcmp2')
plt.plot(time, Tcmp3, label='Tcmp3')
plt.xlabel('Time')
plt.ylabel('Tcmp')
plt.legend()

# plt.subplot(3, 1, 3)
# plt.plot(time, Sa, label='Sa')
# plt.plot(time, Sb, label='Sb')
# plt.plot(time, Sc, label='Sc')
# plt.xlabel('Time')
# plt.ylabel('Switch State')
# plt.legend()

plt.tight_layout()
plt.show()

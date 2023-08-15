import matplotlib.pyplot as plt
import numpy as np

f = open("../data/irls.txt", "r")
# f = open("tcp.txt", "r")
txt_tables = []
line = f.readline()
while line:
    txt_data = [float(x) for x in line.strip().split(',')]
    # print(txt_data)  # 添加这一行进行调试输出
    txt_tables.append(txt_data)
    line = f.readline()

txt_arrays = np.array(txt_tables)
lens = len(txt_arrays)
t = np.array(range(0, lens))

# Close the file after reading the data
f.close()

# Create a figure and four subplots (4 rows, 1 column)
fig, (ax1, ax2, ax3, ax4) = plt.subplots(4, 1, sharex=True)

# Plot the columns of txt_arrays on the subplots
ax1.plot(t, txt_arrays[:, 0])
ax1.set_ylabel('wr')

ax2.plot(t, txt_arrays[:, 1])
ax2.set_ylabel('u0')

ax3.plot(t, txt_arrays[:, 2])
ax3.set_ylabel('Ls')

ax4.plot(t, txt_arrays[:, 3])
ax4.set_xlabel('Index')
ax4.set_ylabel('Rs')

# Show the plot
plt.show()

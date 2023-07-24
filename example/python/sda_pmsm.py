import matplotlib.pyplot as plt
import numpy as np

f = open("../data/sda_pmsm.txt", "r")
# f = open("tcp.txt", "r")
txt_tables = []
line = f.readline()
while line:
    txt_data = eval(line)
    txt_tables.append(txt_data)
    line = f.readline()

txt_arrays = np.array(txt_tables)
lens = len(txt_arrays)
t = np.array(range(0, lens))

# Close the file after reading the data
f.close()

# Create a figure and two subplots (2 rows, 1 column)
fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)

# Plot the first column of txt_arrays on the first subplot (top plot)
ax1.plot(t, txt_arrays[:, 0])
ax1.set_ylabel('wr')

# Plot the second column of txt_arrays on the second subplot (bottom plot)
ax2.plot(t, txt_arrays[:, 1])
ax2.set_xlabel('Index')
ax2.set_ylabel('u0')

# Show the plot
plt.show()

# plt.plot(50e-6 * t, txt_arrays[:, 0])
# plt.xlabel('times/s')
# plt.ylabel('w_r/rad/s')
# plt.savefig('sda_pmsm.png')
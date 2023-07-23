import matplotlib.pyplot as plt
import numpy as np

f = open("../build/data.txt", "r")
# f = open("tcp.txt", "r")
txt_tables = []
line = f.readline()
while line:
    txt_data = eval(line)
    txt_tables.append(txt_data)
    line = f.readline()

txt_arrays = np.array(txt_tables)
lens = txt_arrays.size
t = np.array(range(0, lens))

# plt.plot(txt_arrays[:,0])
plt.plot(t, txt_arrays)

plt.show()
f.close()
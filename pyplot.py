import matplotlib.pyplot as plt
import numpy as np

f = open("data.txt", "r")
txt_tables = []
line = f.readline()
while line:
    txt_data = eval(line)
    txt_tables.append(txt_data)
    line = f.readline()
txt_arrays = np.array(txt_tables)
plt.plot(txt_arrays[:,0])
plt.show()
f.close()
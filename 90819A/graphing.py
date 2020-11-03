import matplotlib.pyplot as plt
import numpy as np

x = []
leftDesired = []
leftActual = []
rightDesired = []
rightActual = []

count = 0

f = open("log.txt", "r")
for line in f.readlines():
    print(line)
    line = line.strip(".")
    line = line.split(",")
    x.append(count)
    leftDesired.append(line[0])
    rightDesired.append(line[1])
    leftActual.append(line[2])
    rightActual.append(line[3])
    count += 10

fig, (ax1, ax2) = plt.subplots(2)
x1 = np.asarray(x, dtype=np.float32)
np1 = np.asarray(leftDesired, dtype=np.float32)
np2 = np.asarray(leftActual, dtype=np.float32)
np3 = np.asarray(rightDesired, dtype=np.float32)
np4 = np.asarray(rightActual, dtype=np.float32)

ax1.plot(x1, np1, 'r')
ax1.plot(x1, np2, 'b')

ax2.plot(x1, np3, 'r')
ax2.plot(x1, np4, 'b')

plt.show()

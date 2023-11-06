import numpy as np
import matplotlib.pyplot as plt

X_MAX = 100
Y_MAX = 100
Z_MAX = 200
CELL_SIZE = 10

data = np.loadtxt("visualization/energyGrid.txt")
data3D = data.T.reshape((int(Z_MAX/CELL_SIZE), int(Y_MAX/CELL_SIZE), int(X_MAX/CELL_SIZE)))
hm = np.sum(data3D, axis=2)

x, y = np.zeros(100), np.zeros(100)
yval = -1
for i in range(len(x)):
    x[i] = i%10
    if not (i%10):
        yval += 1
    y[i] = yval%10

plt.imshow(hm, cmap=plt.cm.viridis, origin='lower', extent=(0, X_MAX, 0, Z_MAX))
plt.colorbar(label='Total E deposited')
plt.show()

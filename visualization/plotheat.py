import numpy as np
import matplotlib.pyplot as plt

X_MAX, Y_MAX, Z_MAX, CELL_SIZE, _ = np.loadtxt("visualization/energyGrid.txt", max_rows=1, unpack=True)

data = np.loadtxt("visualization/energyGrid.txt", skiprows=1)
data3D = data.T.reshape((int(Z_MAX/CELL_SIZE), int(X_MAX/CELL_SIZE), int(Y_MAX/CELL_SIZE)))
hm = np.sum(data3D, axis=2)


fig, ax = plt.subplots()
im = ax.imshow(hm, cmap=plt.cm.viridis, origin='lower', extent=(0, X_MAX, 0, Z_MAX), aspect='auto')
fig.colorbar(im, label='Total E deposited', ax=ax)
ax.set_xlabel('x')
ax.set_ylabel('z')
plt.show()

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

X_MAX = 100
Y_MAX = 100
Z_MAX = 200
CELL_SIZE = 10
N = int(X_MAX*Y_MAX*Z_MAX/CELL_SIZE**3)
nx = int(X_MAX/CELL_SIZE)
ny = int(Y_MAX/CELL_SIZE)
nz = int(Z_MAX/CELL_SIZE)

data = np.loadtxt("visualization/energyGrid.txt")

z = np.repeat(np.arange(0, Z_MAX - Z_MAX % CELL_SIZE, CELL_SIZE), nx*ny)
y = np.tile(np.repeat(np.arange(0, Y_MAX - Y_MAX %
            CELL_SIZE, CELL_SIZE), nx), nz)
x = np.tile(np.arange(0, X_MAX - X_MAX % CELL_SIZE, CELL_SIZE), ny*nz)

dataflat = data.T.flatten()
mask = (dataflat > 20).nonzero()
x = x[mask]
y = y[mask]
z = z[mask]
max = dataflat.max()
markersize = (dataflat[mask])/max*250
# Create a 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z, s=markersize, c=dataflat[mask], cmap=plt.cm.plasma)


# Set labels for each axis
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

# Show the plot
plt.show()

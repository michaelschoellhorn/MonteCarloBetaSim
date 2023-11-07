import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# get constants
X_MAX, Y_MAX, Z_MAX, CELL_SIZE, _ = np.loadtxt(
    "visualization/energyGrid.txt", max_rows=1, skiprows=1, unpack=True)
N = int(X_MAX*Y_MAX*Z_MAX/CELL_SIZE**3)
nx = int(X_MAX/CELL_SIZE)
ny = int(Y_MAX/CELL_SIZE)
nz = int(Z_MAX/CELL_SIZE)

# load data
data = np.loadtxt("visualization/energyGrid.txt", skiprows=3)

# setup positions for plotting
x = np.repeat(np.arange(0, X_MAX - X_MAX % CELL_SIZE, CELL_SIZE), nz*ny)
y = np.tile(np.repeat(np.arange(0, Y_MAX - Y_MAX %
            CELL_SIZE, CELL_SIZE), nz), nx)
z = np.tile(np.arange(0, Z_MAX - Z_MAX % CELL_SIZE, CELL_SIZE), ny*nx)

# modify data to only plot energies over certain minimal value
dataflat = data.flatten()
mask = (dataflat > 50).nonzero()
x = x[mask]
y = y[mask]
z = z[mask]

# Create a 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
max = dataflat.max()
markersize = (dataflat[mask])/max*250
c = ax.scatter(x, y, z, s=markersize, c=dataflat[mask], cmap=plt.cm.plasma)


# Formatting the plot
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
ax.set_zlabel(r'$z$')
ax.set_title('energy deposition 3D')

fig.colorbar(c, label=r'$E_{tot}$ in $MeV$', shrink=0.65, pad=0.12)

# Show the plot
plt.show()

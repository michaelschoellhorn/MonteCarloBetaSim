import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# --------------------- CONSTANTS ---------------------
# Constants to modify by user
E_VIS = 50  # The minimal energy with which a cell is considered for plotting

# Paths to datafiles
DATA_PATH = 'visualization/'
FILENAME = 'energyGrid.txt'

# Load simulation constants
try:
    X_MAX, Y_MAX, Z_MAX, CELL_SIZE, _ = np.loadtxt(
        DATA_PATH+FILENAME, max_rows=1, skiprows=1, unpack=True)

except FileNotFoundError:
    print(
        "plot.py can't find datafile {filename_constants} for loading simulation constants\nPlease check naming or OUTPUT_PATH variable in src/globals.cpp")

N = int(X_MAX*Y_MAX*Z_MAX/CELL_SIZE**3)
NX = int(X_MAX/CELL_SIZE)
NY = int(Y_MAX/CELL_SIZE)
NZ = int(Z_MAX/CELL_SIZE)
# ---------------------- xxxxxxxx --------------------

# ---------------------- Plot data -------------------
# Load data
data = np.loadtxt("visualization/energyGrid.txt", skiprows=3)

# Setup positions for plotting
x = np.repeat(np.arange(0, X_MAX - X_MAX % CELL_SIZE, CELL_SIZE), NZ*NY)
y = np.tile(np.repeat(np.arange(0, Y_MAX - Y_MAX %
            CELL_SIZE, CELL_SIZE), NZ), NX)
z = np.tile(np.arange(0, Z_MAX - Z_MAX % CELL_SIZE, CELL_SIZE), NY*NX)

# Modify data to only plot energies over certain minimal value
dataflat = data.flatten()
mask = (dataflat > E_VIS).nonzero()
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
# ---------------------- xxxxxx --------------------

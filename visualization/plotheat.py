import numpy as np
import matplotlib.pyplot as plt

# --------------- Constants -----------------
# Paths to datafiles
DATA_PATH = 'visualization/'
FILENAME = 'energyGrid.txt'

# Loading simulation constants
try:
    X_MAX, Y_MAX, Z_MAX, CELL_SIZE, _ = np.loadtxt(
        DATA_PATH + FILENAME, max_rows=1, skiprows=1, unpack=True)

except FileNotFoundError:
    print(
        f"plot.py can't find datafile {FILENAME} for loading simulation constants\nPlease check naming or OUTPUT_PATH variable in src/globals.cpp")
# --------------- xxxxxxxx ------------------

# load and modify data
data = np.loadtxt(DATA_PATH + FILENAME, skiprows=3)
data3D = data.T.reshape(
    (int(Z_MAX/CELL_SIZE), int(X_MAX/CELL_SIZE), int(Y_MAX/CELL_SIZE)))
hm = np.sum(data3D, axis=2)

# setup figure and plot
fig, ax = plt.subplots()
im = ax.imshow(hm, cmap=plt.cm.viridis, origin='lower',
               extent=(0, X_MAX, 0, Z_MAX), aspect='auto')
fig.colorbar(im, label=r'$E_{total}$ in $MeV$', ax=ax)
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$z$')
ax.set_title(r'energy deposition')
plt.show()

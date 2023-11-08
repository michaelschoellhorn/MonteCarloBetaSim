import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors as colors
from mpl_toolkits.mplot3d.art3d import Line3DCollection

# --------------- Constants -----------------
# Paths to datafiles
DATA_PATH = 'visualization/'
FILENAME_COORDS = 'coordinates.txt'
FILENAME_CONSTANTS = 'energyGrid.txt'

# Loading simulation constants
try:
    X_MAX, Y_MAX, Z_MAX, CELL_SIZE, _ = np.loadtxt(
        DATA_PATH + FILENAME_CONSTANTS, max_rows=1, skiprows=1, unpack=True)

except FileNotFoundError:
    print(
        f"plot.py can't find datafile {FILENAME_CONSTANTS} for loading simulation constants\nPlease check naming or OUTPUT_PATH variable in src/globals.cpp")
# --------------- xxxxxxxx ------------------

# Loading data
try:
    with open(DATA_PATH + FILENAME_COORDS, 'r') as file:
        line_blocks = file.read().strip().split('\n\n')

except FileNotFoundError:
    print(
        f"plot.py can't find datafile {FILENAME_COORDS}\nPlease check naming or OUTPUT_PATH variable in src/globals.cpp")


# ---------------- Plotting data --------------------
# Initialize 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Modify data
lines = []
energy = []
for i in range(len(line_blocks)):
    # Split each line block into coordinates
    coordinates = line_blocks[i].split('\n')
    x_block, y_block, z_block, e_block = zip(
        *(map(float, coord.split()) for coord in coordinates))
    line = []
    for j in range(len(x_block)-1):
        energy.append(e_block[j])
        line.append([x_block[j], y_block[j], z_block[j]])
        line.append([x_block[j+1], y_block[j+1], z_block[j+1]])
        lines.append(line)
        line = []

# Convert the list of line segments to numpy arrays
lines = np.array(lines)
energy = np.array(energy)

# Create a Normalize object to map float values to the range [0, 1]
norm = colors.Normalize(vmin=min(energy), vmax=max(energy))

# Create a 3D Line3DCollection from the line segments
lc = Line3DCollection(lines, linewidth=1.0, cmap=plt.cm.viridis, norm=norm)
lc.set_array(np.array(energy))
ax.add_collection3d(lc)

# Add a colorbar to show the mapping of line segments to colors
fig.colorbar(lc, ax=ax, label='electron energy')

# Set labels and title
ax.set_xlim(0, X_MAX)
ax.set_ylim(0, Y_MAX)
ax.set_zlim(0, Z_MAX)

ax.set_xlabel('x position')
ax.set_ylabel('y position')
ax.set_zlabel('z position')
ax.set_title('Path of electrons in matter')

# Show the plot
plt.show()
# ------------------ xxxxxxx -------------------------

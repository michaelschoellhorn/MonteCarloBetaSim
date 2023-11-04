import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors as colors
from mpl_toolkits.mplot3d.art3d import Line3DCollection


datapath = 'visualization/'
filename = 'coordinates.txt'

try:
    # Read data from the file
    with open(datapath + filename, 'r') as file:
        line_blocks = file.read().strip().split('\n\n')

    # Initialize 3D plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Plot lines from the data blocks
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

    energy = np.array(energy)
    # Convert the list of line segments to a numpy array
    lines = np.array(lines)

    # Create a Normalize object to map float values to the range [0, 1]
    norm = colors.Normalize(vmin=min(energy), vmax=max(energy))

    # Create a 3D Line3DCollection from the line segments
    lc = Line3DCollection(lines, linewidth=1.0, cmap=plt.cm.viridis, norm=norm)
    lc.set_array(np.array(energy))
    ax.add_collection3d(lc)

    # Add a colorbar to show the mapping of line segments to colors
    fig.colorbar(lc, ax=ax, label='electron energy')

    # Set labels and title
    ax.set_xlim(0, 100)
    ax.set_ylim(0, 100)
    ax.set_zlim(0, 200)

    ax.set_xlabel('x position')
    ax.set_ylabel('y position')
    ax.set_zlabel('z position')
    ax.set_title('Path of electrons in matter')

    # Show the plot
    plt.show()

except FileNotFoundError:
    print(
        f"plot.py can't find datafile {filename}\nPlease check naming or OUTPUT_PATH variable in src/globals.cpp")

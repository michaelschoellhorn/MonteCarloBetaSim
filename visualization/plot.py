import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

binpath = 'build/bin/'
filename = 'coordinates.txt'

try:
    # Read data from the file
    with open(binpath + filename, 'r') as file:
        lines = file.read().strip().split('\n\n')
    
    # Initialize 3D plot
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Plot lines from the data blocks
    for line_block in lines:
        # Split each line block into coordinates
        coordinates = line_block.split('\n')
        x, y, z = zip(*(map(float, coord.split()) for coord in coordinates))
        ax.plot(x, y, z)

    # Set labels and title
    ax.set_xlabel('x position')
    ax.set_ylabel('y position')
    ax.set_zlabel('z position')
    ax.set_title('Path of electrons in matter')

    # Show the plot
    plt.show()

except FileNotFoundError:
    print(f"plot.py can't find {filename} in directory {binpath}\nPlease check naming or path of the simulation outputfile")
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

data = np.loadtxt("visualization/energyGrid.txt")
data3D = data.T.reshape((10, 10, 10))
print(data3D[1][1][1])

x, y, z = np.zeros(1000), np.zeros(1000), np.zeros(1000)
yval = -1
zval = -1
for i in range(len(x)):
    x[i] = i%10
    if not (i%10):
        yval += 1
        if not (yval%10):
            zval += 1
    y[i] = yval%10
    z[i] = zval%10

data3D = data3D.flatten()
mask = (data3D>20).nonzero()
x = x[mask]
y = y[mask]
z = z[mask]
max = data3D.max()
markersize = (data3D[mask]-20)/max*250
# Create a 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z, s=markersize, c=data3D[mask], cmap=plt.cm.plasma)

# Set labels for each axis
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

# Show the plot
plt.show()
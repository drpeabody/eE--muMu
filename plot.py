import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# You may need to change this
output_dir = 'out/'

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Energy Axis
X = np.arange(5, 14000, 1)
# Cos Theta Axis
Y = np.arange(-1, 1, 0.01)

# # Actual Angles
Z = np.load('Z.bin.npy')
# Z = np.empty(len(X) * 5000)
# Z = np.reshape(Z, (len(X), 5000))
# # idx = x - 5
# for x in X:
#     # if x % 1000 is 0:
#     #     print(x)
#     Z[x-5] = np.loadtxt(output_dir + "pythia-E-" + str(x))
# np.save('Z.bin', Z)

X, Y = np.meshgrid(X, Y)
print(np.shape(X))
print(np.shape(Y))
print(np.shape(Z))

surf = ax.plot_surface(X, Y, Z)

# plt.show()

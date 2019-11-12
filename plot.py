import numpy as np
import matplotlib.pyplot as plt

## You may need to change this
output_dir = 'out/'

## Uncomment this to read the files and make a python binary

# startVal, endVal, delta = 7000, 14000, 50
# N = 10000
# len = int((endVal - startVal) / delta) + 1
# Z = np.zeros(len * N)
# Z = np.reshape(Z, (len, N))

# val = startVal
# while val <= endVal:
#     d = np.loadtxt(output_dir + 'pythia-E-' + str(val))
#     Z[int((val - startVal) / delta)] = d
#     val += delta
# np.save('Z.bin', Z)

## Actual Angles output to each file

startVal, delta = 7000, 50
Z = np.load('Z.bin.npy')

for i, z in enumerate(Z):
    plt.hist(z, bins=35)
    plt.xlabel('Cos of ${\\theta}_{13}$')
    plt.ylabel('Number of Events')
    plt.title('E = {} GeV'.format(i * delta + startVal))
    plt.savefig(output_dir + str(i) + '.png')
    plt.close()

import numpy as np
import matplotlib.pyplot as plt
import time

i=0

while True:
    ts = time.time()
    print(ts)
    y = np.random.random()
    plt.scatter(ts, y)
    plt.pause(0.5)

plt.show()
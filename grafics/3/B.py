import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from scipy import stats
N= np.array([500, 1000, 10000, 40000, 100000, 300000, 700000, 1000000] )
t1= np.array([2, 4, 49, 195, 502, 1495, 3509, 5050])

t2 = np.array([1, 3, 31, 126, 323, 986, 2253, 3224])


plt.scatter(N, t1, color='red', s=15, marker='o',
            label='равномерное распределение запросов', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N, t2, color='blue', s=15, marker='s',
            label='неравномерное распределение запросов', alpha=0.8, edgecolors='black', linewidth=1)

plt.xlabel('Длина массива, N', fontsize=10)
plt.ylabel('t(мс), время 100.000 запусокв ', fontsize=10)
plt.title('Зависимость t(N) для s_B', fontsize=12)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=10, loc='upper left')
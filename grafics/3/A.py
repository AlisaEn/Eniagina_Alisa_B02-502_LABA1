import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from scipy import stats
N_A= np.array([500, 1000, 10000, 40000, 100000, 300000, 700000, 1000000] )
tA_1= np.array([2, 5, 49, 198, 503, 1474, 3517, 5007])

tA_2 = np.array([1, 3, 31, 127, 319, 996, 2320, 3334])


plt.scatter(N_A, tA_1, color='red', s=15, marker='o',
            label='равномерное распределение запросов', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N_A, tA_2, color='blue', s=15, marker='s',
            label='неравномерное распределение запросов', alpha=0.8, edgecolors='black', linewidth=1)

plt.xlabel('Длина массива, N', fontsize=10)
plt.ylabel('t(мс), время 100.000 запусокв ', fontsize=10')
plt.title('Зависимость t(N) для s_A', fontsize=12)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=10, loc='upper left')
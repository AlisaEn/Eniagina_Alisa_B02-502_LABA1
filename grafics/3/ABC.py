import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from scipy import stats
N= np.array([500, 1000, 10000, 40000, 100000, 300000, 700000, 1000000] )
t_A= np.array([1, 3, 42, 142, 362, 1237, 2888, 4283])

t_B = np.array([1, 3, 39, 151, 372, 1148, 2745, 3987])

t_C = np.array([13, 9, 109, 495, 1146, 7779, 17817, 75497])
plt.scatter(N, t_A, color='lightgreen', s=15, marker='o',
            label='A', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N, t_B, color='blue', s=15, marker='s',
            label='B', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N, t_C, color='red', s=15, marker='o',
            label='C', alpha=0.8, edgecolors='black', linewidth=1)

plt.xlabel('Длина массива, N', fontsize=10)
plt.ylabel('t(мс), время 10.000 запусокв ', fontsize=10)
plt.title('Зависимость t(N) для s_A, s_B, s_C при неравномерном распределении', fontsize=12)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=10, loc='upper left')
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from scipy import stats


N1 = np.array([500, 1000, 6000,  10000, 40000, 100000, 350000, 500000, 700000, 1000000] )
T1 = np.array([113, 459, 11534, 19378, 24506, 25901, 26421, 29212, 27867, 24295])

N2 = np.array([500, 1000, 6000,  10000, 40000, 100000, 350000, 500000, 700000, 1000000])
T2 = np.array([10, 21, 130, 214, 856, 2339, 7428, 11327, 15644, 21307])/10

N3 = np.array([500, 1000, 6000,  10000, 40000, 100000])
T3 = np.array([24, 51, 226, 252, 270, 566])/10
plt.figure(figsize=(10, 7))

plt.scatter(N1, T1, color='red', s=15, marker='o',
            label='sum_sqr', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N2, T2, color='blue', s=15, marker='s',
            label='sum_linear (not random values in arrays)', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N3, T3, color='orange', s=15, marker='^',
            label='sum_linear (random values in arrays)', alpha=0.8, edgecolors='black', linewidth=1)

# Настройки графика
plt.xlabel('Длина массива, N', fontsize=10)
plt.ylabel('t (мс) на 1.000 запусков', fontsize=10)
plt.title('Сравнение асимптотики поиска суммы для среднего случая для неупорядоченного  и упорядоченного массива', fontsize=12)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=11, loc='upper left')
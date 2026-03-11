import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from scipy import stats


N1 = np.array([500, 1000, 6000,  10000, 40000, 100000, 350000, 500000, 700000, 1000000] )
T1 = np.array([30, 56, 330, 541, 2351, 6165, 21468, 29472, 41316, 56579])

N2 = np.array([500, 1000, 6000,  10000, 40000, 100000, 350000, 500000, 700000, 1000000])
T2 = np.array([25, 26, 35, 32, 37, 40, 46, 51, 53, 51])/10

N3 = np.array([500, 1000, 6000,  10000, 40000, 100000])
T3 = np.array([65, 70, 95, 91, 105, 121])/10
plt.figure(figsize=(10, 7))

plt.scatter(N1, T1, color='red', s=15, marker='o',
            label='linear search', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N2, T2, color='blue', s=15, marker='s',
            label='binar search (not random values in arrays)', alpha=0.8, edgecolors='black', linewidth=1)
plt.scatter(N3, T3, color='orange', s=15, marker='^',
            label='binar search (random values in arrays)', alpha=0.8, edgecolors='black', linewidth=1)

# Настройки графика
plt.xlabel('Длина массива, N', fontsize=10)
plt.ylabel('t (мс) на 100.000 запусков', fontsize=10)
plt.title('Сравнение асимптотики для среднего случая для линейного и бинарного поиска', fontsize=12)
plt.grid(True, alpha=0.3)
plt.legend(fontsize=11, loc='upper left')
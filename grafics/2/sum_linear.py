import numpy as np
import matplotlib.pyplot as plt

N1 = np.array([500, 1000, 6000,  10000, 40000, 100000, 350000, 500000, 700000, 1000000])
t1 = np.array([10, 21, 130, 214, 856, 2339, 7428, 11327, 15644, 21307])

N2 = np.array([500, 1000, 6000,  10000, 40000, 100000])
t2 = np.array([24, 51, 226, 252, 270, 566])

coeffs1 = np.polyfit(N1, t1, 1) 
coeffs2 = np.polyfit(N2, t2, 1) 
a1, b1 = coeffs1
a2, b2 = coeffs2


# Определение общего диапазона x для построения прямых
N_min = min(np.min(N1), np.min(N2))
N_max = max(np.max(N1), np.max(N2))
N_line = np.linspace(N_min, N_max, 100)


plt.scatter(N1, t1, color='blue', marker='o', label='sum_linear (not random values in arrays)')
plt.scatter(N2, t2, color='red', marker='s', label='sum_linear (random values in arrays)')

plt.plot(N_line, a1*N_line + b1, color='blue', linestyle='-', linewidth=2)
plt.plot(N_line, a2*N_line + b2, color='red', linestyle='-', linewidth=2)


plt.xlabel('N, длина массива')
plt.ylabel('t (мс) на 10.000 запусков')
plt.title('Средний случай sum_linear(для отсортированного массива)')
plt.legend()
plt.grid(True)
plt.show()
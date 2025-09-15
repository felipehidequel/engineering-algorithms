import matplotlib.pyplot as plt
import csv
import numpy as np

sizes = []
times = []

with open('benchmark.csv', 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        sizes.append(int(row['n']))
        times.append(float(row['binary_search_ms']))

sizes = np.array(sizes)
times = np.array(times)
times_us = times * 1000


# theoretical = np.log2(sizes) * (times[0] / np.log2(sizes[0]))
theoretical = np.log2(sizes) * (times_us[0] / np.log2(sizes[0]))


plt.figure(figsize=(10, 6))
plt.plot(np.log2(sizes), times_us, marker='o', label='Tempo medido (μs)')
plt.plot(np.log2(sizes), theoretical, linestyle='--', label='O(log n) teórico')
plt.xlabel('log2(Tamanho do vetor n)')
plt.ylabel('Tempo (μs)')
plt.title('Comparação: Busca Binária (medido vs teórico)')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
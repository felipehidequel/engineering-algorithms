import matplotlib.pyplot as plt
import csv

sizes = []
conventional_times = []
strassen_times = []

with open('benchmark.csv', 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        sizes.append(int(row['n']))
        conventional_times.append(float(row['conv_ms']))
        strassen_times.append(float(row['strassen_ms']))

plt.figure(figsize=(10, 6))
plt.plot(sizes, conventional_times, marker='o', label='Convencional')
plt.plot(sizes, strassen_times, marker='s', label='Strassen')

plt.xlabel('Tamanho da matriz (n × n)')
plt.ylabel('Tempo (ms)')
plt.title('Comparação de tempos: Multiplicação de matrizes')
plt.legend()
plt.grid(True)
plt.xticks(sizes)
# plt.yscale('log')
plt.tight_layout()
plt.show()

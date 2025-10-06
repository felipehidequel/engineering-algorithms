import pandas as pd
import matplotlib.pyplot as plt

# Carrega os resultados do benchmark
df = pd.read_csv("results.csv")

algorithms = ['quicksort_det', 'quicksort_rand']
cases = ['average', 'worst']

# Rótulos de complexidade para legenda
cases_labels = {
    'quicksort_det': {'average': 'O(n log n)', 'worst': 'O(n²)'},
    'quicksort_rand': {'average': 'O(n log n)', 'worst': 'O(n log n)'}
}

# Cores para os algoritmos
alg_colors = {
    'quicksort_det': 'green',
    'quicksort_rand': 'orange'
}

linestyles = {
    'quicksort_det': '--',
    'quicksort_rand': '-'
}

case_colors = {'average': 'orange', 'worst': 'red'}

fig, axs = plt.subplots(1, 2, figsize=(16, 6))
fig.suptitle("Comparação Quicksort Determinístico vs Randomizado", fontsize=18)

def format_name(name):
    return name.replace('_', ' ').title()

# ---------- Caso Médio ----------
ax1 = axs[0]
subset_avg = df[df['case'] == 'average']
for alg in algorithms:
    alg_subset = subset_avg[subset_avg['algorithm'] == alg]
    label = f"{format_name(alg)} ({cases_labels[alg]['average']})"
    ax1.plot(alg_subset['n'], alg_subset['time_ms'],
             marker='o', label=label, color=alg_colors[alg], linestyle=linestyles[alg])
ax1.set_title("Caso Médio (Average Case)", fontsize=14)
ax1.set_xlabel("Tamanho do Vetor (n) - Escala Log", fontsize=12)
ax1.set_ylabel("Tempo (ms) - Escala Log", fontsize=12)
ax1.grid(True, which="both", ls="--", alpha=0.5)
ax1.legend()
ax1.set_xscale('log')
ax1.set_yscale('log')

# ---------- Pior Caso ----------
ax2 = axs[1]
subset_worst = df[df['case'] == 'worst']
for alg in algorithms:
    alg_subset = subset_worst[subset_worst['algorithm'] == alg]
    label = f"{format_name(alg)} ({cases_labels[alg]['worst']})"
    ax2.plot(alg_subset['n'], alg_subset['time_ms'],
             marker='o', label=label, color=alg_colors[alg], linestyle=linestyles[alg])
ax2.set_title("Pior Caso (Worst Case)", fontsize=14)
ax2.set_xlabel("Tamanho do Vetor (n) - Escala Log", fontsize=12)
ax2.set_ylabel("Tempo (ms) - Escala Log", fontsize=12)
ax2.grid(True, which="both", ls="--", alpha=0.5)
ax2.legend()
ax2.set_xscale('log')
ax2.set_yscale('log')

plt.tight_layout(rect=[0, 0, 1, 0.95])
plt.savefig("comparacao_quicksort.png", dpi=300)
plt.show()

print("Gráficos gerados e salvos em 'comparacao_quicksort.png'.")

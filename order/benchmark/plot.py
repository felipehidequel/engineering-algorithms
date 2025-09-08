import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

algorithms = ['insertion_sort', 'merge_sort']
cases = ['best', 'average', 'worst']

cases_labels = {
    'insertion_sort': {'best': 'O(n)', 'average': 'O(n²)', 'worst': 'O(n²)'},
    'merge_sort': {'best': 'O(n log n)', 'average': 'O(n log n)', 'worst': 'O(n log n)'}
}

alg_colors = {'insertion_sort': 'blue', 'merge_sort': 'red'}
case_colors = {'best': 'green', 'average': 'orange', 'worst': 'red'}
linestyles = {'insertion_sort': '--', 'merge_sort': '-'}

fig, axs = plt.subplots(2, 2, figsize=(18, 13))
fig.suptitle("Análise Empírica da Complexidade de Algoritmos de Ordenação", fontsize=20)

def format_name(name):
    return name.replace('_', ' ').title()

ax1 = axs[0, 0]
subset_best = df[df['case'] == 'best']
for alg in algorithms:
    alg_subset = subset_best[subset_best['algorithm'] == alg]
    label = f"{format_name(alg)} ({cases_labels[alg]['best']})"
    ax1.plot(alg_subset['n'], alg_subset['time_ms'], marker='o', label=label, color=alg_colors[alg], linestyle=linestyles[alg])
ax1.set_title("Melhor Caso (Best Case)", fontsize=14)
ax1.set_xlabel("Tamanho do Vetor (n) - Escala Log", fontsize=12)
ax1.set_ylabel("Tempo (ms) - Escala Log", fontsize=12)
ax1.grid(True, which="both", ls="--", alpha=0.5)
ax1.legend()
ax1.set_yscale('log')
ax1.set_xscale('log')

ax2 = axs[0, 1]
subset_avg = df[df['case'] == 'average']
for alg in algorithms:
    alg_subset = subset_avg[subset_avg['algorithm'] == alg]
    label = f"{format_name(alg)} ({cases_labels[alg]['average']})"
    ax2.plot(alg_subset['n'], alg_subset['time_ms'], marker='o', label=label, color=alg_colors[alg], linestyle=linestyles[alg])
ax2.set_title("Caso Médio (Average Case)", fontsize=14)
ax2.set_xlabel("Tamanho do Vetor (n) - Escala Log", fontsize=12)
ax2.set_ylabel("Tempo (ms) - Escala Log", fontsize=12)
ax2.grid(True, which="both", ls="--", alpha=0.5)
ax2.legend()
ax2.set_yscale('log')
ax2.set_xscale('log')

ax3 = axs[1, 0]
subset_worst = df[df['case'] == 'worst']
for alg in algorithms:
    alg_subset = subset_worst[subset_worst['algorithm'] == alg]
    label = f"{format_name(alg)} ({cases_labels[alg]['worst']})"
    ax3.plot(alg_subset['n'], alg_subset['time_ms'], marker='o', label=label, color=alg_colors[alg], linestyle=linestyles[alg])
ax3.set_title("Pior Caso (Worst Case)", fontsize=14)
ax3.set_xlabel("Tamanho do Vetor (n) - Escala Log", fontsize=12)
ax3.set_ylabel("Tempo (ms) - Escala Log", fontsize=12)
ax3.grid(True, which="both", ls="--", alpha=0.5)
ax3.legend()
ax3.set_yscale('log')
ax3.set_xscale('log')

ax4 = axs[1, 1]
for alg in algorithms:
    for case in cases:
        subset = df[(df['algorithm'] == alg) & (df['case'] == case)]
        label = f"{format_name(alg)} ({case.title()})"
        ax4.plot(subset['n'], subset['time_ms'], marker='o', label=label, color=case_colors[case], linestyle=linestyles[alg])
ax4.set_title("Visão Geral Comparativa", fontsize=14)
ax4.set_xlabel("Tamanho do Vetor (n) - Escala Log", fontsize=12)
ax4.set_ylabel("Tempo (ms) - Escala Log", fontsize=12)
ax4.grid(True, which="both", ls="--", alpha=0.5)
ax4.legend(fontsize='medium')
ax4.set_yscale('log')
ax4.set_xscale('log')

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig("analise_complexidade_final.png", dpi=300)
plt.show()

print("Gráfico final salvo como 'analise_complexidade_final.png'.")
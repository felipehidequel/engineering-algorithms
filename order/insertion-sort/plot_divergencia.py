import pandas as pd
import matplotlib.pyplot as plt

# Carregar os dados do arquivo CSV gerado pelo C++
try:
    df = pd.read_csv("data.csv")
except FileNotFoundError:
    print("Erro: O arquivo 'data.csv' não foi encontrado.")
    print("Execute o programa C++ primeiro com './analysis > data.csv'")
    exit()


fig1, ax1 = plt.subplots(figsize=(12, 7))

color = 'tab:blue'
ax1.set_xlabel('Tamanho da Entrada (N)', fontsize=14)
ax1.set_ylabel('Operações (Modelo RAM)', color=color, fontsize=14)
ax1.plot(df['tamanho'], df['operacoes_ram'], color=color, marker='o', label='Modelo RAM (Operações)')
ax1.tick_params(axis='y', labelcolor=color)
ax1.grid(True, which='both', linestyle='--', linewidth=0.5)


ax2 = ax1.twinx()
color = 'tab:red'
ax2.set_ylabel('Tempo Real (nanossegundos)', color=color, fontsize=14)
ax2.plot(df['tamanho'], df['tempo_real_ns'], color=color, marker='x', linestyle='--', label='Máquina Real (Tempo)')
ax2.tick_params(axis='y', labelcolor=color)
# ax1.set_xscale('log')
# ax1.set_yscale('log')
# ax2.set_xscale('log')
# ax2.set_yscale('log')

plt.title('Modelo RAM vs. Tempo de Execução Real (Análise de Comportamento)', fontsize=16)
fig1.tight_layout()
fig1.legend(loc="upper left", bbox_to_anchor=(0.1, 0.9))
plt.savefig("ram_vs_real_comportamento.png")


df['proporcao'] = df['operacoes_ram'] / df['tempo_real_ns']


fig2, ax = plt.subplots(figsize=(12, 7))

ax.plot(df['tamanho'], df['proporcao'], marker='o', linestyle='-', color='purple')

ax.set_xlabel('Tamanho da Entrada (N)', fontsize=14)
ax.set_ylabel('Vazão Computacional (Operações por Nanossegundo)', fontsize=14)
ax.set_title('Análise da Divergência: Vazão Computacional vs. Tamanho da Entrada', fontsize=16)
ax.grid(True, which='both', linestyle='--', linewidth=0.5)
ax.set_xscale('log')
ax.set_yscale('log')

plt.savefig("analise_divergencia.png")
plt.show()
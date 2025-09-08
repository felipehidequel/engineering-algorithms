/**
 * @file main.cpp
 * @brief Análise comparativa do algoritmo Insertion Sort: Modelo RAM vs. Tempo
 * Real.
 * @details Este programa implementa o algoritmo de ordenação por inserção
 * (Insertion Sort) e o utiliza para conduzir um experimento que compara a
 * contagem teórica de operações, baseada no modelo de Máquina de Acesso
 * Aleatório (RAM) descrito por Cormen et al., com o tempo de execução real
 * medido em uma máquina física.
 *
 * O programa gera vetores em um cenário de pior caso (ordenados de forma
 * decrescente) com tamanhos crescentes. Para cada tamanho, ele calcula o número
 * total de operações teóricas e mede o tempo de execução em nanossegundos.
 *
 * A saída é formatada como CSV na saída padrão para ser facilmente importada
 * e visualizada por outras ferramentas, como o script Python fornecido.
 *
 * @author Felipe H. Santos-da-Silva
 * @version 1.0
 * @date 2025-09-06
 *
 * @note Para compilar e executar:
 * 1. make
 * 2. Execute o programa e redirecione a saída para um arquivo CSV:
 * ./main > data.csv
 * 3. Use o script em Python para gerar o gráfico:
 * python plot.py
 *
 * @copyright Copyright (c) 2025
 */

#include "insertion.hpp"



int main() {
  std::cout << "tamanho,operacoes_ram,tempo_real_ns" << std::endl;

  for (int n = 16; n <= 524288; n *= 2) {

    std::vector<KeyType> vec(n);
    std::iota(vec.begin(), vec.end(), 1);
    std::reverse(vec.begin(), vec.end());

    std::vector<KeyType> vec_for_ram_model = vec;
    std::vector<KeyType> vec_for_real_time = vec;

    AnnotationResult r = insertion_sort_instr(vec_for_ram_model);
    long long ram_operations = r.total;

    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(vec_for_real_time);
    auto end = std::chrono::high_resolution_clock::now();
    long long real_time_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();

    std::cout << n << "," << ram_operations << "," << real_time_ns << std::endl;
  }

  return 0;
}
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>

int particiona(std::vector<int> &A, int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j)
    {
        if (A[j] <= x)
        {
            ++i;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

int particiona_aleatorizado(std::vector<int> &A, int p, int r)
{
    int i = rand() % (r - p + 1) + p;
    std::swap(A[i], A[r]);
    return particiona(A, p, r);
}

int select(std::vector<int> &a, int p, int r, int i)
{
    if (p == r)
        return a[p];
    int q = particiona(a, p, r);
    int k = q - p + 1;
    if (i == k)
        return a[q];
    else if (i < k)
        return select(a, p, q - 1, i);
    else
        return select(a, q + 1, r, i - k);
}

int select_aleatorio(std::vector<int> &a, int p, int r, int i)
{
    if (p == r)
        return a[p];
    int q = particiona_aleatorizado(a, p, r);
    int k = q - p + 1;
    if (i == k)
        return a[q];
    else if (i < k)
        return select_aleatorio(a, p, q - 1, i);
    else
        return select_aleatorio(a, q + 1, r, i - k);
}

void caso_de_teste(std::vector<int> v, const std::string &descricao)
{
    const int i = v.size() / 2;
    std::vector<int> v1 = v;
    std::vector<int> v2 = v;

    std::cout << "\n===== Caso: " << descricao << " =====\n";

    auto start1 = std::chrono::high_resolution_clock::now();
    int res1 = select(v1, 0, v1.size() - 1, i);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    int res2 = select_aleatorio(v2, 0, v2.size() - 1, i);
    auto end2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> tempo1 = end1 - start1;
    std::chrono::duration<double> tempo2 = end2 - start2;

    double ganho = ((tempo1.count() - tempo2.count()) / tempo1.count()) * 100.0;

    std::cout << "Determinístico: " << tempo1.count() << " s\n";
    std::cout << "Aleatório:      " << tempo2.count() << " s\n";
    std::cout << "Resultado (mediana): " << res1 << " / " << res2 << "\n";
    std::cout << "Ganho percentual do aleatório: " << ganho << "%\n";
}

int main()
{
    srand(time(nullptr));
    const int n = 100000;

    std::vector<int> crescente(n);
    std::iota(crescente.begin(), crescente.end(), 1);
    caso_de_teste(crescente, "Ordenado crescente");

    std::vector<int> decrescente = crescente;
    std::reverse(decrescente.begin(), decrescente.end());
    caso_de_teste(decrescente, "Ordenado decrescente");

    std::vector<int> aleatorio = crescente;
    std::shuffle(aleatorio.begin(), aleatorio.end(), std::mt19937(std::random_device{}()));
    caso_de_teste(aleatorio, "Aleatório");

    return 0;
}

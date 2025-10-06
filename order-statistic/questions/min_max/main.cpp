#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <cstdint>

uint64_t comparisons_non_simul = 0;
uint64_t comparisons_simul = 0;

int min_value(const std::vector<int> &a)
{
    int res = a[0];
    for (size_t i = 1; i < a.size(); i++)
    {
        comparisons_non_simul++;
        if (a[i] < res)
            res = a[i];
    }
    return res;
}

int max_value(const std::vector<int> &a)
{
    int res = a[0];
    for (size_t i = 1; i < a.size(); i++)
    {
        comparisons_non_simul++;
        if (a[i] > res)
            res = a[i];
    }
    return res;
}

void min_max(const std::vector<int> &a, int &min, int &max)
{
    int n = a.size();
    min = max = a[0];
    int start = 1;

    if (n % 2 == 0)
    {
        comparisons_simul++;
        if (a[0] < a[1])
        {
            min = a[0];
            max = a[1];
        }
        else
        {
            min = a[1];
            max = a[0];
        }
        start = 2;
    }

    for (int i = start; i + 1 < n; i += 2)
    {
        comparisons_simul++;
        int local_min, local_max;

        if (a[i] < a[i + 1])
        {
            local_min = a[i];
            local_max = a[i + 1];
        }
        else
        {
            local_min = a[i + 1];
            local_max = a[i];
        }

        comparisons_simul += 2;
        if (local_min < min)
            min = local_min;
        if (local_max > max)
            max = local_max;
    }

    if (n % 2 == 1)
    {
        comparisons_simul += 2;
        if (a[n - 1] < min)
            min = a[n - 1];
        if (a[n - 1] > max)
            max = a[n - 1];
    }
}

int main()
{
    int n = 500'000'000;
    std::vector<int> a(n);

    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, 1e9);
    for (int i = 0; i < n; i++)
        a[i] = dist(gen);

    int val_min, val_max;

    auto start_1 = std::chrono::steady_clock::now();
    int m1 = min_value(a);
    int M1 = max_value(a);
    auto stop_1 = std::chrono::steady_clock::now();

    auto start_2 = std::chrono::steady_clock::now();
    min_max(a, val_min, val_max);
    auto stop_2 = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_non_simul = stop_1 - start_1;
    std::chrono::duration<double> elapsed_simul = stop_2 - start_2;

    std::cout << "Não-simultâneo: " << elapsed_non_simul.count() << " s\n";
    std::cout << "Simultâneo:     " << elapsed_simul.count() << " s\n\n";

    std::cout << "Comparações (não-simultâneo): " << comparisons_non_simul << "\n";
    std::cout << "Comparações (simultâneo):     " << comparisons_simul << "\n";

    std::cout << "\nResultado não-simultâneo -> min=" << m1 << ", max=" << M1 << "\n";
    std::cout << "Resultado simultâneo     -> min=" << val_min << ", max=" << val_max << "\n";
}

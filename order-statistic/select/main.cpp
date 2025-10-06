#include <iostream>
#include <vector>
#include <numeric>

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

int main()
{
    int n = 10;
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);

    for (auto x : v)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";

    int res = select_aleatorio(v, 0, v.size() - 1, n);
    std::cout << res << '\n';
    return 0;
}
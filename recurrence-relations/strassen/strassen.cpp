#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matriz;

matriz multiply_conventional(const matriz &a, const matriz &b) {
  size_t n = a.size();
  matriz c(n, vector<int>(n, 0));

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      for (size_t k = 0; k < n; k++)
        c[i][j] += a[i][k] * b[k][j];

  return c;
}

matriz add(const matriz &a, const matriz &b) {
  size_t n = a.size();
  matriz c(n, vector<int>(n, 0));

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      c[i][j] = a[i][j] + b[i][j];

  return c;
}

matriz sub(const matriz &a, const matriz &b) {
  size_t n = a.size();
  matriz c(n, vector<int>(n, 0));

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      c[i][j] = a[i][j] - b[i][j];

  return c;
}

matriz strassen(const matriz &a, const matriz &b) {
  size_t n = a.size();
  if (n == 1)
    return {{a[0][0] * b[0][0]}};

  if (n <= 128)
    return multiply_conventional(a, b);

  size_t k = n / 2;

  matriz a11(k, vector<int>(k)), a12(k, vector<int>(k)), a21(k, vector<int>(k)),
      a22(k, vector<int>(k));
  matriz b11(k, vector<int>(k)), b12(k, vector<int>(k)), b21(k, vector<int>(k)),
      b22(k, vector<int>(k));

  auto get_submatrix = [](const matriz &m, size_t row, size_t col,
                          size_t size) {
    matriz sub(size, vector<int>(size));
    for (size_t i = 0; i < size; i++)
      for (size_t j = 0; j < size; j++)
        sub[i][j] = m[row + i][col + j];
    return sub;
  };

  a11 = get_submatrix(a, 0, 0, k);
  a12 = get_submatrix(a, 0, k, k);
  a21 = get_submatrix(a, k, 0, k);
  a22 = get_submatrix(a, k, k, k);

  b11 = get_submatrix(b, 0, 0, k);
  b12 = get_submatrix(b, 0, k, k);
  b21 = get_submatrix(b, k, 0, k);
  b22 = get_submatrix(b, k, k, k);

  matriz m1 = strassen(add(a11, a22), add(b11, b22));
  matriz m2 = strassen(add(a21, a22), b11);
  matriz m3 = strassen(a11, sub(b12, b22));
  matriz m4 = strassen(a22, sub(b21, b11));
  matriz m5 = strassen(add(a11, a12), b22);
  matriz m6 = strassen(sub(a21, a11), add(b11, b12));
  matriz m7 = strassen(sub(a12, a22), add(b21, b22));

  matriz c(n, vector<int>(n, 0));
  matriz c11 = add(sub(add(m1, m4), m5), m7);
  matriz c12 = add(m3, m5);
  matriz c21 = add(m2, m4);
  matriz c22 = add(sub(add(m1, m3), m2), m6);

  for (size_t i = 0; i < k; i++)
    for (size_t j = 0; j < k; j++) {
      c[i][j] = c11[i][j];
      c[i][j + k] = c12[i][j];
      c[i + k][j] = c21[i][j];
      c[i + k][j + k] = c22[i][j];
    }

  return c;
}

template <typename Func>
pair<matriz, double> benchmark(Func f, const matriz &a, const matriz &b) {
  auto start = chrono::high_resolution_clock::now();
  matriz result = f(a, b);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> elapsed = end - start;
  return {result, elapsed.count()};
}

int main() {
  ofstream csv("benchmark.csv");
  csv << "n,conv_ms,strassen_ms\n";

  size_t n_max = 2048;
  int repetitions = 5;

  for (size_t n = 16; n <= n_max; n *= 2) {
    double avg_time_conventional = 0.0;
    double avg_time_strassen = 0.0;

    for (int r = 0; r < repetitions; r++) {
      matriz a(n, vector<int>(n));
      matriz b(n, vector<int>(n));

      for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
          a[i][j] = b[i][j] = i * j;

      auto [c_conv, t_conv] = benchmark(multiply_conventional, a, b);
      auto [c_strassen, t_strassen] = benchmark(strassen, a, b);

      avg_time_conventional += t_conv;
      avg_time_strassen += t_strassen;
    }

    avg_time_conventional /= repetitions;
    avg_time_strassen /= repetitions;

    csv << n << "," << avg_time_conventional << "," << avg_time_strassen
        << "\n";
    cout << "n = " << n << " | conv = " << avg_time_conventional
         << " ms | strassen = " << avg_time_strassen << " ms\n";
  }

  csv.close();
  cout << "Benchmark salvo em benchmark.csv\n";

  return 0;
}

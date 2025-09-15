#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;
typedef int Keytype;

Keytype binary_search_recursive(const std::vector<Keytype> &v, Keytype key,
                                int begin, int end) {
  if (begin > end) {
    return -1;
  }

  int middle = (begin + end) / 2;

  if (key < v[middle]) {
    return binary_search_recursive(v, key, begin, middle - 1);
  } else if (key > v[middle]) {
    return binary_search_recursive(v, key, middle + 1, end);
  } else {
    return middle;
  }
}



int main() {
  int repetitions = 10000;
  unsigned int max_n = 536870912;

  ofstream csv("benchmark.csv");
  csv << "n,binary_search_ms\n";

  random_device rd;
  mt19937 gen(rd());

  for (unsigned int n = 16; n <= max_n && n > 0; n *= 2) {
    vector<Keytype> v(n);
    iota(v.begin(), v.end(), 1);

    uniform_int_distribution<Keytype> distrib(1, n);

    auto start = chrono::high_resolution_clock::now();

    volatile Keytype result_sink = 0;

    for (int i = 0; i < repetitions; ++i) {
      Keytype key_to_find = distrib(gen);
      Keytype result = binary_search_recursive(v, key_to_find, 0, v.size() - 1);
      result_sink = result;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;

    double avg_time_ms = elapsed.count() / repetitions;

    csv << n << "," << avg_time_ms << endl;
    cout << "Size: " << n << ", Avg time: " << avg_time_ms << " ms" << endl;

    if (n == max_n)
      cout << "Último resultado encontrado (para evitar otimização): "
           << result_sink << endl;
  }

  csv.close();
  return 0;
}
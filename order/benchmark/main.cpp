#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "../insertion-sort/insertion.hpp"
#include "../merge-sort/merge.hpp"

std::vector<KeyType> generate_vector(int n, const std::string &type) {
  std::vector<KeyType> v(n);

  std::iota(v.begin(), v.end(), 1);

  if (type == "best") {
    return v;
  } else if (type == "worst") {
    std::reverse(v.begin(), v.end());
    return v;
  } else {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    return v;
  }
}

template <typename Func> double benchmark(Func f, std::vector<KeyType> arr) {
  auto start = std::chrono::high_resolution_clock::now();
  f(arr);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  return elapsed.count();
}

void run_benchmarks_for_n(int n, int num_repeats, std::ofstream &file) {
  std::vector<std::string> cases = {"best", "worst", "average"};
  std::cout << "Benchmarking for n = " << n << "...\n";

  for (const auto &c : cases) {
    double avg_time_insertion = 0.0;
    double avg_time_merge = 0.0;

    for (int run = 0; run < num_repeats; run++) {
      auto v1 = generate_vector(n, c);
      auto v2 = v1;

      avg_time_insertion +=
          benchmark([&](auto arr) { insertion_sort(arr); }, v1);
      avg_time_merge +=
          benchmark([&](auto arr) { merge_sort(arr, 0, arr.size() - 1); }, v2);
    }

    avg_time_insertion /= num_repeats;
    avg_time_merge /= num_repeats;

    file << "insertion_sort," << c << "," << n << "," << avg_time_insertion
         << "\n";
    file << "merge_sort," << c << "," << n << "," << avg_time_merge << "\n";
  }
}

int main() {
  long long max_size = 524288; // 2^19
  int num_repeats = 5;
  std::ofstream file("results.csv");
  file << "algorithm,case,n,time_ms\n";

  std::vector<std::string> cases = {"best", "worst", "average"};

  for (int n = 16; n <= max_size; n *= 2) {
    run_benchmarks_for_n(n, num_repeats, file);
  }
  

  file.close();
  std::cout << "Resultados salvos em results.csv\n";
  return 0;
}

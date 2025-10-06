#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <numeric>
#include <fstream>

using namespace std;
using namespace std::chrono;

int partitionDet(vector<int>& A, int p, int r) {
    int x = A[r]; // pivô: último elemento
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void quicksortDet(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = partitionDet(A, p, r);
        quicksortDet(A, p, q - 1);
        quicksortDet(A, q + 1, r);
    }
}

int partitionRand(vector<int>& A, int p, int r) {
    int i = p + rand() % (r - p + 1);
    swap(A[i], A[r]);
    return partitionDet(A, p, r);
}

void quicksortRand(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = partitionRand(A, p, r);
        quicksortRand(A, p, q - 1);
        quicksortRand(A, q + 1, r);
    }
}

std::vector<int> generate_vector(int n, const std::string &type, bool quicksort = false) {
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 1);

    if (type == "average") {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(v.begin(), v.end(), g);
    } else if (type == "worst" && quicksort) {
        std::reverse(v.begin(), v.end()); 
    } 

    return v;
}

double benchmarkDet(std::vector<int> arr) {
  auto start = std::chrono::high_resolution_clock::now();
  quicksortDet(arr, 0, arr.size() - 1);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  return elapsed.count();
}

double benchmarkRand(std::vector<int> arr) {
  auto start = std::chrono::high_resolution_clock::now();
  quicksortRand(arr, 0, arr.size() - 1);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  return elapsed.count();
}


void run_benchmarks_for_n(int n, int num_repeats, std::ofstream &file) {
    std::vector<std::string> cases = {"average", "worst"};
    std::cout << "Benchmarking for n = " << n << "...\n";

    for (const auto &c : cases) {
        double avg_time_det = 0.0;
        double avg_time_rand = 0.0;

        for (int run = 0; run < num_repeats; run++) {
            auto original = generate_vector(n, c, true);

            auto v_det = original;
            auto v_rand = original;

            avg_time_det += benchmarkDet(v_det);
            avg_time_rand += benchmarkRand(v_rand);
        }

        avg_time_det /= num_repeats;
        avg_time_rand /= num_repeats;

        file << "quicksort_det," << c << "," << n << "," << avg_time_det << "\n";
        file << "quicksort_rand," << c << "," << n << "," << avg_time_rand << "\n";
    }
}


int main() {
    srand(time(nullptr));
    long long max_size = 65536; // 2^19
    // max_size /= 2; // 2^19
    int num_repeats = 5;
    std::ofstream file("results.csv");
    file << "algorithm,case,n,time_ms\n";

    for (int n = 16; n <= max_size; n *= 2) {
        run_benchmarks_for_n(n, num_repeats, file);
    }

    file.close();
    std::cout << "Resultados salvos em results.csv\n";
    return 0;
}

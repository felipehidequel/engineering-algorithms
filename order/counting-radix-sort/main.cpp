#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void counting_sort(std::vector<int>& arr) {
    if(arr.empty()) return;
    int max_val = *std::max_element(arr.begin(), arr.end());
    std::vector<int> count(max_val + 1, 0);

    for(int x : arr) count[x]++;
    int idx = 0;
    for(int i = 0; i <= max_val; i++)
        while(count[i]--) arr[idx++] = i;
}

void counting_sort_digit(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    int count[10] = {0};

    for(int i = 0; i < n; i++)
        count[(arr[i]/exp) % 10]++;

    for(int i = 1; i < 10; i++)
        count[i] += count[i-1];

    for(int i = n-1; i >=0; i--) {
        int digit = (arr[i]/exp) % 10;
        output[count[digit]-1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

void radix_sort(std::vector<int>& arr) {
    if(arr.empty()) return;
    int max_val = *std::max_element(arr.begin(), arr.end());
    for(int exp = 1; max_val/exp > 0; exp *= 10)
        counting_sort_digit(arr, exp);
}

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist_small(0, 1000);
    std::uniform_int_distribution<int> dist_large(0, 100000000);
    std::vector<int> sizes = {1000, 10000, 100000, 500000};

    for(auto n : sizes) {
        std::vector<int> v1(n), v2(n);
        for(int i = 0; i < n; i++) {
            v1[i] = dist_small(rng);
        }
        v2 = v1;

        auto start = std::chrono::high_resolution_clock::now();
        counting_sort(v1);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Count Sort (small values, n=" << n << "): "
                  << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";

        start = std::chrono::high_resolution_clock::now();
        radix_sort(v2);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Radix Sort (small values, n=" << n << "): "
                  << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n\n";

        for(int i = 0; i < n; i++) {
            v1[i] = dist_large(rng);
        }
        v2 = v1;

        start = std::chrono::high_resolution_clock::now();
        counting_sort(v1);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Count Sort (large values, n=" << n << "): "
                  << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n";

        start = std::chrono::high_resolution_clock::now();
        radix_sort(v2);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Radix Sort (large values, n=" << n << "): "
                  << std::chrono::duration<double, std::milli>(end-start).count() << " ms\n\n";
    }
}
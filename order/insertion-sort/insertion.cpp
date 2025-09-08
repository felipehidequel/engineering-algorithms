#include "insertion.hpp"

std::vector<KeyType> insertion_sort(std::vector<KeyType> &a) {
  for (size_t i = 1; i < a.size(); i++) {
    KeyType key = a[i];
    int j = i - 1;

    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      j = j - 1;
    }

    a[j + 1] = key;
  }
  return a;
}

AnnotationResult insertion_sort_instr(std::vector<KeyType> &a) {
  AnnotationResult result{0, 0, 0, 0, 0, 0, {}};

  result.assignments++;
  for (size_t i = 1; i < a.size(); i++) {
    result.comparisons++;
    result.iterations++;

    KeyType key = a[i];
    result.assignments++;
    result.accesses++;

    int j = i - 1;
    result.assignments++;
    result.arithmetic_operations++;

    while (j >= 0 && a[j] > key) {
      result.comparisons += 2;
      result.accesses++;

      a[j + 1] = a[j];
      result.accesses += 2;
      result.assignments++;

      j = j - 1;
      result.arithmetic_operations++;
      result.assignments++;
    }

    a[j + 1] = key;
    result.accesses++;
    result.assignments++;
    result.arithmetic_operations++;

    result.comparisons++;
  }

  result.total = result.accesses + result.arithmetic_operations +
                 result.assignments + result.comparisons + result.iterations;
  result.array = a;

  return result;
}

void print_result(AnnotationResult r) {
  std::cout << "+++ Insertion Sort Analysis +++" << std::endl;
  std::cout << "Array size: " << r.array.size() << std::endl;
  std::cout << "Accesses: " << r.accesses << std::endl;
  std::cout << "Arithmetic operations: " << r.arithmetic_operations
            << std::endl;
  std::cout << "Assignments: " << r.assignments << std::endl;
  std::cout << "Comparisons: " << r.comparisons << std::endl;
  std::cout << "Iterations (outer loop): " << r.iterations << std::endl;
  std::cout << "Total operations: " << r.total << std::endl;

  std::cout << "Sorted array: ";
  for (size_t i = 0; i < r.array.size(); i++) {
    std::cout << r.array[i] << " ";
  }
  std::cout << std::endl;
}
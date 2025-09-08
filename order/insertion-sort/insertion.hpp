#ifndef INSERTION_HPP
#define INSERTION_HPP

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

typedef long long KeyType;

struct AnnotationResult {
  unsigned long long comparisons;
  unsigned long long iterations;
  unsigned long long accesses;
  unsigned long long arithmetic_operations;
  unsigned long long assignments;
  unsigned long long total;
  std::vector<KeyType> array;
};

std::vector<KeyType> insertion_sort(std::vector<KeyType> &a);
AnnotationResult insertion_sort_instr(std::vector<KeyType> &a);
void print_result(AnnotationResult r);

#endif
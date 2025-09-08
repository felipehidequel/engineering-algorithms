#include "merge.hpp"

int main() {
  std::vector<KeyType> a = {5, 4, 3, 56, 2, 1};

  merge_sort(a, 0, a.size() - 1);

  for (auto i : a) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}
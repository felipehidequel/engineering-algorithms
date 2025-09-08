#include "merge.hpp"

void merge(std::vector<KeyType> &A, long long begin, long long middle,
           long long end) {
  std::vector<KeyType> left(middle - begin + 1);
  std::vector<KeyType> right(end - middle);

  memcpy(left.data(), &A[begin], left.size() * sizeof(KeyType));
  memcpy(right.data(), &A[middle + 1], right.size() * sizeof(KeyType));

  size_t idxLeft = 0, idxRigth = 0, k;

  for (k = begin; k <= end; k++) {
    if (idxLeft < left.size()) {
      if (idxRigth < right.size()) {

        if (left[idxLeft] < right[idxRigth]) {
          A[k] = left[idxLeft];
          idxLeft++;
        } else {
          A[k] = right[idxRigth];
          idxRigth++;
        }
      } else {
        A[k] = left[idxLeft];
        idxLeft++;
      }
    } else {
      A[k] = right[idxRigth];
      idxRigth++;
    }
  }
}

void merge_sort(std::vector<KeyType> &A, long long begin, long long end) {
  if (begin < end) {
    long long middle = (begin + end) / 2;
    merge_sort(A, begin, middle);
    merge_sort(A, middle + 1, end);
    merge(A, begin, middle, end);
  }
}

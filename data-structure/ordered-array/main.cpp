#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int lower_bound_manual(const std::vector<int> &a, int value) {
    int left = 0;
    int right = a.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (a[mid] < value)
            left = mid + 1;
        else
            right = mid; 
    }
    return left;
}

void inserir_ordenado(std::vector<int> &a, int value){
  int pos = lower_bound_manual(a, value);
  a.insert(a.begin() + pos, value);
}

int binary_search_recursive(const std::vector<int> &v, int key,
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

int main(){
  int n=10;
  std::vector<int> a;
  srand(4);

  int value;
  for (size_t i = 0; i < n; i++)
  {
    value = rand()%n;
    inserir_ordenado(a, value);
  }
  

  
  for (auto i : a)
  {
    std::cout << i << " ";
  }
    std::cout << "\n";
  
  

  return 0;
}
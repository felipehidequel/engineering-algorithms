#include <iostream>

int main() {
  int a[] = {5, 2, 4, 6, 1 , 3};  
  int n = 6;
  int key;
  int i,j;

  for (i = 1; i < n; i++)
  {  
    key = a[i];
    j = i -1;

    while (j>=0 && a[j]>key)
    {
      a[j+1] = a[j];
      j = j-1;
    }

    a[j+1] = key;
  }
  
  for (int i = 0; i < n; i++)
  {
    std::cout << a[i] << std::endl;
  }
  


  return 0;
}
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;

int main() {
  int n = 64;
  int workers = 4;
  int chunksize = n / workers;

  vector<int> tasks(n);
  vector<int> workload(workers, 0);
  iota(tasks.begin(), tasks.end(), 1);


#ifdef RANDOM
  random_device rd;
  mt19937 g(rd());
  shuffle(tasks.begin(), tasks.end(), g);
#endif

  for (size_t worker = 0; worker < workers; worker++) {

    int end = (worker + 1) * chunksize;

    for (size_t i = worker * chunksize; i < end; i++) {
      workload[worker] += tasks[i];
    }
  }

  cout << setw(6) << "Worker"
       << " | " << setw(8) << "Workload" << endl;
  cout << "---------------------" << endl;

  for (size_t worker = 0; worker < workers; worker++) {
    cout << setw(6) << worker << " | " << setw(8) << workload[worker] << endl;
  }

  return 0;
}
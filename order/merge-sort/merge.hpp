#ifndef MERGE_HPP
#define MERGE_HPP

#include <cstring>
#include <iostream>
#include <vector>

typedef long long KeyType;

void merge_sort(std::vector<KeyType> &A, long long begin, long long end);
void merge(std::vector<KeyType> &A, long long begin, long long middle, long long end);

#endif
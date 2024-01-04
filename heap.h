#ifndef heap
#define heap

#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int> &numbers, int N, int i);
void build_max_heap(vector<int> &numbers);
void sort_with_heap_sort(vector<int> &numbers);

#endif

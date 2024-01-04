#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int> &numbers, int N, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if(l < N && numbers[largest] < numbers[l]) {
        largest = l;
    }
    if(r < N && numbers[largest] < numbers[r]) {
        largest = r;
    }
    if(largest != i) {
        swap(numbers[i], numbers[largest]);
        heapify(numbers,N,largest);
    }
}

void build_max_heap(vector<int> &numbers) {
    int N = numbers.size();
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(numbers,N, i);
}

void sort_with_heap_sort(vector<int> &numbers) {
    build_max_heap(numbers);
    int N = numbers.size();
    for(int i = N - 1; i > 0; i--) {
        swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
}

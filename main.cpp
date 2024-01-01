#include <iostream>
#include <vector>
using namespace::std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void sort_with_insertion_sort(vector<int> &numbers) {
    int size = numbers.size();
    for(int i = 1; i < size; i++) {
        int num = numbers[i];
        int j = i - 1;
        while(j > -1 && num < numbers[j]) {
            numbers[j+1] = numbers [j];
            j--;
        }
        numbers[j+1] = num;
    }
}

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

void show(vector<int> numbers) {
    for(auto i = numbers.begin(); i != numbers.end(); ++i) {
        cout << *i << endl;
    }
}

void sort_with_heap_sort(vector<int> &numbers) {
    build_max_heap(numbers);
    show(numbers);
    cout << "\n\n\n\n";
    int N = numbers.size();
    for(int i = N - 1; i > 0; i--) {
        swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
}

int main() {
    vector<int> a = {1, 5, 88, 34, -1, 3, 2, 1990};
    /* sort_with_insertion_sort(a); */
    sort_with_heap_sort(a);
    show(a);
}

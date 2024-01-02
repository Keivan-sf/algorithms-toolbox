#include <exception>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>
using namespace::std;

struct graph_node {
    bool marked = false;
    vector<graph_node*> neighbors;
};

class GraphQueue {
public:
    struct queue_node {
        graph_node* g_node;
        queue_node *next;
    };
    queue_node* front = NULL;
    queue_node* rear = NULL;
    void add(graph_node* g_node) {
        queue_node *new_node = new(queue_node);
        new_node->g_node = g_node;
        if(rear != NULL) {
            rear->next = new_node;
        }
        rear = new_node;
        if(front == NULL) {
            front = new_node;
        }
    }
    graph_node* shift() {
        if(front == NULL) {
            throw std::logic_error("No element in the queue");
        }
        queue_node *new_front = front->next;
        graph_node* g_node = front->g_node;
        delete(front);
        front = new_front;
        return g_node;
    }
};

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void perform_bfs() {
    set<int> marked;

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
    int N = numbers.size();
    for(int i = N - 1; i > 0; i--) {
        swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
}

int find_with_binary_search(int target, vector<int> &numbers) {
    int N = numbers.size();
    int end = numbers.size() - 1;
    int start = 0;
    int mid = (start + end) / 2;
    int i = -1;

    while (start <= end) {
        if(target > numbers[mid]) {
            start = mid+1;
        } else if(target < numbers[mid]) {
            end = mid - 1;
        } else {
            i = mid;
            break;
        }
        mid = (end + start) / 2;
    }
    return i;

}

int main() {
    /* vector<int> a = {1, 5, 88, 34, -1, 3, 2, 1990}; */
    /* sort_with_insertion_sort(a); */
    /* show(a); */
    /* sort_with_heap_sort(a); */
    /* cout << find_with_binary_search(88, a) << endl; */
    /* show(a); */
}

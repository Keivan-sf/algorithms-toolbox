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

void sort_with_merge_sort(vector<int> numbers) {

}

void show(vector<int> numbers) {
    for(auto i = numbers.begin(); i != numbers.end(); ++i) {
        cout << *i << endl;
    }
}

int main() {
    vector<int> a = {1, 5, 88, 34, -1, 3, 2, 1990};
    sort_with_insertion_sort(a);
    show(a);
}

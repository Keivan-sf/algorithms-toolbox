#include<iostream>
#include<vector>
using namespace std;

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

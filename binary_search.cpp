#include <iostream>
#include <vector>
using namespace std;

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

#include <iostream>
#include <vector>
#include <map>

using namespace std;
struct Menu {
    string title;
    vector<string> items;
};

map<string, Menu> menus {
    {"main", Menu{.title= "--+ Welcome to the algorithms toolbox! +--", .items = {"Binary search", "BFS", "Heapify", "Sort", "Infix to prefix or postfix", "Exit"}}},
    {"sort", Menu{.title= "Sorting", .items = {"Insertion sort", "Heap sort", "Back to main menu"}}}
};

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void show(vector<int> numbers) {
    for(auto i = numbers.begin(); i != numbers.end(); ++i) {
        cout << *i << endl;
    }
}

bool is_valid_int(string input, int n) {
    int i = 0;
    if(n < 1 || !input[i]) return false;
    if(input[i] == '-') i++;
    for(; input[i] && i < n; i++) {
        if(int(input[i]) < 48 || int(input[i]) > 57) {
            return false;
        }
    }
    return true;
}

int prompt_menu(Menu menu) {
    string error = "";
    vector<string> &items = menu.items;
    int max = items.size() - 1;
    while(true) {
        clearScreen();
        cout << menu.title << "\n\n";
        for(int i = 0; i < items.size() - 1; i++) {
            cout << i + 1 << ". " << items[i] << "\n";
        }
        cout << "0. " << items[items.size() - 1] << "\n";
        if(error.size() > 0) {
            cout << "\n\033[31m" << error << "\033[0m" << "\n";
        }
        error = "";
        cout << "\nPlease choose an item: ";
        string c;
        cin >> c;
        if(!is_valid_int(c, c.size())) {
            error = "Please enter a valid inteager!";
            continue;
        }
        int input_num = stoi(c);
        if(input_num < 0 || input_num > max) {
            error = "Item " + string(c) + " doesn't exist";
            continue;
        }
        return input_num;
    }
}

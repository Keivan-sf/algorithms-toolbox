#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>
#include <map>
#include <sstream>
#include "./cli.h"

using namespace std;

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

int prompt_menu(Menu menu, string error) {
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

string trim(string &s) {
    string result="";
    int start = 0;
    int end = s.size();
    while(start < end && isspace(s[start])) {
        start++;
    }
    while(end > start && isspace(s[end-1])) {
        end--;
    }
    for(; start < end; start++) {
        result += s[start];
    }
    return result;
}

vector_prompt_result prompt_vector() {
    string error = "";
    while(true) {
        vector<int> result;
        clearScreen();
        cout << "\nPlease enter your numbers separated via comma (\033[33m,\033[0m) or type \033[33mb\033[0m to get back to menu\n\n";
        cout << "E.g: \033[33m1, 2, 3, 4, 5, 6, 12, 45, -12, 102\033[0m\n";
        if(error.size() > 0) cout << "\n\033[31m" << error << "\033[0m" << "\n";
        error = "";
        cout << "\n-> ";
        string s;
        char char_input[1000];
        getchar();
        fgets(char_input, 1000, stdin);
        s = char_input;
        s = trim(s);
        if(s == "b" || s == "B") return vector_prompt_result{.back= true};
        for(int i = 0; i < s.size(); i++) {
            string num = "";
            while(s[i] != ',' && i < s.size()) {
                num += s[i];
                i++;
            }
            num = trim(num);
            if(num.size() < 1) continue;
            if(!is_valid_int(num, num.size())) {
                error = num + " is not a valid inteager!";
                break;
            }
            result.push_back(stoi(num));
        }
        if(error.size() > 0) continue;
        string a = "";
        return vector_prompt_result{.vec = result};
    }
}

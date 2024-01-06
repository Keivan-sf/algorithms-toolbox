#ifndef cli
#define cli

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Menu {
    string title;
    vector<string> items;
};

extern map<string, Menu> menus;

void clearScreen();

void show(vector<int> numbers);

bool is_valid_int(string input, int n);

int prompt_menu(Menu menu, string error = "");

struct vector_prompt_result {
    bool back = false;
    vector<int> vec;
};

vector_prompt_result prompt_vector();

#endif

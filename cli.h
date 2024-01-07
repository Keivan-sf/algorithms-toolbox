#ifndef cli
#define cli

#include "bfs.h"
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
string join(vector<int> numbers, string separator);

bool is_valid_int(string input, int n);

int prompt_menu(Menu menu, string ouput = "");

struct vector_prompt_result {
    bool back = false;
    vector<int> vec;
};

struct int_prompt_result {
    bool back = false;
    int number;
};

struct infix_prompt_result {
    bool back = false;
    string s;
};

vector_prompt_result prompt_vector(string message = "Please enter your numbers separated via comma (\033[33m,\033[0m)\n\nE.g: \033[33m1, 2, 3, 4, 5, 6, 12, 45, -12, 102\033[0m\n");
int_prompt_result prompt_int(string message = "Please enter your number");
graph_node* prompt_graph(string message = "");
infix_prompt_result prompt_infix_string(string message = "Please enter a valid infix string");

#endif

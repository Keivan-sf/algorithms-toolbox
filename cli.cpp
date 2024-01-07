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
#include "./infix_parser.h"
#include "bfs.h"

using namespace std;

map<string, Menu> menus {
    {"main", Menu{.title= "--+ Welcome to the algorithms toolbox! +--", .items = {"Binary search", "BFS", "Heapify", "Sort", "Infix to prefix or postfix", "Exit"}}},
    {"sort", Menu{.title= "Sorting", .items = {"Insertion sort", "Heap sort", "Back to main menu"}}},
    {"infix", Menu{.title= "Infix Conversion", .items = {"To prefix", "To postfix", "Back to main menu"}}},
};

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

string join(vector<int> numbers, string separator) {
    if(numbers.begin() == numbers.end()) return "";
    string result = to_string(*numbers.begin());
    for(auto i = numbers.begin() + 1; i != numbers.end(); ++i) {
        result += separator + to_string(*i);
    }
    return result;
}

void show(vector<int> numbers) {
    if(numbers.begin() == numbers.end()) return;
    cout << *numbers.begin();
    for(auto i = numbers.begin() + 1; i != numbers.end(); ++i) {
        cout << "," << *i;
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

int prompt_menu(Menu menu, string output) {
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

        if(output.size() > 0) {
            cout << "\n\033[32m" << output << "\033[0m" << "\n";
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

vector_prompt_result prompt_vector(string message) {
    string error = "";
    while(true) {
        vector<int> result;
        clearScreen();
        cout << "\n";
        if(message.size() > 0) cout << message << "\n";
        cout << "You can type \033[33mb\033[0m to get back to menu\n";

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

int_prompt_result prompt_int(string message) {
    string error = "";
    while(true) {
        clearScreen();
        cout << "\n";
        if(message.size() > 0) cout << message << "\n";
        cout << "You can type \033[33mb\033[0m to get back to menu" << "\n";
        if(error.size() > 0) cout << "\n\033[31m" << error << "\033[0m" << "\n";
        error = "";
        cout << "\n-> ";
        string num;
        cin >> num;
        num = trim(num);
        if(num == "b") {
            return int_prompt_result{.back=true};
        }
        if(!is_valid_int(num, num.size())) {
            error = num + " is not a valid inteager!";
            continue;
        }
        return int_prompt_result {.number = stoi(num)};
    }
}

string remove_all_spaces(string &s) {
    string result = "";
    for (int i = 0; i<s.size(); i++) {
        if(!isspace(s[i])) {
            result += s[i];
        }
    }
    return result;
}

infix_prompt_result prompt_infix_string(string message) {
    string error = "";
    while(true) {
        clearScreen();
        cout << "\n";
        if(message.size() > 0) cout << message << "\n";
        cout << "You can type \033[33mb\033[0m to get back to menu" << "\n";
        if(error.size() > 0) cout << "\n\033[31m" << error << "\033[0m" << "\n";
        error = "";
        cout << "\n-> ";
        getchar();
        string infix;
        char char_input[1000];
        fgets(char_input, 1000, stdin);
        infix = char_input;
        infix = trim(infix);
        if(infix == "b") {
            return infix_prompt_result{.back=true};
        }
        infix = remove_all_spaces(infix);
        if(!is_valid_infix(infix)) {
            error = "The infix expression is invalid, please enter a valid expression";
            continue;
        }
        return infix_prompt_result {.s = infix};
    }
}

void addEdge(int a, int b, map<int,graph_node *> &nodes) {
    if(nodes.find(a) == nodes.end()) {
        nodes[a] = new graph_node();
        nodes[a] -> data = a;
    }
    if(nodes.find(b) == nodes.end()) {
        nodes[b] = new graph_node();
        nodes[b] -> data = b;
    }
    nodes[a]->neighbors.push_back(nodes[b]);
    nodes[b]->neighbors.push_back(nodes[a]);
}

graph_node* prompt_graph(string message) {
    clearScreen();
    cout << "\nPlease enter edges in the following format: \033[33mX Y\033[0m (X and Y must be positive inteagers and separated via space)\n"
         << "E.g: \033[33m1 2\033[0m\n\n"
         << "Type \033[33mb\033[0m when you are finished\n\n";
    getchar();
    int edge_number = 1;
    map<int,graph_node *> nodes;
    while(true) {
        string edge;
        cout << "Enter edge #" << edge_number<< ": ";
        char char_input[1000];
        fgets(char_input, 1000, stdin);
        edge = char_input;
        edge = trim(edge);
        if(edge == "b") {
            if(edge_number == 1) {
                cout << "\n\033[33mYou have not entered any edges yet thus you may not go to the next menu. The command is ignored\033[0m\n\n";
                edge = "";
                continue;
            }
            break;
        }
        string a="", b="";
        bool space_found = false;
        for(int i =0; i<edge.size(); i++) {
            if(space_found) {
                b+= edge[i];
            } else if(isspace(edge[i])) {
                space_found = true;
            } else {
                a += edge[i];
            }
        }
        if(!is_valid_int(a, a.size()) || !is_valid_int(b, b.size())) {
            cout << "\n\033[33mInvalid input format, The edge is ignored\033[0m\n\n";
            edge = "";
            continue;
        }
        int first_node = stoi(a), second_node = stoi(b);
        if(first_node < 1 || second_node < 1) {
            cout << "\n\033[33mNode numbers must be positive numbers\033[0m\n\n";
            edge = "";
            continue;
        }
        edge_number++;
        addEdge(first_node, second_node, nodes);
        cout << "\n";
        // add!
    }
    string error = "";
    while(true) {
        clearScreen();
        cout << "\nEnter a starting node: \n";
        if(error.size() > 0) {
            cout << "\n\033[31m" << error << "\033[0m" << "\n";
            error = "";
        }
        cout << "\n->";
        string s;
        cin >> s;
        s = trim(s);
        if(!is_valid_int(s, s.size()) || nodes.find(stoi(s)) == nodes.end()) {
            error = "You haven't defined any edge for such node";
            continue;
        }
        return nodes[stoi(s)];
    }
}

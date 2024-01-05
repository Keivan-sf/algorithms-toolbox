#include <cstdio>
#include <exception>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include "./infix_parser.h"
#include "./bfs.h"
#include "./binary_search.h"
#include "./heap.h"
#include "./insertion_sort.h"
#include "./cli.h"

using namespace::std;
void handle_sort_option() {
    prompt_menu(menus["sort"]);
}

int main() {
    string error = "";
    while(true) {
        clearScreen();
        int i = prompt_menu(menus["main"]);
        clearScreen();
        error = "";
        switch (i) {
        case 0:
            return 0;
        case 4:
            handle_sort_option();
            break;
        }
    }
}

int main2() {
    vector<int> a = {1, 5, 88, 34, -1, 3, 2, 1990};
    sort_with_insertion_sort(a);
    /* show(a) */
    /* sort_with_heap_sort(a); */
    show(a);
    cout << find_with_binary_search(88, a) << endl;

    /* vector<graph_node> nodes; */
    /* for(int i = 0; i<7; i++) { */
    /*     nodes.push_back(graph_node { */
    /*         .marked = false, */
    /*         .data = i, */
    /*     }); */
    /* } */
    /* nodes[0].neighbors.push_back(&nodes[1]); */
    /* nodes[0].neighbors.push_back(&nodes[2]); */
    /*  */
    /* nodes[1].neighbors.push_back(&nodes[0]); */
    /* nodes[1].neighbors.push_back(&nodes[3]); */
    /* nodes[1].neighbors.push_back(&nodes[4]); */
    /* nodes[1].neighbors.push_back(&nodes[5]); */
    /*  */
    /* nodes[2].neighbors.push_back(&nodes[0]); */
    /* nodes[2].neighbors.push_back(&nodes[5]); */
    /* nodes[2].neighbors.push_back(&nodes[6]); */
    /*  */
    /* nodes[3].neighbors.push_back(&nodes[1]); */
    /* nodes[3].neighbors.push_back(&nodes[4]); */
    /*  */
    /* nodes[4].neighbors.push_back(&nodes[1]); */
    /* nodes[4].neighbors.push_back(&nodes[3]); */
    /*  */
    /* nodes[5].neighbors.push_back(&nodes[1]); */
    /* nodes[5].neighbors.push_back(&nodes[2]); */
    /*  */
    /* nodes[6].neighbors.push_back(&nodes[2]); */
    /* cout << perform_bfs(&nodes[0]) << endl; */

    /* cout << infixToPrefix("a+c/d*d") << endl; */
    /* cout << infixToPostfix("a+c/d*d") << endl; */

    return 0;
}

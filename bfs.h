#ifndef bfs
#define bfs
#include <iostream>
#include <vector>
using namespace std;

struct graph_node {
    bool marked = false;
    int data;
    vector<graph_node*> neighbors;
};

string perform_bfs(graph_node* start);
#endif

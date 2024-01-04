#include <iostream>
#include <vector>
#include "./bfs.h"
using namespace::std;


class GraphQueue {
public:
    struct queue_node {
        graph_node* g_node;
        queue_node *next;
    };
    queue_node* front = NULL;
    queue_node* rear = NULL;
    void add(graph_node* g_node) {
        queue_node *new_node = new(queue_node);
        new_node->g_node = g_node;
        if(rear != NULL) {
            rear->next = new_node;
        }
        rear = new_node;
        if(front == NULL) {
            front = new_node;
        }
    }
    graph_node* shift() {
        if(front == NULL) {
            throw std::logic_error("No element in the queue");
        }
        if(front == rear) {
            rear = NULL;
        }
        queue_node *new_front = front->next;
        graph_node* g_node = front->g_node;
        delete(front);
        front = new_front;
        return g_node;
    }
    graph_node* peek() {
        if(front == NULL) return NULL;
        return front->g_node;
    }
};


string perform_bfs(graph_node* start) {
    GraphQueue q;
    q.add(start);
    start->marked = true;
    string result = "";
    while(q.peek()) {
        graph_node* current = q.shift();
        result += to_string(current->data) + " -> ";
        for(auto i = current->neighbors.begin(); i!=current->neighbors.end(); ++i) {
            if(!(*i)->marked) {
                (*i)-> marked = true;
                q.add(*i);
            }
        }
    }
    return result;
}

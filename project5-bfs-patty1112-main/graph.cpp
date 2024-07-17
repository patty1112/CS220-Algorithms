/*
 * graph.cpp
 *
 * Method definitions for the graph class.
 *
 * Author: <your name here>
 */

#include "graph.h"

graph::graph(int vertex_count) {
    nodeCount = vertex_count;
    vector<vector<int>> newVector(vertex_count);
    for(size_t i = 0; i < newVector.size(); i++) {
        vector<int> adjList;
        newVector[i] = adjList;
    }
    this->adjList = newVector;

}

void graph::add_edge(int from, int to) {
    adjList[from].push_back(to);
}

vector<int> graph::find_shortest_path(int from, int to) {
    vector<bool> visited(nodeCount);
    for(size_t i = 0; i < visited.size(); i++) {
        visited[i] = false;
    }
    graph pathTree(nodeCount);
    queue<int> toCheck;
    visited[from] = true;
    toCheck.push(from);

    int current;
    while(!(toCheck.empty()) && !(visited[to])) {
        current = toCheck.front();
        toCheck.pop();
        for(int i: adjList[current]) {
            if(visited[i] == false) {
                toCheck.push(i);
                visited[i] = true;
                pathTree.add_edge(i, current);
            }
        }
    }
    vector<int> path;
    if(visited[to]) {
        path.push_back(to);
        while(to != from) {
            to = pathTree.adjList[to].front();
            path.push_back(to);
        }
    }
    reverse(path.begin(), path.end());
    return path;
}
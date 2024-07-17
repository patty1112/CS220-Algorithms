/*
 * graph.h
 *
 * Declaration of the graph class.
 * 
 * Author: <your name here>
 */

#ifndef _GRAPH_BFS_H
#define _GRAPH_BFS_H

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class graph {
public:
    graph(int vertex_count);
    void add_edge(int from, int to);
    vector<int> find_shortest_path(int from, int to);

private:
    vector<vector<int>> adjList;
    int nodeCount;
};

#endif

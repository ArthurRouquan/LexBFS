#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using Edge = std::pair<std::size_t, std::size_t>;

struct Graph {
    std::size_t n, m;
    std::vector<Edge> edges;
    std::vector<std::vector<std::size_t>> adjlist;

    void add_edge(Edge edge) {
        edges.push_back(edge);
        adjlist[edge.first].push_back(edge.second);
        adjlist[edge.second].push_back(edge.first);
    }
};

auto read_instance(const std::string& filename) {
    Graph graph;

    std::ifstream instance;
    instance.open(filename);

    for (std::string line; getline(instance, line);) {
        std::stringstream input(line);
        if (line.at(0) == 'p') {
            input.ignore(6);
            input >> graph.n >> graph.m;
            graph.edges.reserve(graph.m);
            graph.adjlist.resize(graph.n);
        }
        if (line.at(0) == 'e') {
            input.ignore(2);
            Edge edge;
            input >> edge.first >> edge.second;
            --edge.first; --edge.second;
            graph.add_edge(edge);
        }
    }

    return graph;
}

#endif
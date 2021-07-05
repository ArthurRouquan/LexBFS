#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <iterator>
#include <limits>
#include "graph.hpp"

auto& operator>>(std::istream& is, Edge& e) {
    is.ignore(2) >> e.tail >> e.head;
    --e.tail; --e.head;
    return is;
}

auto read_col_instance(std::string_view filepath) -> GraphVectorEdges
{
    GraphVectorEdges graph;
    std::ifstream file{filepath.data()};
    for (char c = file.get(); c != 'p'; file.get(c))
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    file.ignore(6) >> graph.n >> graph.m;
    graph.edges.reserve(graph.m);
    std::copy_n(std::istream_iterator<Edge>(file), graph.m, std::back_inserter(graph.edges));
    return graph;
}
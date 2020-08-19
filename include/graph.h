#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#include <cstdio>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include "span.hpp"

template <typename node_t>
struct Edge { node_t first, last; };

template <typename T>
class CompactAdjacencyList
{
    /* Static unoriented simple graph with contiguous memory adjacency lists.
       Neighbors queries should be fast. Vertices are represented between 0 and
       n (excluded) with the given T type. */
public:
    using node_t = T;
    using size_t = std::size_t;
    using edge_t = Edge<node_t>;
    using iter_t = std::vector<node_t>::iterator;

private:
    size_t n, m;
    std::vector<node_t> adjlist;
    std::vector<iter_t> adjlist_view;

public:
    CompactAdjacencyList(size_t n, const std::vector<edge_t>& edges)
        : n(n), m(size(edges)), adjlist(2 * m), adjlist_view(n + 1)
    {
        // calculate the degree of each vertex
        std::vector<size_t> degrees(n);
        for (const auto& [u, v] : edges) { ++degrees[u]; ++degrees[v]; }

        // set the pointers for each vertex of the compacted adjacency list
        adjlist_view[0] = begin(adjlist);
        for (node_t i = 0; i < n; ++i)
            adjlist_view[i+1] = adjlist_view[i] + degrees[i];

        // fill the compacted adjacency list
        auto copy_view = adjlist_view;
        for (const auto& [u, v] : edges) {
            *copy_view[u] = v; ++copy_view[u];
            *copy_view[v] = u; ++copy_view[v];
        }
    }

    auto nb_vertices() const { return n; }

    auto nb_edges() const { return m; }

    auto neighbors(const node_t& node) const
        { return tcb::span(&*adjlist_view[node], &*adjlist_view[node + 1]); }

    auto degree(const node_t& node) const
        { return std::distance(adjlist_view[node], adjlist_view[node + 1]); }

    auto print() const {
        for (node_t i = 0; i < n; ++i) {
            std::printf("[%u] : ", i);
            for (const auto& n : neighbors(i)) std::printf("%u ", n);
            std::puts("");
        }
    }
};



template <typename node_t>
auto read_instance(const std::string& filename) {
    std::vector<Edge<node_t>> edges;
    std::size_t n, m;

    std::ifstream instance;
    instance.open(filename);

    for (std::string line; getline(instance, line);)
    {
        std::stringstream input(line);

        if (line.at(0) == 'p') {
            input.ignore(6);
            input >> n >> m;
            edges.reserve(m);
        } else if (line.at(0) == 'e') {
            input.ignore(2);
            Edge<node_t> edge;
            input >> edge.first >> edge.last;
            --edge.first; --edge.last; // instance files starting vertex is 1
            edges.push_back(std::move(edge));
        }
    }

    return CompactAdjacencyList(n, edges);
}

#endif
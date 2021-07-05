#pragma once
#include <vector>
#include <span>
#include <cstdint>
#include <cstdio>
#include <ranges>
#include <iostream>

using vertex_t = std::uint32_t;
using size_t = std::size_t;

struct Edge { vertex_t tail, head; };

/* Represents a graph as a collection of edges. */
struct GraphVectorEdges
{
    vertex_t n; size_t m; // number of vertices (resp. edges)
    std::vector<Edge> edges;
};

/* Represents an undirected graph with contiguous memory adjacency lists (glued together in a vector
and accessed individually with a std::span). Neighbors queries should be fast. */
class Graph
{
public:
    Graph(GraphVectorEdges const& graph);
    auto nb_vertices() const { return n; }
    auto nb_edges() const { return m; }
    auto vertices() const { return std::ranges::iota_view{vertex_t{0}, n}; }
    auto neighbors(vertex_t node) const { return adjlist_span[node]; }
    auto degree(vertex_t node) const { return size(adjlist_span[node]); }
    void print_adjlist() const;

private:
    vertex_t n; size_t m; // number of vertices (resp. edges)
    std::vector<vertex_t> adjlist;
    std::vector<std::span<vertex_t>> adjlist_span;
};


Graph::Graph(GraphVectorEdges const& graph) : n(graph.n), m(graph.m), adjlist(2*m), adjlist_span(n)
{
    std::vector<vertex_t> degree(n, 0);
    for (auto [u, v] : graph.edges) { ++degree[u]; ++degree[v]; }
    
    std::vector<decltype(adjlist)::iterator> it(n + 1);
    it[0] = begin(adjlist);
    for (auto u : vertices()) {
        it[u + 1] = it[u] + degree[u];
        adjlist_span[u] = std::span(it[u], it[u + 1]);
    }

    for (auto [u, v] : graph.edges) {
        *it[u] = v; *it[v] = u;
        ++it[u]; ++it[v];
    }
}


void Graph::print_adjlist() const
{
    std::printf("Graph G = (V, E) - |V| = %zu, |E| = %zu\n", n, m);
    for (auto u : vertices()) {
        std::printf("[%u]: ", u);
        for (auto v : neighbors(u))
            std::printf("%u ", v);
        std::puts("");
    }
}
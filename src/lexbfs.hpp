#pragma once
#include <optional>
#include <numeric>
#include <list>
#include <forward_list>
#include "graph.hpp"


/* Returns the Lexicographic Breadth-First Search (Lex-BFS) ordering of the given graph G = (V, E)
and a (0 by default) starting vertex in linear time O(|V| + |E|). */
std::vector<vertex_t> lexBFS(Graph const& graph, std::optional<vertex_t> const start_vertex = {})
{
    std::vector<vertex_t> ordering(graph.nb_vertices());
    std::iota(begin(ordering), end(ordering), 0);

    struct Interval { decltype(ordering)::iterator start; };
    std::list<Interval> intervals{{begin(ordering)}, {end(ordering)}};
    
    struct VertexInfo {
        decltype(ordering)::iterator order;
        decltype(intervals)::iterator interval;
        bool reached;
    };
    std::vector<VertexInfo> vertices_info;
    vertices_info.reserve(graph.nb_vertices());
    for (auto it = begin(ordering); it != end(ordering); ++it)
        vertices_info.emplace_back(it, begin(intervals), false);

    auto pop_front = [&](auto interval) {
        if (next(interval->start) != next(interval)->start) ++interval->start;
        else intervals.erase(interval); // careful, the given iterator could become invalid
    };

    auto swap_order = [](auto& lhs_order, auto& rhs_order) {
        std::swap(lhs_order, rhs_order);
        std::iter_swap(lhs_order, rhs_order);
    };

    if (start_vertex) swap_order(vertices_info[*start_vertex].order, vertices_info.front().order);

    for (auto const pivot : ordering) // algorithm's main loop
    {
        vertices_info[pivot].reached = true;
        pop_front(vertices_info[pivot].interval);
        for (auto const neighbor : graph.neighbors(pivot)) // partition refinement
        {
            auto& [order, interval, reached] = vertices_info[neighbor];
            if (reached) continue;
            swap_order(order, vertices_info[*interval->start].order); // swap the adjacent vertex with the front element of its interval
            if (interval == begin(intervals)) intervals.emplace_front(order); // create a new interval if there is no interval with higher priority
            pop_front(interval--); // move it to the 'next' interval with higher priority and remove it from its previous interval
        }
    }
    
    return ordering;
}


/* Checks if a graph is chordal in linear time O(|V|+|E|) of the given graph G = (V, E). Slighty mo
-dificated version of FILL Algorithm found in the article "Algorithmic aspects of vertex elimination
on graphs" (1976) (Rose, Tarjan, Lueker) */
bool is_chordal(Graph const& graph)
{
    auto ordering = lexBFS(graph);
    
    std::vector<vertex_t> index(graph.nb_vertices());    
    for (auto u : graph.vertices()) index[ordering[u]] = u;

    static constexpr auto Undefined = std::numeric_limits<vertex_t>::max();
    std::vector<vertex_t> pred(graph.nb_vertices(), Undefined);
    
    for (const auto& vertex : ordering)
    {
        vertex_t index_parent = Undefined;
        vertex_t counter = 0;

        for (const auto& neighbor : graph.neighbors(vertex))
            if (index[neighbor] > index[vertex]) {
                pred[neighbor] = vertex;
                index_parent = std::min(index_parent, index[neighbor]);
                ++counter;
            }
        
        if (index_parent == Undefined) continue;
        for (const auto adj_parent : graph.neighbors(ordering[index_parent]))
            counter -= (pred[adj_parent] == vertex);

        if (counter > 1) return false;
    }

    return true;
}
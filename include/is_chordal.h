#ifndef CHORDAL_H
#define CHORDAL_H

#include <vector>
#include <algorithm>
#include "graph.h"
#include "lexbfs.h"

template<class Graph>
auto is_chordal(const Graph& graph)
{
    /* Checks if a graph is chordal in linear time O(|V|+|E|) of the given graph
       G = (V, E). Slighty modificated version of FILL Algorithm found in the
       article "Algorithmic aspects of vertex elimination on graphs" (1976)
       (Rose, Tarjan, Lueker) */

    auto ordering = lexBFS(graph);

    std::vector<std::size_t> index(graph.nb_vertices());    
    for (std::size_t i = 0; i < graph.nb_vertices(); ++i)
        index[ordering[i]] = i;

    std::vector<std::size_t> test(graph.nb_vertices(), graph.nb_vertices() + 1);
    
    for (const auto& vertex : ordering)
    {
        std::size_t idx_parent = graph.nb_vertices() + 1;
        std::size_t counter = 0;

        for (const auto& neighbor : graph.neighbors(vertex))
            if (index[neighbor] > index[vertex]) {
                test[neighbor] = vertex;
                idx_parent = std::min<std::size_t>(idx_parent, index[neighbor]);
                ++counter;
            }
        
        for (const auto adj_parent : graph.neighbors(ordering[idx_parent]))
            counter -= (test[adj_parent] == vertex);

        if (counter > 1) return false;
    }

    return true;
}

#endif
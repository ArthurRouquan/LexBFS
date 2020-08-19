#ifndef LEXBFS_H
#define LEXBFS_H

#include <list>
#include <numeric>
#include <vector>
#include <optional>
#include "graph.h"

template<class Graph>
auto lexBFS(const Graph& graph, std::optional<std::size_t> starting_vertex = {})
{
    /* Returns the Lexicographic Breadth-First Search (Lex-BFS) ordering of the
       given graph G = (V, E) and a (0 by default) starting vertex in liear time
       O(|V| + |E|). */

    // Structures declaration ──────────────────────────────────────────────────

    using node_t = typename Graph::node_t;
    struct Interval { std::vector<node_t>::iterator first, last; };
    struct VertexView // easy access on the priority and interval of a vertex
    { 
        std::vector<node_t>::iterator priority;
        std::list<Interval>::iterator interval;
        bool visited;
    };

    // Variables declaration ───────────────────────────────────────────────────

    std::vector<node_t> ordering(graph.nb_vertices()); // vertices are sorted by descending order of priority
    std::iota(begin(ordering), end(ordering), 0);

    std::list<Interval> intervals{{begin(ordering), --end(ordering)}}; // starts with one interval containing all vertices

    std::vector<VertexView> vertices_view(graph.nb_vertices()); 
    std::for_each(begin(vertices_view), end(vertices_view),
        [&, it = begin(ordering)](auto& node)
        mutable { node = {it++, begin(intervals), false}; });

    // Lambdas definition ──────────────────────────────────────────────────────

    auto is_empty = [](auto&& interval)
        { return (interval->first == interval->last + 1); };
        
    auto shrink_front = [&](auto&& interval) { 
        ++interval->first;
        if (is_empty(interval))
            intervals.erase(interval); // the iterator could be invalidate
    };

    auto swap_priority = [](auto& lhs_priority, auto& rhs_priority) {
        std::swap(lhs_priority, rhs_priority);
        std::iter_swap(lhs_priority, rhs_priority);
    };

    // Lex-BFS Algorithm ───────────────────────────────────────────────────────

    if (starting_vertex)
        swap_priority(vertices_view[*starting_vertex].priority,
                      vertices_view.front().priority);

    for (const auto& pivot : ordering) // algorithm main loop
    {
        vertices_view[pivot].visited = true;
        shrink_front(vertices_view[pivot].interval);

        for (const auto& adjacent_vertex : graph.neighbors(pivot)) // partition refinement
        {
            auto& [priority, interval, visited] = vertices_view[adjacent_vertex];
            if (visited) continue;
            swap_priority(priority, vertices_view[*interval->first].priority); // swap the adjacent vertex with the front element of its interval in the ordering
            if (interval == begin(intervals))
                intervals.push_front({priority, priority});
            (--interval)->last = priority; // move it to the 'next' interval with higher priority
            shrink_front(next(interval)); // remove it from its previous interval
        }
    }

    return ordering;
}

#endif


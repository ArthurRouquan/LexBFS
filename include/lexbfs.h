#ifndef LEXBFS_H
#define LEXBFS_H

#include <cstdio>
#include <list>
#include <numeric>
#include <vector>
#include <optional>
#include <algorithm>
#include "graph.h"

struct Interval {
    std::vector<std::size_t>::iterator first, last;
    bool empty() { return first == last + 1; }
};

struct VertexView {
    std::vector<std::size_t>::iterator priority;
    std::list<Interval>::iterator interval;
    bool visited;
};

auto lexBFS(const Graph& graph, std::optional<std::size_t> starting_vertex = std::nullopt)
{
    /* returns the Lexicographic Breadth-First Search (Lex-BFS) ordering of the given
       graph G(V, E) and a (0 by default) starting vertex in O(|V| + |E|).
       Remove the commented lines to print the iterations. */

    std::vector<std::size_t> ordering(graph.n); // vertices sorted by order of priority
    std::iota(begin(ordering), end(ordering), 0);

    std::list<Interval> intervals{{begin(ordering), --end(ordering)}};
    
    std::vector<VertexView> vertices_view(graph.n); // easy access on the priority and interval of a given vertex (iterators on ordering and intervals)
    std::for_each(begin(vertices_view), end(vertices_view), [&, it = begin(ordering)](auto& node)
        mutable { node = {it++, begin(intervals), false}; });

    // auto print_interval = [](const Interval& interval) {
    //     printf("{");
    //     std::for_each(interval.first, interval.last, [](auto i) { printf("%zu,", i); });
    //     printf("%zu} ", *interval.last);
    // };

    auto shrink_front = [&](auto&& interval) { 
        ++interval->first;
        if (interval->empty())
            intervals.erase(interval); // careful, the iterator interval could become invalidate!
    };

    auto swap_priority = [](auto& lhs_priority, auto& rhs_priority) {
        std::swap(lhs_priority, rhs_priority);
        std::iter_swap(lhs_priority, rhs_priority);
    };

    if (starting_vertex)
        swap_priority(vertices_view[*starting_vertex].priority, begin(vertices_view)->priority);

    for (const auto pivot : ordering) // algorithm main loop
    {
        // printf("Pivot [%zu]\n", pivot);
        vertices_view[pivot].visited = true;
        shrink_front(vertices_view[pivot].interval);

        for (const auto adjacent_vertex : graph.adjlist[pivot]) // partition refinement
        {
            auto& [priority, interval, visited] = vertices_view[adjacent_vertex];
            if (visited) continue;
            swap_priority(priority, vertices_view[*interval->first].priority); // swap the adjacent vertex with the front element of its interval in the ordering
            if (interval == begin(intervals))
                intervals.push_front({priority, priority});
            (--interval)->last = priority; // move it to the 'next' interval with higher priority
            shrink_front(next(interval)); // remove it from its previous interval
            // printf("   * [%zu] : ", adjacent_vertex);
            // std::for_each(begin(intervals), end(intervals), print_interval); puts("");
        }
    }

    return ordering;
}

#endif
#include <cstdio>
#include <chrono>
#include "graph.h"
#include "lexbfs.h"
#include "is_chordal.h"

int main(int argc, char *argv[])
{
    std::string instance = (argc >= 2 ? argv[1] : "toy2");
    auto graph = read_instance<size_t>("graph_instances/" + instance + ".col");
    printf("Input graph G = (V, E) instance:\n   * Name: %s\n   * |V| = %zu\n   * |E| = %zu\n",
        instance.c_str(), graph.nb_vertices(), graph.nb_edges());
    
    auto print_ordering = [](const auto& ordering) {
        printf("Lex-BFS ordering = [");
        std::for_each(begin(ordering), --end(ordering), [](auto i) { printf("%zu,", i); });
        printf("%zu]\n", *--end(ordering));
    };
    
    {
        auto time_start = std::chrono::steady_clock::now();
        auto ordering = lexBFS(graph);
        auto duration = duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - time_start).count();
        printf("Lex-BFS algorithm duration: %zd µs\n", duration);
        print_ordering(ordering);
    }

    printf("Graph %s chordal.\n", is_chordal(graph) ? "is" : "isn't");
    
    return EXIT_SUCCESS;
}
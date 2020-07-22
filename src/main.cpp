#include <iostream>
#include <chrono>
#include "graph.h"
#include "lexbfs.h"

int main(int argc, char *argv[])
{
    std::string instance = (argc >= 2 ? argv[1] : "myciel3");
    auto graph = read_instance("graph_instances/" + instance + ".col");
    printf("Input graph G(V, E) instance:\n   * Name: %s\n   * |V| = %zu\n   * |E| = %zu\n",
        instance.c_str(), graph.n, graph.m);

    auto time_start = std::chrono::steady_clock::now();

    auto ordering = lexBFS(graph);
    
    auto duration = duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - time_start).count();
    printf("Algorithm duration: %zd µs\n", duration);

    printf("π = [");
    std::for_each(begin(ordering), --end(ordering), [](auto i) { printf("%zu,", i); });
    printf("%zu]\n", *--end(ordering));

    return EXIT_SUCCESS;
}
#include "graph.hpp"
#include "instance_reader.hpp"
#include "lexbfs.hpp"
#include <chrono>
#include <iostream>


int main(int argc, char* argv[])
{
    if (argc != 2) throw std::runtime_error("No input file.");
    Graph graph{read_col_instance(argv[1])};
    std::printf("\nInput instance G = (V, E) - |V| = %zu, |E| = %zu\n", graph.nb_vertices(), graph.nb_edges());

    auto start = std::chrono::steady_clock::now();
    auto ordering = lexBFS(graph);
    auto duration = duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();

    std::printf("Lex-BFS ordering: ");
    for (auto v : ordering) std::printf("%zu ", v);
    std::printf("\nLex-BFS algorithm's duration: %zu us", duration);
    std::printf("\nThe graph %s chordal.\n", is_chordal(graph) ? "is" : "isn't");
}
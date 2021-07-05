# Lexicographic Breadth-First Search Algorithm

Implementation in C++20 of the [Lex-BFS](https://en.wikipedia.org/wiki/Lexicographic_breadth-first_search) algorithm based on the idea of partition refinement (first developed by Donald J. Rose, Robert E. Tarjan, and George S. Lueker), in linear time O(|V| + |E|) given a graph G = (V, E) and an optional starting vertex. This implementation was made for educational purposes.

## Data structures

![GitHub Logo](/img/data_structures.png)

## How to run it?

This project uses CMake. To run the executable you need to pass a graph instance .col file:

```
$ lexbfs ../graph_instances/toy2.col

Input instance G = (V, E) - |V| = 7, |E| = 14
Lex-BFS ordering: 0 1 2 3 6 4 5 
Lex-BFS algorithm's duration: 4 us
The graph is chordal.
```

## References
1. Graph instances : https://mat.tepper.cmu.edu/COLOR/instances.html

2. Rose, D. J., Tarjan, R. E., Lueker, G. S., *Algorithmic aspects of vertex elimination on graphs* (1976) https://doi.org/10.1137%2F0205021
3. Habib M., McConnell R., Paul C., Viennot L., *Lex-BFS and partition refinement, with applications to transitive orientation, interval graph recognition and consecutive ones testing* (2000) https://doi.org/10.1016/S0304-3975(97)00241-7
4. Derek G. Corneil, *Lexicographic Breadth First Search – A Survey* (2004) https://doi.org/10.1007%2F978-3-540-30559-0_1

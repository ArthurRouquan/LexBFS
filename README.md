# Lexicographic Breadth-First Search Algorithm in modern C++

Implementation in modern C++ of the [Lex-BFS](https://en.wikipedia.org/wiki/Lexicographic_breadth-first_search) algorithm based on the idea of partition refinement (first developed by Donald J. Rose, Robert E. Tarjan, and George S. Lueker), in linear time O(|V| + |E|) given a graph G = (V, E) and an optional starting vertex.

## How to run it?

```console
make
./bin/main instance_name
```

## References

1. Graph instances : https://mat.tepper.cmu.edu/COLOR/instances.html
2. Rose, D. J., Tarjan, R. E., Lueker, G. S., *Algorithmic aspects of vertex elimination on graphs* (1976) https://doi.org/10.1137%2F0205021
3. Habib M., McConnell R., Paul C., Viennot L., *Lex-BFS and partition refinement, with applications to transitive orientation, interval graph recognition and consecutive ones testing* (2000) https://doi.org/10.1016/S0304-3975(97)00241-7
4. Derek G. Corneil, *Lexicographic Breadth First Search – A Survey* (2004) https://doi.org/10.1007%2F978-3-540-30559-0_1

# Lexicographic Breadth-First Search Algorithm in modern C++

Implementation in modern C++ of the [Lex-BFS](https://en.wikipedia.org/wiki/Lexicographic_breadth-first_search) algorithm based on the idea of partition refinement (first developed by Donald J. Rose, Robert E. Tarjan, and George S. Lueker), in linear time O(|V| + |E|) given a graph G = (V, E) and an optional starting vertex.

## How to run it?

```console
$ make
$ ./bin/main instance_name
```

Output example (with uncommented print lines)
```console
$ ./bin/main myciel3
Input graph G(V, E) instance:
   * Name: myciel3
   * |V| = 11
   * |E| = 20
Pivot [0]
   * [1] : {1} {2,3,4,5,6,7,8,9,10} 
   * [3] : {1,3} {2,4,5,6,7,8,9,10} 
   * [6] : {1,3,6} {4,5,2,7,8,9,10} 
   * [8] : {1,3,6,8} {5,2,7,4,9,10} 
Pivot [1]
   * [2] : {3,6,8,2} {5,7,4,9,10} 
   * [5] : {3,6,8,2,5} {7,4,9,10} 
   * [7] : {3,6,8,2,5,7} {4,9,10} 
Pivot [3]
   * [4] : {6,8,2,5,7,4} {9,10} 
   * [5] : {5} {8,2,6,7,4} {9,10} 
   * [9] : {5} {8,2,6,7,4,9} {10} 
Pivot [5]
   * [10] : {8,2,6,7,4,9,10} 
Pivot [8]
   * [4] : {4} {6,7,2,9,10} 
   * [10] : {4,10} {7,2,9,6} 
Pivot [4]
   * [2] : {10,2} {7,9,6} 
   * [7] : {10,2,7} {9,6} 
Pivot [10]
   * [6] : {2,7,6} {9} 
   * [7] : {7} {2,6} {9} 
   * [9] : {7} {2,6,9} 
Pivot [7]
Pivot [2]
   * [6] : {6} {9} 
   * [9] : {6,9} 
Pivot [6]
Pivot [9]
Algorithm duration: 78 µs
π = [0,1,3,5,8,4,10,7,2,6,9]
```
## References

1. Graph instances : https://mat.tepper.cmu.edu/COLOR/instances.html
2. Rose, D. J., Tarjan, R. E., Lueker, G. S., *Algorithmic aspects of vertex elimination on graphs* (1976) https://doi.org/10.1137%2F0205021
3. Habib M., McConnell R., Paul C., Viennot L., *Lex-BFS and partition refinement, with applications to transitive orientation, interval graph recognition and consecutive ones testing* (2000) https://doi.org/10.1016/S0304-3975(97)00241-7
4. Derek G. Corneil, *Lexicographic Breadth First Search – A Survey* (2004) https://doi.org/10.1007%2F978-3-540-30559-0_1

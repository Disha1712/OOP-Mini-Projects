# Graph Data Structure

## Overview
The Graph Data Structure is implemented as an undirected graph with various operations using operator overloading.

## Features
### Graph Class
- **Attributes:**
  - `vertices` (private): Set of vertices.
  - `edges` (private): List of edges.

- **Methods:**
  - `operator+ (Graph G)`: Returns the union of two graphs.
  - `operator- (Graph G)`: Returns the intersection of two graphs.
  - `operator!()`: Returns the complement of a graph.
  - `operator>> (istream&)`: Reads graph data.
  - `operator<< (ostream&)`: Prints the graph.
  - `isReachable(u, v)`: Checks if vertex `v` is reachable from `u`.
  - `addEdge(u, v)`: Adds an edge between `u` and `v`.
  - `removeEdge(u, v)`: Removes an edge between `u` and `v`.

## Formal Definitions
### Union of Graphs (G1 + G2)
Given two graphs G1(V1, E1) and G2(V2, E2), their union is:
- **Vertex Set**: V = V1 ∪ V2
- **Edge Set**: E = E1 ∪ E2

### Intersection of Graphs (G1 - G2)
Given two graphs G1(V1, E1) and G2(V2, E2), their intersection is:
- **Vertex Set**: V = V1 ∪ V2
- **Edge Set**: E = E1 ∩ E2

### Complement of a Graph (!G)
For a graph G(V, E), its complement G' has:
- The same vertex set V.
- An edge between two vertices if and only if there was no edge between them in G.

## Input Format
- `Graph` (Keyword to indicate graph input)
- `N M` (Number of vertices N and edges M)
- `u v` (M lines, each representing an edge between u and v)
- Operations:
  - `union`
  - `intersection`
  - `complement`
  - `isReachable u v`
  - `add_edge u v`
  - `remove_edge u v`
  - `printGraph`
  - `end` (terminates input)

## Output Format
- `isReachable u v`: Prints "Yes" or "No".
- `printGraph`: Displays each vertex and its adjacent vertices.

## Sample Input
```
Graph
4 3
0 1
1 2
2 3
printGraph
isReachable 0 3
complement
printGraph
end
```

## Sample Output
```
Vertex 0: 1
Vertex 1: 0 2
Vertex 2: 1 3
Vertex 3: 2
Yes
Vertex 0: 2 3
Vertex 1: 3
Vertex 2: 0
Vertex 3: 0 1
```

## Additional Notes
- Operator overloading is used.
- The graph is undirected and uses 0-based indexing.
- Duplicate edges are ignored.


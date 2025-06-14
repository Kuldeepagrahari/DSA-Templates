# 📘 DSA Templates README (C++ Implementations)

This README contains categorized explanations of all major Data Structures and Algorithms templates included in this C++ template repository.

---

## 🔗 Graph Algorithms

Includes templates for:

- BFS, DFS
- Dijkstra's Algorithm
- Bellman-Ford
- Floyd-Warshall
- Union-Find (DSU)
- Kruskal's and Prim's MST
- Tarjan’s SCC / Bridges / Articulation Points
- Topological Sort (DFS & Kahn’s)
- 0-1 BFS / Multi-source BFS / Bi-directional BFS
- Euler Tour / Binary Lifting / LCA
- Dynamic Connectivity with DSU (with rollback or segment tree)

📌 **Usage Hint:** Graph templates are modular—always begin with a basic DFS/BFS and incrementally move to Tarjan, SCC, or MST as needed.

---

## 🧮 Dynamic Programming (DP)

Includes templates for:

- 1D/2D DP (Tabulation + Memoization)
- Knapsack, LIS, Subset Sum, Matrix Chain Multiplication
- Bitmask DP
- Tree DP, Digit DP, Interval DP, DP on Grids
- DP + Bitmask + Graphs, DP + Sliding Window
- DP with Memory Optimization
- State Compression, DP + Binary Search

🧠 **Revision Tip:** For each DP pattern, memorize:
1. State representation
2. Transition logic
3. Base cases
4. Iteration order (Top-Down or Bottom-Up)

---

## 🌲 Tree & BST Templates

Templates include:

- DFS, Preorder, Postorder, Inorder
- LCA (Binary Lifting & Euler Tour)
- Diameter, Subtree Sum, Tree Distances
- Tree Flattening
- Fenwick Tree (Binary Indexed Tree)
- Segment Tree + Lazy Propagation
- AVL / Treap / Red-Black Trees (basic simulation or usage)

💡 **Pro Tip:** Practice subtree and rerooting problems. Focus on “combine child DP states” logic.

---

## 🔍 Hashing

Covers:

- Open Addressing: Linear / Quadratic / Double Hashing
- Separate Chaining
- Frequency Maps, Grouping with HashMaps
- Rolling Hash (Double Hash for collisions)
- Custom Hash functions (e.g. splitmix64)
- Hashing for Palindrome Checks, Substring Matching

🎯 **Important:** Always guard against collisions in contests—prefer unordered_map with custom hash.

---

## 🔠 String Algorithms

Templates include:

- KMP Prefix Table
- Z-Algorithm
- Suffix Array + LCP (Kasai’s)
- Trie + Trie with Count
- Aho-Corasick (on request)
- Manacher's Algorithm
- Rabin-Karp / Rolling Hash
- Longest Repeated/Palindromic Substrings

📎 **Hint:** Use Suffix Arrays + LCP for substring count queries; Z-Algorithm for pattern matching.

---

## 📁 Others (Heap, Deque, Sliding Window, Monotonic Stack, etc.)

- Stack/Queue/Deque Implementations
- Monotonic Stack/Queue (Next Greater Element)
- Sliding Window Max/Min
- Priority Queue usage in Graphs or Merging K Lists

---

## 🧠 Revision Tips

1. Revisit one category weekly. Aim to dry-run or implement from memory.
2. Add LeetCode problem tags for each.
3. Use visualizer tools for trees/graphs.
4. Practice pattern mixing: Tree + DP, Bitmask + Graphs, etc.
5. Highlight intuition: What subproblems lead to optimal solutions?

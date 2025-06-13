// ================================
// Complete Graph Algorithms Template
// ================================

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
vector<int> adj[N];
bool visited[N];

// ---------------------------
// DFS (Recursive)
// ---------------------------
void dfs(int node) {
    visited[node] = true;
    for (int child : adj[node]) {
        if (!visited[child]) dfs(child);
    }
}

// ---------------------------
// DFS (Iterative)
// ---------------------------
void dfs_iterative(int start) {
    stack<int> s;
    s.push(start);
    while (!s.empty()) {
        int node = s.top(); s.pop();
        if (!visited[node]) {
            visited[node] = true;
            for (int i = adj[node].size()-1; i >= 0; --i) {
                if (!visited[adj[node][i]]) s.push(adj[node][i]);
            }
        }
    }
}

// ---------------------------
// BFS
// ---------------------------
void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int child : adj[node]) {
            if (!visited[child]) {
                visited[child] = true;
                q.push(child);
            }
        }
    }
}

// ---------------------------
// Topological Sort (DFS)
// ---------------------------
vector<int> topo_sort;
void topo_dfs(int node) {
    visited[node] = true;
    for (int child : adj[node]) {
        if (!visited[child]) topo_dfs(child);
    }
    topo_sort.push_back(node);
}

// ---------------------------
// Topological Sort (Kahn's Algo)
// ---------------------------
void kahn_topo(int n) {
    vector<int> indeg(n, 0);
    for (int i = 0; i < n; i++) for (int x : adj[i]) indeg[x]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int node = q.front(); q.pop();
        cout << node << ' ';
        for (int x : adj[node]) {
            indeg[x]--;
            if (indeg[x] == 0) q.push(x);
        }
    }
}

// ---------------------------
// Cycle Detection (Undirected DFS)
// ---------------------------
bool dfs_cycle(int node, int parent) {
    visited[node] = true;
    for (int child : adj[node]) {
        if (!visited[child]) {
            if (dfs_cycle(child, node)) return true;
        } else if (child != parent) {
            return true;
        }
    }
    return false;
}

// ---------------------------
// Cycle Detection (Directed Graph)
// ---------------------------
bool dfs_cycle_directed(int node, vector<int>& state) {
    state[node] = 1;
    for (int child : adj[node]) {
        if (state[child] == 0) {
            if (dfs_cycle_directed(child, state)) return true;
        } else if (state[child] == 1) {
            return true;
        }
    }
    state[node] = 2;
    return false;
}

// ---------------------------
// Connected Components
// ---------------------------
void find_components(int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
            count++;
        }
    }
    cout << "Connected components: " << count << '\n';
}

// ---------------------------
// Bipartite Graph Check
// ---------------------------
bool is_bipartite(int n) {
    vector<int> color(n, -1);
    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// ---------------------------
// Dijkstra's Algorithm
// ---------------------------
#define pii pair<int, int>
vector<pii> adjw[N];
int dist[N];
void dijkstra(int src, int n) {
    fill(dist, dist + n, 1e9);
    dist[src] = 0;
    set<pii> s;
    s.insert({0, src});
    while (!s.empty()) {
        auto [d, u] = *s.begin();
        s.erase(s.begin());
        for (auto [v, w] : adjw[u]) {
            if (dist[u] + w < dist[v]) {
                s.erase({dist[v], v});
                dist[v] = dist[u] + w;
                s.insert({dist[v], v});
            }
        }
    }
}

// ---------------------------
// Bellman-Ford
// ---------------------------
struct Edge { int u, v, wt; };
vector<Edge> edges;
int bellman_ford(int n, int src) {
    vector<int> d(n, 1e9);
    d[src] = 0;
    for (int i = 1; i < n; i++) {
        for (auto e : edges) {
            if (d[e.u] + e.wt < d[e.v]) {
                d[e.v] = d[e.u] + e.wt;
            }
        }
    }
    for (auto e : edges) {
        if (d[e.u] + e.wt < d[e.v]) return -1; // negative cycle
    }
    return 0;
}

// ---------------------------
// Floyd-Warshall
// ---------------------------
int fw[N][N];
void floyd(int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fw[i][j] = min(fw[i][j], fw[i][k] + fw[k][j]);
}

// ---------------------------
// Prim's Algorithm
// ---------------------------
bool inMST[N];
int prims(int n) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    int cost = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        cost += w;
        for (auto [v, wt] : adjw[u]) {
            if (!inMST[v]) pq.push({wt, v});
        }
    }
    return cost;
}

// ---------------------------
// Kruskal's Algorithm
// ---------------------------
struct Edge2 {
    int u, v, wt;
    bool operator<(Edge2 const& e) const {
        return wt < e.wt;
    }
};
int parent[N];
int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}
void unite(int x, int y) {
    x = find(x); y = find(y);
    if (x != y) parent[y] = x;
}
int kruskal(vector<Edge2>& edges, int n) {
    for (int i = 0; i < n; i++) parent[i] = i;
    sort(edges.begin(), edges.end());
    int cost = 0;
    for (auto e : edges) {
        if (find(e.u) != find(e.v)) {
            cost += e.wt;
            unite(e.u, e.v);
        }
    }
    return cost;
}

// ---------------------------
// DSU Template (Dynamic Connectivity)
// ---------------------------
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n); rank.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

// ---------------------------
// Tarjan's Algorithm (SCC / Bridges / Articulation Points)
// ---------------------------
int timer;
int tin[N], low[N];
bool isArticulation[N];
vector<pair<int,int>> bridges;

void tarjan(int node, int parent = -1) {
    visited[node] = true;
    tin[node] = low[node] = timer++;
    int children = 0;

    for (int to : adj[node]) {
        if (to == parent) continue;
        if (visited[to]) {
            low[node] = min(low[node], tin[to]);
        } else {
            tarjan(to, node);
            low[node] = min(low[node], low[to]);
            if (low[to] > tin[node]) {
                bridges.push_back({node, to}); // Bridge
            }
            if (low[to] >= tin[node] && parent != -1) {
                isArticulation[node] = true;
            }
            ++children;
        }
    }
    if (parent == -1 && children > 1) {
        isArticulation[node] = true;
    }
}

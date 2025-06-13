class Graph {
    int V;
    Node** adj;

    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };

public:
    Graph(int v) : V(v) {
        adj = new Node*[V];
        for (int i = 0; i < V; i++) adj[i] = nullptr;
    }

    void addEdge(int u, int v) {
        Node* newNode = new Node(v);
        newNode->next = adj[u];
        adj[u] = newNode;
    }

    void DFSUtil(int v, bool visited[]) {
        visited[v] = true;
        std::cout << v << " ";
        for (Node* p = adj[v]; p; p = p->next)
            if (!visited[p->data]) DFSUtil(p->data, visited);
    }

    void DFS(int start) {
        bool* visited = new bool[V]();
        DFSUtil(start, visited);
    }
};

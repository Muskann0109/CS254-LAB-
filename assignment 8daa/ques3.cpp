#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

using namespace std;

typedef tuple<int, int, int> Edge; // (weight, u, v)

class Graph {
private:
    int V;
    vector<vector<Edge>> adj;

    int findParent(int parent[], int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = findParent(parent, parent[x]);
    }

    void unionSet(int parent[], int rank[], int x, int y) {
        int xroot = findParent(parent, x);
        int yroot = findParent(parent, y);

        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(w, u, v);
        adj[v].emplace_back(w, v, u);
    }

    vector<Edge> kruskalMST() {
        vector<Edge> mst;
        vector<Edge> non_mst_edges;
        int parent[V];
        int rank[V];

        for (int i = 0; i < V; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        vector<Edge> edges;
        for (int u = 0; u < V; u++) {
            for (auto edge : adj[u])
                edges.push_back(edge);
        }

        sort(edges.begin(), edges.end());

        for (auto edge : edges) {
            int u = get<1>(edge);
            int v = get<2>(edge);
            int w = get<0>(edge);

            if (findParent(parent, u) != findParent(parent, v)) {
                mst.push_back(edge);
                unionSet(parent, rank, u, v);
            } else {
                non_mst_edges.push_back(edge);
            }
        }

        return mst;
    }

    vector<Edge> secondMST() {
        vector<Edge> mst = kruskalMST();
        vector<Edge> second_mst = mst;
        int parent[V];
        int rank[V];

        for (int i = 0; i < V; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        vector<Edge> non_mst_edges;
        for (auto edge : kruskalMST()) {
            int u = get<1>(edge);
            int v = get<2>(edge);
            if (findParent(parent, u) != findParent(parent, v)) {
                unionSet(parent, rank, u, v);
            } else {
                non_mst_edges.push_back(edge);
            }
        }

        sort(non_mst_edges.begin(), non_mst_edges.end());

        for (int i = 0; i < V; i++) {
            parent[i] = i;
            rank[i] = 0;
        }

        for (auto edge : non_mst_edges) {
            int u = get<1>(edge);
            int v = get<2>(edge);
            int w = get<0>(edge);

            if (findParent(parent, u) != findParent(parent, v)) {
                second_mst.push_back(edge);
                unionSet(parent, rank, u, v);
            }
        }

        return second_mst;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    vector<Edge> mst = g.kruskalMST();
    vector<Edge> second_mst = g.secondMST();

    cout << "Minimum Spanning Tree:\n";
    for (auto edge : mst)
        cout << "(" << get<1>(edge) << ", " << get<2>(edge) << "), weight: " << get<0>(edge) << "\n";

    cout << "\nSecond Best Minimum Spanning Tree:\n";
    for (auto edge : second_mst)
        cout << "(" << get<1>(edge) << ", " << get<2>(edge) << "), weight: " << get<0>(edge) << "\n";

    return 0;
}
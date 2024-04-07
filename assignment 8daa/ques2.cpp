#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, pair<int, int>> Edge; // {cost, {node1, node2}}
typedef pair<int, int> ColoredEdge; // {cost, color}

int findParent(vector<int>& parent, int x) {
    if (parent[x] == -1)
        return x;
    return parent[x] = findParent(parent, parent[x]);
}

void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
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

vector<ColoredEdge> alternatingMST(vector<vector<ColoredEdge>>& graph, int n) {
    vector<Edge> edges;
    for (int u = 0; u < n; u++) {
        for (auto edge : graph[u]) {
            edges.push_back({edge.first, {u, edge.second}});
        }
    }

    sort(edges.begin(), edges.end());

    vector<ColoredEdge> mst;
    vector<int> parent(n, -1);
    vector<int> rank(n, 0);

    int prevColor = -1;
    for (auto edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int cost = edge.first;
        int color = v;

        if (findParent(parent, u) != findParent(parent, v)) {
            if (prevColor == -1 || prevColor != color) {
                mst.push_back({cost, color});
                unionSet(parent, rank, u, v);
                prevColor = color;
            }
        }
    }

    return mst;
}

int main() {
    int n = 5;
    vector<vector<ColoredEdge>> graph(n);

    // Example graph
    graph[0].push_back({2, 1});
    graph[0].push_back({6, 0});
    graph[1].push_back({3, 0});
    graph[1].push_back({8, 1});
    graph[1].push_back({5, 0});
    graph[2].push_back({7, 1});
    graph[3].push_back({9, 0});

    vector<ColoredEdge> mst = alternatingMST(graph, n);

    cout << "Minimum Spanning Tree with Alternating Colored Edges:\n";
    for (auto edge : mst) {
        cout << "Cost: " << edge.first << ", Color: " << edge.second << "\n";
    }

    return 0;
}
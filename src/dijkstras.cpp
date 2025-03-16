#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous[source] = -1;
    priority_queue<pair<int, int>> minHeap;
    minHeap.push({source, 0});
    while(!minHeap.empty()) {
        int u = minHeap.extractVertexWithMinimumWeight().first;
        if visited[u] continue;
        visited[u] = true;
        for(Edge edge: graph[u]) {
            int v = edge.dest;
            int weight = edge.second;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}


vector<int> extract_shortest_path(const vector<int>& distance, const vector<int>& previous, int destination) {
    vector<int> path;

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    return path;
}


void print_path(const vector<int>& path, int total) {
    if (path.empty()) return;

    cout << "Shortest path: ";
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << "\nTotal distance: " << total << endl;
}

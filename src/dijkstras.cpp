#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    
    distance[source] = 0;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
    
        int u = current.vertex;

        if (visited[u]) {
            continue;
        }
        visited[u] = true;
    
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }

    return distance;
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

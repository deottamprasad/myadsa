#include <bits/stdc++.h> // T = O(V×ElogV), S = O(V2+E)
using namespace std;

void addVertex(vector< vector< pair<int, int> > > &adjList, int &newVertex) {
    int V = adjList.size();
    newVertex = V;  // Assign the new vertex ID as the current number of vertices
    adjList.push_back({});
    for (int u = 0; u < V; u++) {
        adjList[newVertex].push_back(make_pair(u, 0)); // Connect new vertex to all others with 0 weight
    }
}

bool bellmanFord(const vector< vector< pair<int, int> > > &adjList, int V, vector<int> &h) {
    h[V] = 0;  // New vertex (source) distance is 0
    for (int i = 0; i < V; i++) {  // Relax all edges V times
        for (int u = 0; u <= V; u++) {
            for (int j = 0; j < adjList[u].size(); j++) {
                int v = adjList[u][j].first;
                int w = adjList[u][j].second;
                if (h[u] != INT_MAX && h[u] + w < h[v]) {
                    h[v] = h[u] + w;
                }
            }
        }
    }
    // Check for negative-weight cycles
    for (int u = 0; u <= V; u++) {
        for (int j = 0; j < adjList[u].size(); j++) {
            int v = adjList[u][j].first;
            int w = adjList[u][j].second;
            if (h[u] != INT_MAX && h[u] + w < h[v]) {
                return true; // Negative cycle detected
            }
        }
    }
    return false;
}

void removeVertex(vector< vector< pair<int, int> > > &adjList, int newVertex) {
    adjList.pop_back();  // Remove the last vertex and its edges
}

void reweightEdges(vector< vector< pair<int, int> > > &adjList, const vector<int> &h) {
    for (int u = 0; u < adjList.size(); u++) {
        for (int j = 0; j < adjList[u].size(); j++) {
            int v = adjList[u][j].first;
            int w = adjList[u][j].second;
            adjList[u][j].second = w + h[u] - h[v]; // Adjust edge weight
        }
    }
}

void dijkstra(const vector< vector< pair<int, int> > > &adjList, int src, vector< vector<int> > &dist) {
    int V = adjList.size();
    vector<int> d(V, INT_MAX);
    d[src] = 0;
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u > d[u]) continue;

        for (int j = 0; j < adjList[u].size(); j++) {
            int v = adjList[u][j].first;
            int w = adjList[u][j].second;
            if (d[u] != INT_MAX && d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pq.push(make_pair(d[v], v));
            }
        }
    }
    for (int v = 0; v < V; v++) {
        dist[src][v] = d[v];
    }
}

void reweightDistances(vector< vector<int> > &dist, const vector<int> &h) {
    int V = dist.size();
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (dist[u][v] != INT_MAX) {
                dist[u][v] += h[v] - h[u];  // Reweight the distance back to original
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    vector< vector< pair<int, int> > > adjList(V);
    cout << "Enter the edges (u v w):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back(make_pair(v, w));
    }

    // Step 1: Add a new vertex connected to all vertices with zero-weight edges
    int newVertex = V;
    addVertex(adjList, newVertex);

    // Step 2: Run Bellman-Ford to detect negative cycles and find shortest paths from new vertex
    vector<int> h(V + 1, INT_MAX);  // h[i] will store the shortest distance from the new vertex
    bool isCycle = bellmanFord(adjList, V, h);
    if (isCycle) {
        cout << "The graph contains a negative cycle!" << endl;
        return 1;
    }

    // Step 3: Remove the extra vertex and reweight edges
    removeVertex(adjList, newVertex);
    reweightEdges(adjList, h);

    // Step 4: Use Dijkstra's algorithm for each vertex and adjust distances back to original weights
    vector< vector<int> > dist(V, vector<int>(V, INT_MAX));
    for (int u = 0; u < V; u++) {
        dijkstra(adjList, u, dist);
    }
    reweightDistances(dist, h);

    // Output the shortest distances
    cout << "The shortest distances between all pairs of vertices are:" << endl;
    for (int u = 0; u < V; u++) {
        cout << "Source " << u << " : ";
        for (int v = 0; v < V; v++) {
            if (dist[u][v] == INT_MAX) cout << "INF ";
            else cout << dist[u][v] << " ";
        }
        cout << endl;
    }

    return 0;
}

//5
//10
//0 1 6
//0 3 7
//1 2 5
//1 3 8
//1 4 -4
//2 1 -2
//3 2 -3
//3 4 9
//4 2 7
//4 0 2


#include<bits/stdc++.h> //T = O((V+E)logV) S = O(V+E)
using namespace std;

void dijkstra(vector<vector<pair<int,int> > > &adjList, int src, vector<int> &dist) {
	dist[src] = 0;
	int V = adjList.size();
	vector<bool> visited(V, false);
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push({0,src});
	while(!pq.empty()) {
		pair<int,int> curr = pq.top();
		pq.pop();
		int u = curr.second;
		if(visited[u])
			continue;
		visited[u] = true;
		for(int i=0;i<adjList[u].size();i++) {
			int v = adjList[u][i].first;
			int w = adjList[u][i].second;
			if(visited[v]==false) {
				if(dist[v]>dist[u]+w) {
					dist[v] = dist[u]+w;
					pq.push({dist[v],v});
				}
			}
		}
	}
}
int main() {
	int V=0, E=0;
	cout<<"Enter the no of vertices: ";
	cin>>V;
	cout<<"Enter the no of edges: ";
	cin>>E;
	cout<<"Enter the edges: "<<endl;
	vector<vector<pair<int,int> > > adjList(V);
	for(int i=0; i<E; i++) {
		int u,v, w;
		cin>>u>>v>>w;
		adjList[u].push_back({v,w});
	}
	vector<int> dist(V,INT_MAX);
	dijkstra(adjList, 0, dist);
	cout<<"The shortest distance from source 0 to all vertices is: ";
	for(int i=0;i<V;i++) {
		cout<<dist[i]<<" ";
	}
	return 0;
}

//5
//10
//0 1 10
//0 3 5
//1 2 1
//1 3 2
//2 4 4
//3 1 3
//3 4 2
//3 2 9
//4 0 7
//4 2 6

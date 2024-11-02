#include<bits/stdc++.h> //T = O(VE+E) S = O(V+E)
using namespace std;

bool bellmanFord(vector<vector<pair<int,int> > > &adjList, int src, vector<int> &dist) {
	dist[src] = 0;
	int V = adjList.size();
	for(int i=0;i<V-1;i++) {
		for(int u=0;u<V;u++) {
			for(int j=0;j<adjList[u].size();j++) {
				int v = adjList[u][j].first;
				int w = adjList[u][j].second;
				if(dist[v]>dist[u]+w) {
					dist[v] = dist[u]+w;
				}
			}
		}
	}
	for(int u=0;u<V;u++) {
		for(int j=0;j<adjList[u].size();j++) {
			int v = adjList[u][j].first;
			int w = adjList[u][j].second;
			if(dist[v]>dist[u]+w) {
				return false;
			}
		}
	}
	return true;
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
	bool noNegCycle = bellmanFord(adjList, 0, dist);
	if(!noNegCycle) {
		cout<<"There is a negative cycle in the graph!!!";
		return 1;
	}
	cout<<"The shortest distance from source 0 to all vertices is: ";
	for(int i=0;i<V;i++) {
		cout<<dist[i]<<" ";
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


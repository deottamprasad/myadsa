#include<bits/stdc++.h> //T = O(V+E) S = O(V+E)
using namespace std;

void dfs(vector<vector<int> > &adjList, vector<bool> &visited, int u, ofstream &outFile) {
	visited[u]=true;
	outFile<<u<<" ";
	for(int i=0;i<adjList[u].size();i++) {
		int v = adjList[u][i];
		if(visited[v]==false) {
			dfs(adjList, visited, v, outFile);
		}
	}
}
int main() {
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	if(!inFile.is_open()||!outFile.is_open()) {
		cerr<<"Could not open input or output file";
		return 1;
	}
	int V=0, E=0;
//	cout<<"Enter no of vertices in graph:";
	inFile>>V;
//	while(V<=0) {
//		cout<<"No vertices in graph!!! Try again";
//		cin>>V;
//	}
//	cout<<"Enter the no of edges in graph:";
	inFile>>E;
//	while(E<0) {
//		cout<<"Number of edges should be non-negative!!! Try again";
//		cin>>E;
//	}
	vector<vector<int> > adjList(V);
	vector<bool> visited(V,false);
//	cout<<"Enter each edge where 0<=u,v<"<<V<<":"<<endl;
	for(int i=0;i<E;i++) {
		int u,v;
		inFile>>u>>v;
//		if(u<0||u>=V||v<0||v>=V) {
//			cout<<"Invalid vertex Try again";
//			cin>>u>>v;
//		}
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	outFile<<"The dfs traversal of given graph is:";
	for(int i=0;i<V;i++) {
		if(visited[i]==false) {
			dfs(adjList, visited, i, outFile);
		}
	}
	inFile.close();
	outFile.close();
	return 0;
}

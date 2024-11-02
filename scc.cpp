#include<bits/stdc++.h> // T  = 3*O(V+E) S = O(V+E)
using namespace std;

void dfs1(vector<vector<int> > &adjList, vector<bool> &visited, stack<int> &st, int u) {
	visited[u] = true;
	for(int i=0;i<adjList[u].size();i++) {
		int v = adjList[u][i];
		if(visited[v]==false) {
			dfs1(adjList, visited, st, v);
		}
	}
	st.push(u);
}
void transpose(vector<vector<int> > &adjList, vector<vector<int> > &adjListT) {
	for(int u=0;u<adjList.size();u++) {
		for(int i=0;i<adjList[u].size();i++) {
			int v = adjList[u][i];
			adjListT[v].push_back(u);
		}
	}
}
void dfs2(vector<vector<int> > &adjListT, vector<bool> &visited, int u) {
	visited[u] = true;
	cout<<u<<" ";
	for(int i=0;i<adjListT[u].size();i++) {
		int v = adjListT[u][i];
		if(visited[v]==false) {
			dfs2(adjListT, visited, v);
		}
	}
}
int main() {
	int V = 0, E = 0;
	cout<<"Enter the no of vertices: ";
	cin>>V;
	//Handle V
	cout<<"Enter the no of edges: ";
	cin>>E;
	//Handle E
	vector<vector<int> > adjList(V);
	vector<bool> visited(V,false);
	cout<<"Enter the edges: "<<endl;
	for(int i=0;i<E;i++) {
		int u,v;
		cin>>u>>v;
		adjList[u].push_back(v);
	}
	stack<int> st;
	for(int i=0;i<V;i++) {
		if(visited[i]==false) {
			dfs1(adjList, visited, st, i);
		}
	}
	vector<vector<int> > adjListT(V);
	transpose(adjList, adjListT);
	for(int i=0;i<V;i++) {
		visited[i] = false;
	}
	cout<<"The strongly connected components are: "<<endl;
	while(!st.empty()) {
		int u = st.top();
		st.pop();
		if(visited[u]==false) {
			dfs2(adjListT, visited, u);
			cout<<endl;
		}
	}
	return 0;
}

//8
//12
//0 4
//1 0
//2 3
//3 2
//4 1
//5 1
//5 4
//5 6
//6 5
//6 2
//7 6
//7 3


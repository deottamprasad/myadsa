#include<bits/stdc++.h> //T = O(V+E) S = O(V+E)
using namespace std;

bool dfs(vector<vector<int> > &adjList, vector<bool> &recSt, vector<bool> &visited, int u, stack<int> &st) {
	visited[u]=true;
	recSt[u] = true;
	for(int i=0;i<adjList[u].size();i++) {
		int v = adjList[u][i];
		if(visited[v]==false) {
			dfs(adjList, recSt, visited, v, st);
		}
		else if(recSt[v]){
			cout<<"There is a cycle";
			return false;
		}
	}
	recSt[u]=false;
	st.push(u);
	return true;
}
int main() {
	int V = 0;
	int E = 0;
	cout<<"Enter the no of vertices:";
	cin>>V;
	//Handle V
	cout<<"Enter the no of edges:";
	cin>>E;
	//Handle E
	vector<vector<int> > adjList(V);
	cout<<"Enter the edges:"<<endl;
	for(int i=0;i<E;i++) {
		int u,v;
		cin>>u>>v;
		adjList[u].push_back(v);
	}
	vector<bool> visited(V,false);
	vector<bool> recSt(V,false);
	stack<int> st;
	bool flag = true;
	for(int i=0;i<V;i++) {
		if(visited[i]==false) {
			flag = dfs(adjList, recSt, visited, i, st);
		}
	}
	if(flag) {
		cout<<"The topological sort of above graph:";
		while(!st.empty()) {
			cout<<st.top()<<" ";
			st.pop();
		}
	}
	return 0;
}
//undershort = 0
//pants = 1
//belt = 2
//shirt = 3
//tie = 4
//jacket = 5
//shocks = 6
//shoes = 7
//watch = 8
//9
//9
//0 1
//0 7
//6 7
//1 7
//1 2
//3 2
//3 4
//2 5
//4 5

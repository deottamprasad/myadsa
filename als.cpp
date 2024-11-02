#include<bits/stdc++.h> //T = O(n), S = O(n)
using namespace std;

int assemblyLineScheduling(vector<vector<int> > &a, vector<vector<int> > &t, vector<int> &e, vector<int> &x) {
	int n = a[0].size();
	vector<vector<int> > T(2,vector<int>(n,0));
	T[0][0] = e[0]+a[0][0];
	T[1][0] = e[1]+a[1][0];
	for(int j=1;j<n;j++) {
		T[0][j] = min(T[0][j-1]+a[0][j], T[1][j-1]+t[1][j-1]+a[0][j]);
		T[1][j] = min(T[1][j-1]+a[1][j], T[0][j-1]+t[0][j-1]+a[1][j]);
	}
	int minTime = min(T[0][n-1]+x[0],T[1][n-1]+x[1]);
	return minTime;
}
int main() {
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	if(!inFile.is_open()||!outFile.is_open()) {
		cerr<<"Error opening input or output file"<<endl;
		return 1;
	}
	int n;
//	cout<<"Enter no of stations (n):";
	inFile>>n;
	vector<vector<int> > a(2,vector<int>(n,0)), t(2, vector<int>(n-1,0));
	vector<int> e(2,0), x(2,0);
//	cout<<"Enter entry times:";
	inFile>>e[0];
	inFile>>e[1];
//	cout<<"Enter exit times:";
	inFile>>x[0];
	inFile>>x[1];
//	cout<<"Enter acitivity time for each station in each line:";
	for(int i=0;i<2;i++) {
		for(int j=0;j<n;j++) {
			inFile>>a[i][j];
		}
	}
//	cout<<"Enter transfer time for each station in each line:";
	for(int i=0;i<2;i++) {
		for(int j=0;j<n-1;j++) {
			inFile>>t[i][j];
		}
	}
	int minTime = assemblyLineScheduling(a,t,e,x);
	outFile<<"The minimum time to process through the assembly lines is:"<<minTime;
	inFile.close();
	outFile.close();
}
//4
//10 12
//18 7
//4 5 3 2
//2 10 1 4
//7 4 5
//9 2 8
//
//35

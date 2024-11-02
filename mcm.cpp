#include<bits/stdc++.h> //T = O(n3) S = O(n2)
using namespace std;

int matrixChainMultiplication(vector<int> &p, vector<vector<int> > &s) {
	int n = p.size()-1;
	vector<vector<int> > dp(n,vector<int>(n,0));
	for(int l=2;l<=n;l++) {
		for(int i=0;i<n-l+1;i++) {
			int j = i+l-1;
			dp[i][j] = INT_MAX;
			for(int k=i;k<j;k++) {
				int cost = dp[i][k]+dp[k+1][j]+p[i]*p[k+1]*p[j+1];
				if(cost<dp[i][j]) {
					dp[i][j] = cost;
					s[i][j] = k;
				}
			}
		}
	}
	return dp[0][n-1];
}
void printOptimalParens(vector<vector<int> > &s, int i, int j) {
	if(i==j) {
		cout<<"A"<<i+1;
		return;
	}
	cout<<"(";
	printOptimalParens(s, i, s[i][j]);
	printOptimalParens(s, s[i][j]+1, j);
	cout<<")";
}
int main() {
	vector<int> dim;
	int n;
	cout<<"Enter the no of matrices (n):";
	cin>>n;
	cout<<"Enter the dimensions of matrices (n+1):";
	for(int i=0;i<n+1;i++) {
		int x;
		cin>>x;
		if(x<=0) {
			cout<<"Dimension should be positive!!! Try again";
			i--;
		}
		else
			dim.push_back(x);
	}
	vector<vector<int> > s(n,vector<int>(n,0));
	int minCost = matrixChainMultiplication(dim,s);
	cout<<"Minimum cost of matrix chain multiplication is:"<<minCost<<endl;
	cout<<"Optimal parenthesization:";
	printOptimalParens(s,0,n-1);
}

//Enter the number of matrices: 4
//Enter the dimensions: 10 20 30 40 30
//
//Minimum cost of matrix chain multiplication is: 30000
//Optimal Parenthesization: ((A1(A2A3))A4)


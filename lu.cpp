#include<bits/stdc++.h> //T=O(N3) S=O(N2)
using namespace std;

void luDecompose(vector<vector<double> > &A, vector<vector<double> > &L, vector<vector<double> > &U) {
	int n = A.size();
	for(int k=0;k<n;k++) {
		L[k][k] = 1;
		U[k][k] = A[k][k];
		for(int i=k+1;i<n;i++) {
			L[i][k] = A[i][k]/U[k][k];
			U[k][i] = A[k][i];
		}
		for(int i=k+1;i<n;i++) {
			for(int j=k+1;j<n;j++) {
				A[i][j] = A[i][j]-L[i][k]*U[k][j];
			}
		}
	}
}
void solve(vector<vector<double> > &L, vector<vector<double> > &U, vector<double> &b, vector<double> &x) {
	int n = L.size();
	//Ly = b
	vector<double> y(n,0);
	for(int i=0;i<n;i++) {
		double lySum = 0;
		for(int j=0;j<i-1;j++) {
			lySum += (L[i][j]*y[j]);
		}
		y[i] = b[i] - lySum;
	}
	//Ux = y
	for(int i=n-1;i>=0;i--) {
		double uxSum = 0;
		for(int j=i+1;j<n;j++) {
			uxSum += (U[i][j]*x[j]);
		}
		x[i] = (y[i]-uxSum)/U[i][i];
	}
}
int main() {
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	if(!inFile.is_open() || !outFile.is_open()) {
		cerr<<"Can't open input or output file";
		return 1;
	}
	int n;
//	cout<<"Enter the dimension of matrix: ";
	inFile>>n;
	vector<vector<double> > A(n,vector<double>(n, 0));
	vector<double> b(n,0);
//	cout<<"Enter the elements of matrix (A):"<<endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			inFile>>A[i][j];
		}
	}
//	cout<<"Enter the vector (b):";
	for(int i=0;i<n;i++) {
		inFile>>b[i];
	}
	vector<vector<double> > L(n, vector<double>(n,0)), U(n, vector<double>(n,0));
	luDecompose(A,L,U);
	outFile<<"Lower unit triangular matrix (L):"<<endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			outFile<<L[i][j]<<" ";
		}
		outFile<<endl;
	}
	outFile<<"Upper triangular matrix (U):"<<endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			outFile<<U[i][j]<<" ";
		}
		outFile<<endl;
	}
	vector<double> x(n, 0);
	solve(L,U,b,x);
	outFile<<"Solution vector (x):";
	for(int i=0;i<n;i++) {
		outFile<<x[i]<<" ";
	}
	inFile.close();
	outFile.close();
	return 0;
}

//2 3 1 5
//6 13 5 19
//2 19 10 23
//4 10 11 31

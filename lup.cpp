#include<bits/stdc++.h> //T = O(n3) S = O(n2)
using namespace std;

bool lupDecompose(vector<vector<double> > &A, vector<vector<double> > &L, vector<vector<double> > &U, vector<int> &p) {
	int n = A.size();
	for(int k=0;k<n;k++) {
		int pivot = 0, k1 = k;
		for(int i=k;i<n;i++) {
			if(pivot<abs(A[i][k])) {
				pivot = abs(A[i][k]);
				k1 = i;
			}
		}
		if(pivot==0) {
			return true;
		}
		if(k!=k1){
			swap(p[k],p[k1]);
			for(int i=0;i<n;i++) {
				swap(A[k][i],A[k1][i]);
			}
		}
		for(int i=k+1;i<n;i++) {
			A[i][k] /= A[k][k];
		}
		for(int i=k+1;i<n;i++) {
			for(int j=k+1;j<n;j++) {
				A[i][j] = A[i][j] - (A[i][k]*A[k][j]);
			}
		}
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			if(i==j) {
				L[i][i] = 1;
				U[i][i] = A[i][i];
			}
			else if(i>j) {
				L[i][j] = A[i][j];
			}
			else {
				U[i][j] = A[i][j];
			}
		}
	}
	return false;
}
void solve(vector<vector<double> > &L, vector<vector<double> > &U, vector<int> &p, vector<double> &b1, vector<double> &x) {
	int n = L.size();
	vector<double> b(n,0);
	for(int i=0;i<n;i++) {
		b[i] = b1[p[i]];
	}
	//Ly = pb
	vector<double> y(n,0);
	for(int i=0;i<n;i++) {
		double lySum = 0;
		for(int j=0;j<=i-1;j++) {
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
	int n;
	cout<<"Enter the dimension of matrix A:";
	cin>>n;
	vector<vector<double> > A(n,vector<double>(n,0)), L(n,vector<double>(n,0)), U(n,vector<double>(n,0));
	vector<double> b(n,0);
	cout<<"Enter the elements of matrix (A):"<<endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>A[i][j];
		}
	}
	cout<<"Enter the elements of vector (b):";
	for(int i=0;i<n;i++) {
		cin>>b[i];
	}
	vector<int> p(n,0);
	for(int i=0;i<n;i++) {
		p[i] = i;
	}
	bool singular = lupDecompose(A,L,U,p);
	if(singular) {
		cout<<"The matrix is singular!!!";
		return 1;
	}
	cout<<"Lower unit triangular matrix (L):"<<endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<L[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"Upper triangular matrix (U):"<<endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cout<<U[i][j]<<" ";
		}
		cout<<endl;
	}
	vector<double> x(n,0);
	solve(L,U,p,b,x);
	cout<<"Solution vector (x):";
	for(int i=0;i<n;i++) {
		cout<<x[i]<<" ";
	}
	return 0;
}
//2 0 2 0.6
//3 3 4 -2
//5 5 4 2
//-1 -2 3.4 -1

#include<bits/stdc++.h>   //T=O(nlogn) S=O(n)
using namespace std;
typedef complex<double> Complex;
const double pi = acos(-1);

void fft(vector<Complex> &x, bool invert) {
	int n = x.size();
	if(n<=1)
		return;
	vector<Complex> even(n/2),odd(n/2);
	for(int i=0;i<n/2;i++) {
		even[i] = x[2*i];
		odd[i] = x[2*i+1];
	}
	fft(even,invert);
	fft(odd,invert);
	double angle = 2*pi/n*(invert?-1:1);
	Complex w(1), wn(cos(angle),sin(angle));
	for(int k=0;k<n/2;k++) {
		Complex t = w*odd[k];
		x[k] = even[k]+t;
		x[k+n/2] = even[k]-t;
		if(invert) {
			x[k]/=2;
			x[k+n/2]/=2;
		}
		w *= wn;
	}
}
vector<double> multiplyPolynomials(vector<double> &a, vector<double> &b) {
	int n=1;
	while(n<a.size()+b.size()) n*=2;
	vector<Complex> fa(a.begin(),a.end()), fb(b.begin(),b.end());
	fa.resize(n);
	fb.resize(n);
	fft(fa,false);
	fft(fb,false);
	for(int i=0;i<n;i++) {
		fa[i] *= fb[i];
	}
	fft(fa,true);
	vector<double> res(n);
	for(int i=0;i<n;i++) {
		res[i] = round(fa[i].real());
	}
	return res;
}
int main() {
	int deg1, deg2;
	cout<<"Enter degree of first polynomial: ";
	cin>>deg1;
	vector<double> poly1(deg1+1);
	cout<<"Enter the coefficients of first polynomial from constant term to highest degree: ";
	for(int i=0;i<=deg1;i++) {
		cin>>poly1[i];
	}
	cout<<"Enter degree of second polynomial: ";
	cin>>deg2;
	vector<double> poly2(deg2+1);
	cout<<"Enter the coefficients of second polynomial from constant term to highest degree: ";
	for(int i=0;i<=deg2;i++) {
		cin>>poly2[i];
	}
	vector<double> res = multiplyPolynomials(poly1, poly2);
	cout<<"Resultant polynomial coefficients: ";
	for(int i=0;i<res.size();i++) {
		if(i==0||res[i]!=0) {
			cout<<res[i]<<" ";
		}
	}
	return 0;
}

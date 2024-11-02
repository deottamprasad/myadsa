#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream> // For file handling

using namespace std;

typedef complex<double> Complex;
const double PI = acos(-1);

void fft(vector<Complex>& x) {
    int N = x.size();
    if (N <= 1) return;

    vector<Complex> even(N / 2), odd(N / 2);
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    fft(even);
    fft(odd);

    for (int k = 0; k < N / 2; k++) {
        Complex t = polar(1.0, -2 * PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

vector<Complex> multiplyPolynomials(const vector<double>& a, const vector<double>& b) {
    int n = a.size() + b.size() - 1;
    int m = 1;
    while (m < n) m *= 2; 

    vector<Complex> fa(m), fb(m);
    for (size_t i = 0; i < a.size(); i++) fa[i] = a[i];
    for (size_t i = 0; i < b.size(); i++) fb[i] = b[i];

    fft(fa);
    fft(fb);

    vector<Complex> result(m);
    for (int i = 0; i < m; i++) {
        result[i] = fa[i] * fb[i];
        result[i] = round(result[i].real());
    }

    return result;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt" << endl;
        return 1; // Exit if the file cannot be opened
    }

    int degree1, degree2;
    inputFile >> degree1; // Read degree of the first polynomial
    vector<double> poly1(degree1 + 1);
    for (int i = 0; i <= degree1; i++) {
        inputFile >> poly1[i]; // Read coefficients of the first polynomial
    }

    inputFile >> degree2; // Read degree of the second polynomial
    vector<double> poly2(degree2 + 1);
    for (int i = 0; i <= degree2; i++) {
        inputFile >> poly2[i]; // Read coefficients of the second polynomial
    }

    inputFile.close(); // Close the file

    vector<Complex> result = multiplyPolynomials(poly1, poly2);

    cout << "Resultant polynomial: " << endl;
    for (const auto& coeff : result) {
        cout << coeff << " ";
    }
    cout << endl;

    return 0;
}


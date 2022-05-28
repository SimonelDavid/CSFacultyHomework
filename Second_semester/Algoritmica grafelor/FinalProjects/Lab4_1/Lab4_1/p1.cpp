#include<iostream>
#include<fstream>

using namespace std;

ifstream in("in.txt");
ofstream out("out.txt");

int n;
long long int p[100001];
long long int pruf[100001];

void citire() {
	in >> n;
	for (int i = 0; i < n; i++) {
		in >> p[i];
	}
}

long long int fmin(int n) {
	long long int frmin = 0;
	int i = 0;
	while (i < n) {
		if (frmin == p[i]) {
			frmin++;
			i = -1;
		}
		i++;
	}
	return frmin;
}

int main() {

	citire();

	for (int i = 0; i < n - 1; i++) {
		int fm = fmin(n);
		pruf[i] = p[fm];
		p[fm] = fm;
	}
	out << n - 1 << endl;
	for (int i = 0; i < n - 1; i++) {
		out << pruf[i] << " ";
	}
}
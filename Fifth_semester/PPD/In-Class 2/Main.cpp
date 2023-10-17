#include <iostream>
#include "Test0.h"
#include "Test0_mutex.h"
#include <thread>
#include <vector>
#include <functional>

using namespace std;

const int n = 20000000;
double* a = new double[n];
double* b = new double[n];
double* c = new double[n];
const int p = 5;
vector<double> a_vec(n);
vector<double> b_vec(n);
vector<double> c_vec(n);

void sum(double* aa, double* bb, double* cc, int start, int end, std::function<double(double, double)> operation) {
	for (int i = start; i < end; i++) {
		cc[i] = operation(aa[i], bb[i]);
	}
}

void sum_vec(vector<double> aa, vector<double> bb, vector<double> cc, int start, int end, std::function<double(double, double)> operation) {
	for (int i = start; i < end; i++) {
		cc[i] = operation(aa[i], bb[i]);
	}
}

void sum_paralel(double* aa, double* bb, double* cc, int p, int n, std::function<double(double, double)> operation) {
	thread* threads = new thread[p];
	int segmentSize = n / p;
	int rest = n % p;
	int start = 0;
	int end;

	for (int i = 0; i < p; i++) {
		end = start + segmentSize;
		if (rest > 0) {
			end++;
			rest--;
		}
		threads[i] = thread(sum, a, b, c, start, end, operation);
		start = end;
	}
	for (int i = 0; i < p; i++) {
		threads[i].join();
	}
}

void sum_paralel_vec(vector<double> aa, vector<double> bb, vector<double> cc, int p, int n, std::function<double(double, double)> operation) {
	thread* threads = new thread[p];
	int segmentSize = n / p;
	int rest = n % p;
	int start = 0;
	int end;

	for (int i = 0; i < p; i++) {
		end = start + segmentSize;
		if (rest > 0) {
			end++;
			rest--;
		}
		threads[i] = thread(sum, a, b, c, start, end, operation);
		start = end;
	}
	for (int i = 0; i < p; i++) {
		threads[i].join();
	}
}

void print_c(double* cc) {
	for (int i = 0; i < n; i++) {
		std::cout << c[i] << " ";
	}
	std::cout << "\n";
}

int main() {

	for (int i = 0; i < n; i++)
	{
		a[i] = i * 1.5;
		b[i] = i * 1.5;
	}
	auto t_start_s = chrono::steady_clock::now();

	sum(a, b, c, 0, n, [=](double xx, double yy) {return pow(xx, 3) + pow(yy, 3);});

	auto t_final_s = chrono::steady_clock::now();
	auto diff = t_final_s - t_start_s;
	cout << "[S/N] Computation time: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;

	auto t_start_p = chrono::steady_clock::now();

	sum_paralel(a, b, c, p, n, [=](double xx, double yy) {return pow(xx, 3) + pow(yy, 3);});

	auto t_final_p = chrono::steady_clock::now();
	auto diff2 = t_final_p - t_start_p;
	cout << "[P/N] Computation time: " << chrono::duration <double, milli>(diff2).count() << " ms" << endl;

	//print_c(c);


	auto t_start_sv = chrono::steady_clock::now();

	sum_vec(a_vec, b_vec, c_vec, 0, n, [=](double xx, double yy) {return pow(xx, 3) + pow(yy, 3); });

	auto t_final_sv = chrono::steady_clock::now();
	auto diff_v = t_final_sv - t_start_sv;
	cout << "[S/V] Computation time: " << chrono::duration <double, milli>(diff_v).count() << " ms" << endl;

	auto t_start_pv = chrono::steady_clock::now();

	sum_paralel_vec(a_vec, b_vec, c_vec, p, n, [=](double xx, double yy) {return pow(xx, 3) + pow(yy, 3); });

	auto t_final_pv = chrono::steady_clock::now();
	auto diff2_v = t_final_pv - t_start_pv;
	cout << "[P/V] Computation time: " << chrono::duration <double, milli>(diff2_v).count() << " ms" << endl;

	return 0;
}
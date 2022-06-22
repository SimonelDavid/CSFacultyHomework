#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#include <string>
using namespace std;

ifstream fin("1-in.txt");
ofstream fout("1-out.txt");

map<string, int> fr;
map<string, string> coduri;

string text, prim;

string min_char(string c) {
	char min = 'z';
	for (auto it : c)
		if (it < min) min = it;

	string ret = "";
	ret = ret + min;
	return ret;
}


struct comparator
{
	bool operator()(std::string x, std::string y)
	{
		if (fr[x] != fr[y])
			return fr[x] > fr[y];
		return min_char(x) > min_char(y);
	}
};

typedef struct parinte{
	string st, dr;
};

map<string, parinte> fii;
void parcurgere(std::string k, std::string nr) {
	if (k.length() == 1) coduri[k] = nr;
	nr = nr + '0';
	if (fii[k].st != "-1")
		parcurgere(fii[k].st, nr);
	nr.pop_back();
	nr = nr + '1';
	if (fii[k].dr != "-1")
		parcurgere(fii[k].dr, nr);
	nr.pop_back();
}
int main(int argc, char** argv) {
	priority_queue<string, vector<string>, comparator > pq;
	int cont = 0;

	getline(fin, text);
	for (auto c : text) {
		string it = "";
		it = it + c;
		if (fr[it] == 0) cont++;
		fr[it]++;//aici se realizeaza frecventa fiecarei litere
	}

	//afisam numarul de caractere codate
	fout << cont << '\n';

	//afisam caracterele si frecventa fiecarui caracter
	for (auto const& it : fr) {
		fout << it.first << " " << it.second << '\n';
		pq.push(it.first);
	}

	for (int i = 1; i < cont; i++) {
		//construim arborele
		string x = pq.top();
		pq.pop();
		string y = pq.top();
		pq.pop();
		int sum = fr[x] + fr[y];
		string n = x + y;
		fr[n] = sum;
		pq.push(n);

		if (x.length() == 1) {
			//nod frunza, nu are descendenti
			string snull = "-1";
			parinte fnull;
			fnull.st = snull;
			fnull.dr = snull;
			fii[x] = fnull;
		}

		if (y.length() == 1) {
			//nod frunza, nu are descendenti
			string snull = "-1";
			parinte fnull;
			fnull.st = snull;
			fnull.dr = snull;
			fii[y] = fnull;
		}

		prim = n;
		parinte desc;
		if (fr[x] != fr[y]) {
			desc.st = x;
			desc.dr = y;
		}
		else {
			string minx = min_char(x);
			string miny = min_char(y);

			if (minx < miny) {
				desc.st = x;
				desc.dr = y;
			}
			else {
				desc.st = y;
				desc.dr = x;
			}
		}
		fii[prim] = desc;

	}
	parcurgere(prim, ""); //pentru fiecare litera se determina codul

	//afisam codul
	for (auto c : text) {
		string it = "";
		it = it + c;
		fout << coduri[it];
	}
	return 0;
}
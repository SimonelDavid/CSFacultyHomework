#include <iostream>
#include <queue>
#include <limits.h>
#include <string.h>
#include <fstream>
#include <list>
#include <stack>
#include <vector>
#include <unordered_set>
using namespace std;

ifstream in("4-in.txt");
ofstream out("out.txt");
/*
int V, e, flow_maxim;
int graf[100][100];

void citire() {
	in >> V >> e;
	for (int i = 0; i < e; i++) {
		int a, b;
		in >> a >> b;
		in >> graf[a][b];
	}
}

bool bfs(int graf_rezidual[100][100], int s, int t, int parent[])
{
	bool vizitat[100];
	memset(vizitat, 0, sizeof(vizitat));

	queue<int> q;
	q.push(s);
	vizitat[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (vizitat[v] == false && graf_rezidual[u][v] > 0) {
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				vizitat[v] = true;
			}
		}
	}

	return false;
}

void fordFulk()
{
	int u, v;
	int s = 0;
	int t = V - 1;

	int graf_rezidual[100][100]; 
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			graf_rezidual[u][v] = graf[u][v];

	int parent[100];

	flow_maxim = 0; 

	while (bfs(graf_rezidual, s, t, parent)) {
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, graf_rezidual[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			graf_rezidual[u][v] -= path_flow;
			graf_rezidual[v][u] += path_flow;
		}

		flow_maxim += path_flow;
	}
}

int main()
{
	citire();
	fordFulk();
	out << flow_maxim;

	return 0;
}
*/

void pompare(int** graf, int** flux, int* exces, const int u, const int v)
{
    const int delta = std::min(exces[u], graf[u][v] - flux[u][v]);
    flux[u][v] += delta;
    flux[v][u] -= delta;
    exces[u] -= delta;
    exces[v] += delta;
}

void inalta(int** graf, int** flux, int* inaltime, const int u, const int noduri)
{
    int inaltimeMin = INT_MAX;
    for (int v = 0; v < noduri; ++v)
        if (graf[u][v] - flux[u][v] > 0) // capacitate reziduala
            inaltimeMin = std::min(inaltimeMin, inaltime[v]);

    inaltime[u] = inaltimeMin + 1;
}

void descarca(int** graf, int** flux, int* inaltime, int* exces, int* curent, const int u, const int noduri)
{
    while (exces[u] > 0)
    {
        if (curent[u] == noduri) // daca nu mai avem vecini in care sa pompam
        {
            inalta(graf, flux, inaltime, u, noduri); // inaltam nodul curent
            curent[u] = 0; // resetam faptul ca am vizitat vecinii deci putem sa-i revizitam
            continue;
        }

        const int v = curent[u];
        if (graf[u][v] - flux[u][v] > 0 && inaltime[u] == inaltime[v] + 1) // daca pot sa pompez
            pompare(graf, flux, exces, u, v); // atunci pompez
        else
            ++curent[u]; // continui cu urmatorul vecin
    }
}

int pompare_topologica(int** graf, int** flux, const int sursa, const int destinatie, const int noduri)
{
    std::list<int> L;
    L.clear();

    int* inaltime = new int[noduri] {};
    int* exces = new int[noduri] {};
    int* curent = new int[noduri] {};

    inaltime[sursa] = noduri;
    exces[sursa] = INT_MAX;
    for (int v = 0; v < noduri; ++v)
    {
        if (v != sursa)
            pompare(graf, flux, exces, sursa, v); // pompez din sursa cat de mult pot vecinilor

        if (v != sursa && v != destinatie)
            L.push_back(v); // L = V \ { s, t }
    }

    std::list<int>::iterator it = L.begin();
    while (it != L.end())
    {
        int u = *it;
        int inaltime_veche = inaltime[u];

        descarca(graf, flux, inaltime, exces, curent, u, noduri);

        if (inaltime[u] > inaltime_veche)
            L.splice(L.begin(), L, it); // mut elementul si iteratorul la inceput

        ++it; // continui cu urmatorul element
    }

    int fluxMaxim = exces[destinatie];

    delete[] curent;
    delete[] exces;
    delete[] inaltime;

    return fluxMaxim;
}

int main() {
    int noduri, arce;
    in >> noduri >> arce;
    int** graf = new int* [noduri] {};
    int** flux = new int* [noduri] {};
    for (int i = 0; i < noduri; ++i)
    {
        graf[i] = new int[noduri] {};
        flux[i] = new int[noduri] {};
    }
    for (int i = 0; i < arce; ++i)
    {
        int x, y, cost;
        in >> x >> y >> cost;
        graf[x][y] = cost;
    }

    out << pompare_topologica(graf, flux, 0, noduri - 1, noduri);

    for (int i = 0; i < noduri; ++i)
    {
        delete[] flux[i];
        delete[] graf[i];
    }
    delete[] flux;
    delete[] graf;
    in.close();
    out.close();

    return 0;

}
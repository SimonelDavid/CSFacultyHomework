#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <fstream>
using namespace std;

ifstream in("4-in.txt");
ofstream out("out.txt");

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

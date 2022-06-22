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
ifstream fin("in.txt");
ofstream fout("out.txt");


bool bfs(int** graf_rezidual, int sursa, int destinatie, int* parinte, int noduri) {
    bool* viz = new bool[noduri] {};

    queue<int> q;
    q.push(sursa);
    viz[sursa] = true;
    parinte[sursa] = -1;

    while (!q.empty() && !viz[destinatie]) {
        int nodCurent = q.front();
        q.pop();
        for (int i = 0; i < noduri && !viz[destinatie]; i++) {
            int cost = graf_rezidual[nodCurent][i];
            if (!viz[i] && cost > 0) {
                q.push(i);
                viz[i] = true;
                parinte[i] = nodCurent;
            }
        }
    }
    bool rez = viz[destinatie];
    delete[] viz;
    return rez;
    
}


int EdmondsKarp(int** graf_rezidual, int sursa, int destinatie, int noduri) {
    int fluxMax = 0;
    int* parinte = new int[noduri] {};
    while (bfs(graf_rezidual, sursa, destinatie, parinte, noduri)) {
        int capacitateMin = INT_MAX;
        for (int v = destinatie; v != sursa; v = parinte[v]) {
            int u = parinte[v];
            capacitateMin = std::min(capacitateMin, graf_rezidual[u][v]);
        }
        for (int v = destinatie; v != sursa; v = parinte[v]) {
            int u = parinte[v];
            graf_rezidual[u][v] -= capacitateMin;
            graf_rezidual[v][u] += capacitateMin;
        }
        fluxMax += capacitateMin;
    }
    delete[] parinte;
    return fluxMax;
}

int main() {
    int noduri, arce;
    fin >> noduri >> arce;
    int** graf_rezidual = new int* [noduri];
    for (int i = 0; i < noduri; i++) {
        graf_rezidual[i] = new int[noduri] {};
    }
    for (int i = 0; i < arce; i++) {
        int x, y, cost;
        fin >> x >> y >> cost;
        graf_rezidual[x][y] = cost;
    }
    fout << EdmondsKarp(graf_rezidual, 0, noduri - 1, noduri);
    for (int i = 0; i < noduri; i++) {
        delete[] graf_rezidual[i];
    }
    delete[] graf_rezidual;
    fin.close();
    fout.close();

    return 0;

}
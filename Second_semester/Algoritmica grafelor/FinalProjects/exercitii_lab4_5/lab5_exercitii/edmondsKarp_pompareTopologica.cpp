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


//////////////////////////////////////////////pb2 

ifstream fin2("in2.txt");
ofstream fout2("out2.txt");

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

////////////////////////////////////////////pb3
ifstream fin3("in3.txt");
ofstream fout3("out3.txt");
void hierholzer(std::unordered_set<int>* G, const int start, std::vector<int>& eulerCircuit)
{
    std::stack<int> path;
    path.push(start);

    while (!path.empty())
    {
        const int u = path.top();
        if (G[u].size()) // cat timp mai avem muchii care au pe u ca extremitate
        {
            const int v = *G[u].begin();

            //stergem muchia u - v din graf
            G[u].erase(G[u].begin());
            G[v].erase(u);

            //continuam cu vecinul lui u adica v
            path.push(v);
            continue;
        }

        path.pop();
        eulerCircuit.push_back(u);
    }

    eulerCircuit.pop_back();
    for (const auto& n : eulerCircuit)
        fout3 << n << ' ';
}

int main() {
    

    //pb1 Edmonds Karp
   /* int noduri, arce;
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
    fout.close();*/

    //p2 pompare topologica
    int noduri, arce;
    fin2 >> noduri >> arce;
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
        fin2 >> x >> y >> cost;
        graf[x][y] = cost;
    }

    fout2 << pompare_topologica(graf, flux, 0, noduri - 1, noduri);

    for (int i = 0; i < noduri; ++i)
    {
        delete[] flux[i];
        delete[] graf[i];
    }
    delete[] flux;
    delete[] graf;
    fin2.close();
    fout2.close();


    //pb 3 ciclu eulerian
    /*std::vector<int> eulerCircuit;

    int noduri, muchii;
    fin3 >> noduri >> muchii;
    std::unordered_set<int>* G = new std::unordered_set<int>[noduri];
    for (int i = 0; i < muchii; ++i)
    {
        int x, y;
        fin3 >> x >> y;
        G[x].insert(y);
        G[y].insert(x);
    }

    hierholzer(G, 0, eulerCircuit);

    delete[] G;
    fout3.close();
    fin3.close();*/

    return 0;

}



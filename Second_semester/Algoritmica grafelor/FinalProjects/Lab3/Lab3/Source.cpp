#include <fstream>
#include <climits>
#include <iostream>

int g[10000][10000];

int v, e, s;

struct Verteges {
    int d, pi;
}
verteges[10000];

void Initializare_s() {
    for (int i = 0; i < v; i++) {
        verteges[i].d = INT16_MAX;
        verteges[i].pi = -1;
    }
    verteges[s].d = 0;
}

void Relax(int u, int v) {
    if (verteges[v].d > verteges[u].d + g[u][v]) {
        verteges[v].d = verteges[u].d + g[u][v];
        verteges[v].pi = u;
    }
}

bool Bellman_Ford() {
    Initializare_s();
    for (int k = 0; k < v - 1; k++)
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                Relax(i, j);
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            if (verteges[j].d > verteges[i].d + g[i][j]) {
                return false;
            }
    return true;
}


int main(int argc, char* argv[]) {

    std::ifstream in("date_intrare.txt");
    std::ofstream out("date_iesire.txt");
    in >> v >> e >> s;
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            g[i][j] = INT16_MAX;
    for (int i = 0; i < e; i++) {
        int x, y, w;
        in >> x >> y >> w;
        g[x][y] = w;
    }

    if (Bellman_Ford()) {
        for (int i = 0; i < v; i++)
            if (verteges[i].d == INT16_MAX)
                out << "INF ";
            else
                out << verteges[i].d << " ";
    }
    return 0;
}
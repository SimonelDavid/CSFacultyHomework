#include <fstream>
#include <climits>
#include <iostream>

int g[10000][10000];

int varfuri, e, s;

struct Verteges {
    int d, pi;
}
verteges[10000];

void Initializare_s() {
    for (int i = 0; i < varfuri; i++) {
        verteges[i].d = INT16_MAX;
        verteges[i].pi = -1;
    }
    verteges[s].d = 0;
}

void Relax(int u, int varfuri) {
    if (verteges[varfuri].d > verteges[u].d + g[u][varfuri]) {
        verteges[varfuri].d = verteges[u].d + g[u][varfuri];
        verteges[varfuri].pi = u;
    }
}

bool Bellman_Ford() {
    Initializare_s();
    for (int k = 0; k < varfuri - 1; k++)
        for (int i = 0; i < varfuri; i++)
            for (int j = 0; j < varfuri; j++)
                Relax(i, j);
    for (int i = 0; i < varfuri; i++)
        for (int j = 0; j < varfuri; j++)
            if (verteges[j].d > verteges[i].d + g[i][j]) {
                return false;
            }
    return true;
}


int main(int argc, char* argv[]) {

    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    in >> varfuri >> e >> s;
    for (int i = 0; i < varfuri; i++)
        for (int j = 0; j < varfuri; j++)
            g[i][j] = INT16_MAX;
    for (int i = 0; i < e; i++) {
        int x, y, w;
        in >> x >> y >> w;
        g[x][y] = w;
    }

    if (Bellman_Ford()) {
        for (int i = 0; i < varfuri; i++)
            if (verteges[i].d == INT16_MAX)
                out << "INF ";
            else
                out << verteges[i].d << " ";
    }
    return 0;
}
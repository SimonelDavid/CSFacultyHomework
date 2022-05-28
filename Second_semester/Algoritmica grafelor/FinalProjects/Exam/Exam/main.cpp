#include <fstream>
#include <climits>
#include <iostream>

int g[10000][10000];

int vf, e, s;

struct Vert {
    int d, pi;
}
vert_[10000];

void init_bellman() {
    for (int i = 0; i < vf; i++) {
        vert_[i].d = INT16_MAX;
        vert_[i].pi = -1;
    }
    vert_[s].d = 0;
}

void Relax(int u, int vf) {
    if (vert_[vf].d > vert_[u].d + g[u][vf]) {
        vert_[vf].d = vert_[u].d + g[u][vf];
        vert_[vf].pi = u;
    }
}

bool Bellman_Ford() {
    init_bellman();
    for (int k = 0; k < vf - 1; k++)
        for (int i = 0; i < vf; i++)
            for (int j = 0; j < vf; j++)
                Relax(i, j);
    for (int i = 0; i < vf; i++)
        for (int j = 0; j < vf; j++)
            if (vert_[j].d > vert_[i].d + g[i][j]) {
                return false;
            }
    return true;
}


int main(int argc, char* argv[]) {

    std::ifstream in("in.txt");
    std::ofstream out("out.txt");
    in >> vf >> e >> s;
    for (int i = 0; i < vf; i++)
        for (int j = 0; j < vf; j++)
            g[i][j] = INT16_MAX;
    for (int i = 0; i < e; i++) {
        int x, y, w;
        in >> x >> y >> w;
        g[x][y] = w;
    }

    if (Bellman_Ford()) {
        for (int i = 0; i < vf; i++)
            if (vert_[i].d == INT16_MAX)
                out << "INF ";
            else
                out << vert_[i].d << " ";
    }
    return 0;
}
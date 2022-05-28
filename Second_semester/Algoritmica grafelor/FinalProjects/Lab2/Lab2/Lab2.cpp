#include<iostream>
#include<fstream>
using namespace std;
#define INF 10000

ifstream cit("source.txt");

int v[101][101];//incidenta
int g[101][101];
int d[101][101];
int p[101];
int n;

void citire() {
    cit >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cit >> a >> b;
        g[a][b] = 1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            v[i][j] = g[i][j];
}

void drum_minim(int u) {
    for (int i = 1; i <= n; i++) {
        if (i == u)
            d[u][i] = 0;
        else
            d[u][i] = INF;
    }
    int l = 1;
    int r = 1;
    int q[101];

    q[l] = u;
    while (l <= r) {
        int x = q[l];
        l++;
        for (int y = 1; y <= n; y++) {
            if (g[x][y]) {
                if (d[u][y] == INF) {
                    d[u][y] = d[u][x] + 1;
                    p[y] = x;
                    r++;
                    q[r] = y;
                }
            }
        }
    }
}

void afisare_drum(int st, int dr) {
    if (st == dr) {
        cout << st << " ";
        return;
    }
    afisare_drum(st, p[dr]);
    cout << dr << " ";
}

void mat_tranz()
{
    int k, i, j;
    for (k = 1; k <= n; ++k)
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= n; ++j)
                if (v[i][k] && v[k][j])
                    v[i][j] = 1;
}

void afisare() {
    cout << "matricea tranzitiva" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    citire();
    mat_tranz();
    afisare();

    int st, dr;
    cin >> st;
    cin >> dr;
    drum_minim(st);
    if (d[st][dr] != INF)
        afisare_drum(st, dr);
    else cout << "nu exista";

    return 0;
}
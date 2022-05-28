#include <iostream>
#include <fstream>
using namespace std;
///listă de muchii a unui graf neorientat la matricea de adiacență
///1.matrice de incidență

///II:
///vf izolate (grad 0)
///graf regular? acelasi grad pt toate varfurile
///matricea distantelor
/// conexitate


ifstream cit("vm.txt");

int g[101][101];
int inc[101][101];
int n, m;

int grad(int vf) {
    int gr = 0;
    for (int i = 1; i <= n; i++)
        if (g[vf][i] == 1)gr++;
    return gr;
}

int freq[101];

void parcurgere(int vf) {
    freq[vf] = 1;
    for (int i = 1; i <= n; i++) {
        if (g[vf][i] && !freq[i]) {
            parcurgere(i);
        }
    }
}

void izolate() {
    cout << "vf izolate:" << endl;
    for (int i = 1; i <= n; i++) {
        if (grad(i) == 0) {
            cout << i << " ";
        }
    }
}

int conex() {
    parcurgere(1);
    for (int i = 1; i <= n; i++)
        if (!freq[i])return 0;
    return 1;
}

int regulat() {
    int gr = grad(1);
    for (int i = 2; i <= n; i++)
        if (gr != grad(i))
            return 0;
    return 1;
}

void citire() {
    cit >> n;
    int a, b;
    while (cit >> a) {
        //constructie matrice de adiacență
        cit >> b;
        g[a][b] = 1;
        g[b][a] = 1;
        //constructie matrice de incidență
        m++;///nr de muchii
        inc[a][m] = 1;
        inc[b][m] = 1;
    }
    cit.close();
}

void afisare() {
//matricea de adiacenta:
    cout << "matricea de adiacenta" << endl;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }

//matricea de incidenta:
    cout << endl << "matricea de incidenta" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cout << inc[i][j] << " ";
        cout << endl;
    }
}

int d[101][101];

void roy() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            d[i][j] = g[i][j];
            if (!g[i][j] && i != j)
                d[i][j] = 100;
        }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][k] != 100 && d[k][j] != 100) {
                    if (d[i][j] > d[i][k] + d[k][j])
                        d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

void dist() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == 100)cout << "inf ";
            else
                cout << d[i][j] << "   ";
        }
        cout << endl;
    }
}

int main() {
    citire();
    afisare();
    izolate();
    if (regulat()) {
        cout << "\nregulat";
    }
    else {
        cout << "\nnu este regulat";
    }

    if (conex()) {
        cout << "\nconex" << endl;
    }
    else {
        cout << "\nnu conex" << endl;
    }

    roy();
    dist();
    return 0;
}

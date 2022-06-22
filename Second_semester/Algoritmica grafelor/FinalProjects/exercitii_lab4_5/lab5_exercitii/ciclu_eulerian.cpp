#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <tuple>

using namespace std;

ifstream f("Text.txt");

int n, m;

vector<vector<pair<int, bool>>>G;

void dfs(int x)
{
    for (auto& p : G[x])
        if(p.second)
        {
            p.second = 0;
            for (auto& k : G[p.first])
                if (k.first == x)
                    k.second = 0;
            dfs(p.first);
        }
    cout << x << ' ';
}

int main()
{
    f >> n >> m;
    G = vector<vector<pair<int, bool>>>(n + 1);
    int a, b;
    for (int i = 1; i <= m; ++i)
    {
        f >> a >> b;
        G[a].emplace_back(b, 1);
        G[b].emplace_back(a, 1);
    }
    dfs(0);

    return 0;
}
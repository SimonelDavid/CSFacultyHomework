#include <iostream>
using namespace std;
int main()
{
    int n,m,p,q,i,j,aux;
    int mat[30][30];
    cin>>n>>m;
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
            cin >> mat[i][j];
    cin >> p >> q;
    for(j=1; j<=n; j++){
        aux = mat[p][j];
        mat[p][j] = mat[q][j];
        mat[q][j] = aux;
    }
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
            cout << mat[i][j];
    return 0;
}
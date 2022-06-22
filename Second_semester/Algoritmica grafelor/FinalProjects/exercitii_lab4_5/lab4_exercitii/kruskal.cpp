//pentru arbore minim de acoperire
#include <iostream>
#include <fstream>
using namespace std;

struct Arch{
    int u, v, w;
}arches[1001];

int set[101], n, m;
int p[101]; ///parinti (arbore)
int k; //varfuri din arbore

void sort(){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i < m-1; i++){
            if(arches[i].w > arches[i+1].w){
                Arch aux = arches[i];
                arches[i] = arches[i+1];
                arches[i+1] = aux;
                sorted = false;
            }
        }
    }
}

Arch arbore[101];
int c;


void kruskal(){
    c = 0;
    k = 0;
    for(int i = 0; i < n; i++)
        set[i] = i;
    sort();
    for(int i = 0; i < m; i++){
        Arch arch = arches[i];
        if(set[arch.u] != set[arch.v]){
            c += arch.w;
            arbore[k] = arch;
            k++;
            int set_v = set[arch.v];
            for(int j = 0; j < n; j++){
                if(set[j] == set_v)set[j] = set[arch.u];
            }
        }
    }

}

void citire(){
    ifstream cit("date.in");
    cit>>n>>m;
    int a, b, cc;
    int i = 0;
    while(cit>>a>>b>>cc){
        arches[i].u = a;
        arches[i].v = b;
        arches[i].w = cc;
        i++;
    }
    cit.close();
}


int main() {
    citire();
    kruskal();
    cout<<c<<" "<<k<<endl;
    for(int i = 0; i < k; i++)
        cout<<arbore[i].u<<" "<<arbore[i].v<<" "<<endl;
    return 0;
}
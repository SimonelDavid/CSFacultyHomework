///JOHNSON
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

vector<int> min_length;
vector<int> bellman_dist;
vector<vector<int>> johnson_matrix;

auto cmp = [](int poz1, int poz2) { return min_length[poz1] > min_length[poz2]; };
priority_queue<int, vector<int>, decltype(cmp)> q(cmp);

void read_data(vector<vector<pair<int, int>>>& G, int& V, int& E) {
	fin >> V >> E;
	for (int i = 0; i < V; i++) {
		vector<pair<int, int>> line;
		G.push_back(line);
	}
	for (int i = 0; i < E; i++) {
		int x, y, w;
		fin >> x >> y >> w;
		G[x].push_back(make_pair(y, w));
	}
}

void print_data(vector<vector<pair<int, int>>> graph) {
	for (int i = 0; i < graph.size(); i++) {
		cout << i << ": ";
		for (int j = 0; j < graph[i].size(); j++) {
			cout << "(varfuri: " << graph[i][j].first << ", d: " << graph[i][j].second << ") ";
		}
		cout << endl;
	}
}

void dijkstra(vector<vector<pair<int, int>>> graph, int source) {
	min_length.clear();
	for (int i = 0; i < graph.size(); i++) {
		if (i == source) min_length.push_back(0);
		else min_length.push_back(INT_MAX / 2);
	}
	q.push(source);
	while (!q.empty()) {
		int i = q.top();
		q.pop();
		for (int j = 0; j < graph[i].size(); j++) {
			int u = i, varfuri = graph[i][j].first, w = graph[i][j].second;
			if (min_length[varfuri] > min_length[u] + w) {
				min_length[varfuri] = min_length[u] + w;
				q.push(varfuri);
			}
		}
	}
}

bool bellmanFord(vector<vector<pair<int, int>>> graph, int source) {
	for (int i = 0; i < graph.size(); i++) {
		if (i != source) bellman_dist.push_back(INT_MAX / 2);
		else bellman_dist.push_back(0);
	}

	for (int k = 1; k < graph.size(); k++) {
		//loop trough edges
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				int u = i, varfuri = graph[i][j].first;
				int w = graph[i][j].second;
				if (bellman_dist[varfuri] > bellman_dist[u] + w) {
					bellman_dist[varfuri] = bellman_dist[u] + w;
				}
			}
		}
	}
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			int u = i, varfuri = graph[i][j].first;
			int w = graph[i][j].second;
			if (bellman_dist[varfuri] > bellman_dist[u] + w) {
				return false;
			}
		}
	}

	return true;

}

void Johnson(vector<vector<pair<int, int>>>& graph) {
	//add new node
	int s = graph.size();
	vector<pair<int, int>> sLine;
	graph.push_back(sLine);
	for (int i = 0; i < s; i++) {
		graph[s].push_back(make_pair(i, 0));
	}
	if (bellmanFord(graph, s) == false) {
		cout << "Bellman failed!\n";
	}
	else {
		vector<int> h;
		for (int i = 0; i < graph.size(); i++) {
			h.push_back(bellman_dist[i]);
		}
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				int u = i, varfuri = graph[i][j].first;
				graph[i][j].second += (h[u] - h[varfuri]);
			}
		}
		for (int i = 0; i < s; i++) {
			vector<int> line;
			johnson_matrix.push_back(line);
			for (int j = 0; j < s; j++) {
				johnson_matrix[i].push_back(0);
			}
		}
		graph.pop_back();
		for (int i = 0; i < graph.size(); i++) {
			dijkstra(graph, i);
			for (int j = 0; j < graph.size(); j++) {
				johnson_matrix[i][j] = min_length[j] - h[i] + h[j];
			}
		}
	}
}

int main() {
	int V, E;
	vector<vector<pair<int, int>>> graph;
	read_data(graph, V, E);
	//print_data(graph);

	Johnson(graph);
	if (johnson_matrix.size() == 0) {
		fout << -1;
	}
	else {
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph[i].size(); j++) {
				fout << i << " " << graph[i][j].first << " " << graph[i][j].second << endl;
			}
		}
		for (int i = 0; i < johnson_matrix.size(); i++) {
			for (int j = 0; j < johnson_matrix[i].size(); j++) {
				if (johnson_matrix[i][j] > INT_MAX / 3) fout << "INF ";
				else fout << johnson_matrix[i][j] << " ";
			}
			fout << endl;
		}
	}
	return 0;
}






//MOORE


#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

#define INF 99999999

using namespace std;

int numar_noduri;
int matrice_ad[100][100];

void Moore(int graf[100][100], int sursa, vector<int>& lungime, vector<int>& parinti)
{
	queue<int> coada;
	lungime[sursa] = 0;
	for (int i = 1; i <= numar_noduri; i++)
		if (i != sursa)
			lungime[i] = INF;

	coada.push(sursa);
	while (!coada.empty())
	{
		sursa = coada.front();
		coada.pop();
		for (int i = 1; i <= numar_noduri; i++)
		{
			if (graf[sursa][i] == 1)
				if (lungime[i] == INF)
				{
					parinti[i] = sursa;
					lungime[i] = lungime[sursa] + 1;
					coada.push(i);
				}
		}
	}
}

void Moore_drum(int varfuri, vector<int> lungime, vector<int> parinti)
{
	int k = lungime[varfuri];
	cout << varfuri << " ";
	while (k != 0)
	{
		cout << parinti[varfuri] << " ";
		varfuri = parinti[varfuri];
		k--;
	}
}

int main()
{
	int sursa;
	ifstream fin("intrare.in");

	fin >> numar_noduri >> sursa;

	vector<int> distanta(numar_noduri + 1, 0);
	vector<int> parinte(numar_noduri + 1, 0);


	int nod1, nod2;
	while (fin >> nod1 >> nod2)
	{
		matrice_ad[nod1][nod2] = 1;
	}

	Moore(matrice_ad, sursa, distanta, parinte);
	for (int i = 1; i <= 12; i++)
		cout << distanta[i] << " ";
	Moore_drum(9, distanta, parinte);
	return 0;
}






///BELLMAN FORD


#include <fstream>
#define INF 1000000
using namespace std;

int graf[10000][10000], drum[10000], predecesori[10000], lista_muchii[10000];

ifstream fin("1-in.txt");
ofstream fout("1-out.txt");

void Bellman_Ford(int graf[][10000], int varfuri, int nod_sursa, int final)
{
	//initializare
	for (int i = 0; i < varfuri; i++)
	{
		if (i == nod_sursa)
			drum[i] = 0;
		else
			drum[i] = INF;
		predecesori[i] = NULL;
	}

	//procedura de relaxare
	for (int i = 1; i <= varfuri - 1; i++)
		for (int u = 0; u < varfuri; u++)
			for (int varfuri = 0; varfuri < varfuri; varfuri++)
				if (graf[u][varfuri] != INF && (drum[varfuri] > drum[u] + graf[u][varfuri]))
				{
					drum[varfuri] = drum[u] + graf[u][varfuri];
					predecesori[varfuri] = predecesori[u];
				}

}

int main(int argc, char* argv[])
{

	int varfuri, final, sursa;
	fin >> varfuri >> final >> sursa;

	//initializare
	for (int i = 0; i < varfuri; i++)
		for (int j = 0; j < varfuri; j++)
		{
			if (i == j)
				graf[i][j] = 0;
			else
				graf[i][j] = INF;
		}

	//incarcare valori in graf
	int nod1, nod2, cost;
	int k = 0;
	for (int i = 0; i < final; i++)
	{
		fin >> nod1 >> nod2 >> cost;
		graf[nod1][nod2] = cost;
		lista_muchii[k] = nod1;
		lista_muchii[k + 1] = nod2;
		k++;
	}

	Bellman_Ford(graf, varfuri, sursa, final);
	for (int i = 0; i < varfuri; i++)
		if (drum[i] == INF)
			fout << "INF" << " ";
		else
			fout << drum[i] << " ";

	fin.close();
	fout.close();
	return 0;
}






///BFS



void BFS(int sursa, int a[100][100], vector<int> vizitat, vector<int> distanta)
{

	queue<int> coada;
	int nivel = 0;
	vizitat[sursa] = 1;
	coada.push(sursa);
	while (!coada.empty())
	{
		nivel++;
		sursa = coada.front();
		coada.pop();
		cout << sursa << " -> " << distanta[sursa] << "\n";
		for (int j = 1; j <= n; j++)
		{
			if (a[sursa][j] == 1)
				if (!vizitat[j])
				{
					vizitat[j] = 1;
					distanta[j] += nivel;
					coada.push(j);
				}
		}
	}
}






///DFS


void DFS(int sursa, int a[100][100], vector<int>& vizitat)
{
	vizitat[sursa] = true;
	cout << sursa << " ";
	for (int i = 1; i <= n; i++)
	{
		if (a[sursa][i] == 1)
			if (!vizitat[i])
				DFS(i, a, vizitat);
	}
}






///DIJKSTRA


void Dijkstra(int graf[100][100], int sursa, vector<int>& lungime, vector<int>& vizitat)
{
	//initializez mai intai vectorul de lungimi
	for (int i = 1; i <= numar_noduri; i++)
	{
		lungime[i] = graf[sursa][i];
	}

	//vizitez sursa
	vizitat[sursa] = 1;

	//distanta la sursa e 0
	lungime[sursa] = 0;


	int minim;
	int pozitie;
	//parcurg fiecare nivel mai putin cel cu sursa
	for (int i = 1; i < numar_noduri; i++)
	{
		minim = INF; //initializez minimul cu cel mai mare numar posibil

		//parcurg fiecare nod
		for (int j = 1; j <= numar_noduri; j++)
		{
			//caut cea mai mica lungime dintre nodurile nevizitate, si o salvez
			if (!vizitat[j] && lungime[j] < minim)
			{
				pozitie = j;
				minim = lungime[j];
			}
		}

		//parcurg iar fiecare nod
		for (int j = 1; j <= numar_noduri; j++)
		{
			//daca gasesc un nod nevizitat
			if (!vizitat[i])
			{
				//verific daca distanta de la sursa la nodul i e mai mica prin nodul intermediar gasit mai sus
				if (lungime[i] > lungime[pozitie] + graf[pozitie][i])
					lungime[i] = lungime[pozitie] + graf[pozitie][i];
			}
		}
	}
}






///BELLMAN DIJKSTRA JOHNSON


#include <iostream>
#include <fstream>
using namespace std;

/*
 * coada cu priorități
 */
struct queue {
	int lft, rght;
	int q[101];
	/*
	 * adaugă varfuri în coadă
	 */
	void push(int varfuri) {
		rght++;
		q[rght] = varfuri;
	}
	/*
	 * Q -> varfuri a.î  d[varfuri] = min{d[u] | u \in Q}
	 */
	int pop(const int d[]) {
		int minn = lft;
		for (int i = 1; i <= rght; i++) {
			if (d[q[i]] < d[q[minn]])
				minn = i;
		}
		int varfuri = q[minn];
		for (int i = minn; i < rght; i++)
			q[i] = q[i + 1];
		rght--;
		return varfuri;
	}

	bool empty() const {
		return lft > rght;
	}
};

#define INF 10000;

/*
 * start -> vârful de start
 * d <-> vectorul de distante d[i] = i.d unde i e vârf
 * w <-> matricea ponderilor; w[u][varfuri] = (u, varfuri).w; (u, varfuri) muchie
 * n -> număr de vârfuri
 */
void dijkstra(int start, int d[], int w[1001][1001], int n) {
	queue q{};
	/*
	 * inițializare
	 */
	for (int i = 0; i < n; i++) {
		if (i != start) {
			d[i] = INF;
			q.push(i);
		}
	}
	d[start] = 0;
	q.push(start);
	while (!q.empty()) {
		int varfuri = q.pop(d);
		for (int i = 0; i < n; i++) {
			int alt = d[varfuri] + w[varfuri][i];
			if (alt < d[i])
				d[i] = alt;
		}
	}
}

/*
 * structura unei final
 */
struct arch {
	/*
	 * două vârfuri u și varfuri și o pondere w(u, varfuri)
	 */
	int u, varfuri, w;
};

/*
 * citirea grafului din fișier
 * w <- matricea de pondere w[u][varfuri] = w(u, varfuri)
 * e <- lista de final (struct arch)
 * n <- număr de vărfuri
 * m <- număr de final
 */
void read(int w[1001][1001], arch e[], int& n, int& m) {
	ifstream cit("date.in");
	cit >> n >> m;
	int a, b, c;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			w[i][j] = INF;
	int i = 1;
	while (cit >> a >> b >> c) {
		e[i].u = a;
		e[i].varfuri = b;
		e[i].w = c;
		w[a][b] = c;
		i++;
	}
	cit.close();
}

/*
 * funcția de inițializare Bellman-Ford
 * d <-> vectorul de distanță d[i] = i.d; i \in V
 * s -> vârful de start
 * n -> nr. de vârfuri din graf
 */
void init(int d[], int s, int n) {
	for (int i = 0; i < n; i++)
		d[i] = INF;
	d[s] = 0;
}

/*
 * funcția de relaxare Bellman-Ford
 * arc <-> arcul care se actualizează arc repr. (arc.u, arc.varfuri) și (u, varfuri).w = arc.w
 */
void relax(arch arc, int d[]) {
	if (d[arc.varfuri] > d[arc.u] + arc.w) {
		d[arc.varfuri] = d[arc.u] + arc.w;
	}
}

/*
 * e -> lista de arce
 * d <- vectorul de distante d[i] = i.d; i \in V
 * m -> nr de arce
 * s -> vărful de start
 * returnează fals dacă există circuite de cost negativ
 */
bool blmnfrd(arch e[], int d[], int n, int m, int s) {
	init(d, s, n);
	for (int i = 1; i < m; i++) {
		for (int j = 1; j <= m; j++) {
			relax(e[j], d);
		}
	}
	for (int j = 1; j <= m; j++) {
		if (d[e[j].varfuri] > d[e[j].u] + e[j].w)
			return false;
	}
	return true;
}

/*
 * w -> matricea de costuri
 * d -> un vector de distanțe
 * n -> nr de varfuri
 * m -> nr de arce
 * e -> listă de arce (dubla reprezentare a grafului, ca și w)
 * w_ <- matricea de reprezentare a drumurilor de cost minim w_[i][j] <- costul drumului de cost minim de la i la j
 */
bool jhon(int w[1001][1001], int d[], int n, int m, arch e[], int w_[1001][1001]) {
	int m_init = m;   //copie nr de arce inițiale
	/*
	 * se adaugă un vârf nou în graf (vârful n)
	 * se adaugă arcele (n, i) pt orice i din V ( i != n)
	 * (n, i).w = 0; i \in V \ {n}
	 */
	for (int i = 0; i < n; i++) {
		m++;
		e[m].u = n;
		e[m].varfuri = i;
		e[m].w = 0;
	}
	w[n][n] = INF;
	n++;
	/*
	 * {w cu n; e cu m} <- reprezentarea noului graf
	 * {w cu n-1; e cu m_init} <- reprezentarea grafului inițial
	 */

	 /*
	  * se apelează bellman-ford pentru noul graf
	  * se folosește reprezentarea cu listă de final
	  */
	if (!blmnfrd(e, d, n, m, n - 1))return false;
	/*
	 * reponderare
	 */
	for (int i = 1; i <= m; i++) {
		e[i].w = e[i].w + d[e[i].u] - d[e[i].varfuri];
		w[e[i].u][e[i].varfuri] = e[i].w;
	}
	/*
	 * afișare grafului inițial după reponderare
	 */
	for (int i = 1; i <= m_init; i++)
		cout << e[i].u << " " << e[i].varfuri << " " << e[i].w << endl;
	cout << endl;
	/*
	 * init w_ (output)
	 */
	int d_[1001];
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - 1; j++)
			w_[i][j] = INF;
	/*
	 * apel dijkstra din fiecare vârf al grafului inițial
	 * completare w_
	 */
	for (int i = 0; i < n - 1; i++) {
		dijkstra(i, d_, w, n - 1);
		for (int j = 0; j < n - 1; j++) {
			w_[i][j] = d_[j] + d[j] - d[i];
		}
	}
	return true;
}

/*
 * afisarea matricii de drumuri de cost minim
 */
void af_m(int w_[1001][1001], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (w_[i][j] > 1000) {
				cout << "INF ";
			}
			else {
				cout << w_[i][j] << " ";
			}
		}
		cout << endl;
	}
}

int main() {
	int w[1001][1001], d[1001], n, m;
	arch e[10001];
	read(w, e, n, m);
	int w_[1001][1001];
	if (jhon(w, d, n, m, e, w_)) {
		af_m(w_, n);
	}
	else cout << "-1";
	return 0;

}





/// LABORATOR 1


#include <iostream>
#include <fstream>
using namespace std;
///listă de final a unui graf neorientat la matricea de adiacență
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
		m++;///nr de final
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





/// LAB 3 BELLMAN FORD



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

	std::ifstream in("date_intrare.txt");
	std::ofstream out("date_iesire.txt");
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






///Kosaraju



// Kosaraju's algorithm to find strongly connected components in C++

#include <iostream>
#include <list>
#include <stack>

using namespace std;

class Graph {
	int V;
	list<int>* adj;
	void fillOrder(int s, bool visitedV[], stack<int>& Stack);
	void DFS(int s, bool visitedV[]);

public:
	Graph(int V);
	void addEdge(int s, int d);
	void printSCC();
	Graph transpose();
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

// DFS
void Graph::DFS(int s, bool visitedV[]) {
	visitedV[s] = true;
	cout << s << " ";

	list<int>::iterator i;
	for (i = adj[s].begin(); i != adj[s].end(); ++i)
		if (!visitedV[*i])
			DFS(*i, visitedV);
}

// Transpose
Graph Graph::transpose() {
	Graph g(V);
	for (int s = 0; s < V; s++) {
		list<int>::iterator i;
		for (i = adj[s].begin(); i != adj[s].end(); ++i) {
			g.adj[*i].push_back(s);
		}
	}
	return g;
}

// Add edge into the graph
void Graph::addEdge(int s, int d) {
	adj[s].push_back(d);
}

void Graph::fillOrder(int s, bool visitedV[], stack<int>& Stack) {
	visitedV[s] = true;

	list<int>::iterator i;
	for (i = adj[s].begin(); i != adj[s].end(); ++i)
		if (!visitedV[*i])
			fillOrder(*i, visitedV, Stack);

	Stack.push(s);
}

// Print strongly connected component
void Graph::printSCC() {
	stack<int> Stack;

	bool* visitedV = new bool[V];
	for (int i = 0; i < V; i++)
		visitedV[i] = false;

	for (int i = 0; i < V; i++)
		if (visitedV[i] == false)
			fillOrder(i, visitedV, Stack);

	Graph gr = transpose();

	for (int i = 0; i < V; i++)
		visitedV[i] = false;

	while (Stack.empty() == false) {
		int s = Stack.top();
		Stack.pop();

		if (visitedV[s] == false) {
			gr.DFS(s, visitedV);
			cout << endl;
		}
	}
}

int main() {
	Graph g(8);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 0);
	g.addEdge(4, 5);
	g.addEdge(5, 6);
	g.addEdge(6, 4);
	g.addEdge(6, 7);

	cout << "Strongly Connected Components:\n";
	g.printSCC();
}
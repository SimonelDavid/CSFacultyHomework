#include <iostream>
#include <queue>
#include <map>
#include <fstream>
using namespace std;

ifstream fin("1.in");
ifstream in("1.in");
ofstream fout("1.out");

struct Nod
{
    int caracter;
    int frecventa;
    int minChar;
    Nod* left, * right;
    Nod(int caracter, int frecventa, int minChar)
    {
        left = right = nullptr;
        this->caracter = caracter;
        this->frecventa = frecventa;
        this->minChar = minChar;
    }
};

struct compare
{
    bool operator()(Nod* left, Nod* right) {
        if (left->frecventa == right->frecventa) {
            return left->minChar > right->minChar;
        }
        return (left->frecventa > right->frecventa);
    }
};

priority_queue<Nod*, vector<Nod*>, compare> coada;
map<int, string> dictionar;
int n;

void aflareCod(struct Nod* root, string str)
{
    if (!root) return;
    if (root->caracter != '||')
        dictionar.insert(pair<int, string>(root->caracter, str));

    aflareCod(root->right, str + "1");
    aflareCod(root->left, str + "0");
}

void codareHuffman()
{
    struct Nod* stang, *drept, *top;
    int newFrecventa, newMinChar;
    for (int i = 1; i <= n - 1; i++)
    {
        stang = coada.top();
        coada.pop();
        drept = coada.top();
        coada.pop();
        newFrecventa = stang->frecventa + drept->frecventa;
        newMinChar = min(stang->minChar, drept->minChar);
        top = new Nod('||', newFrecventa, newMinChar);
        top->left = stang;
        top->right = drept;
        coada.push(top);
    }
    aflareCod(coada.top(), "");
}

void citire()
{
	int caractere[128] = { 0 }, cuvinte = 0;
    char c;
	string text;
	while (fin >> text)
    {
        if (cuvinte > 0) caractere[' ']++;
		for (size_t i = 0; i < text.size(); i++)
			caractere[text[i]]++;
        cuvinte++;
	}
	for (int i = 0; i < 128; i++)
		if (caractere[i] > 0)
		{
            coada.push(new Nod(i, caractere[i], i));
            n++;
		}
    fout << n << endl;
    for (int i = 0; i < 128; i++)
        if (caractere[i] != 0)
            fout << char(i) << " " << caractere[i] << endl;
}

void afisare()
{
    string text;
    int key, cuvinte = 0;
    while (in >> text)
    {
        if (cuvinte > 0) fout << dictionar[' '];
        for (int i = 0; i < text.size(); i++)
        {
            key = text[i];
            fout << dictionar[key];
        }
        cuvinte++;
    }
}

void dealocare(Nod* nod)
{
    if (nod == nullptr) return;
    dealocare(nod->left);
    dealocare(nod->right);
    delete nod;
}

int main()
{
    citire();
    codareHuffman();
    afisare();
    dealocare(coada.top());
    return 0;
}
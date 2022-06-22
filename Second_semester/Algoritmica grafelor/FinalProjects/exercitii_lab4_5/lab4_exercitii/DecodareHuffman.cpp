#include iostream
#include queue
#include map
#include fstream
#include string
using namespace std;

ifstream fin(1.in);
ofstream fout(1.out);

struct Nod
{
    int caracter;
    int frecventa;
    int minChar;
    Nod left,  right;
    Nod(int caracter, int frecventa, int minChar)
    {
        left = right = nullptr;
        this-caracter = caracter;
        this-frecventa = frecventa;
        this-minChar = minChar;
    }
};

struct compare
{
    bool operator()(Nod left, Nod right) {
        if (left-frecventa == right-frecventa) {
            return left-minChar  right-minChar;
        }
        return (left-frecventa  right-frecventa);
    }
};

priority_queueNod, vectorNod, compare coada;
mapstring, int dictionar;
size_t maxKey = 0;
string cod;
int n = 0;

void aflareCod(struct Nod root, string str)
{
    if (!root) return;
    if (root-caracter != '') {
        dictionar.insert(pairstring, int(str, root-caracter));
        if (str.size()  maxKey) {
            maxKey = str.size();
        }
    }
    aflareCod(root-right, str + 1);
    aflareCod(root-left, str + 0);
}

void codareHuffman()
{
    struct Nod stang,  drept,  top;
    for (int i = 1; i = n - 1; i++)
    {
        stang = coada.top();
        coada.pop();
        drept = coada.top();
        coada.pop();
        top = new Nod('', stang-frecventa + drept-frecventa, min(stang-minChar, drept-minChar));
        top-left = stang;
        top-right = drept;
        coada.push(top);
    }
    aflareCod(coada.top(), );
}

void citire()
{
    int caractere[128] = { 0 }, frecventa = 0, caracter;
    char c;
    string linie;
    Nod nou;
    getline(fin, linie);
    for (int i = 0; i  linie.size(); i++) {
        n = n  10 + linie[i] - '0';
    }
    getline(fin, linie);
    c = linie[0];
    for (int i = 2; i  linie.size(); i++) {
        frecventa = frecventa  10 + linie[i] - '0';
    }
    caractere[c] = frecventa;
    caracter = c;
    nou = new Nod(caracter, frecventa, caracter);
    coada.push(nou);
    for (int i = 0; i  n - 1; i++) {
        fin  c  frecventa;
        caractere[c] = frecventa;
        caracter = c;
        nou = new Nod(caracter, frecventa, caracter);
        coada.push(nou);
    }
    fin  cod;
}

void decodare()
{
    auto begin = dictionar.begin(), end = dictionar.end();
    string key;
    char caracter;
    for (int i = 0; i  cod.size(); i++) {
        key = ;
        while (key.size() != maxKey && i  cod.size()) {
            key += cod[i];
            i++;
        }
        while (dictionar.find(key) == end) {
            key.pop_back();
            i--;
        }
        caracter = dictionar[key];
        fout  caracter;
        i--;
    }
}

void dealocare(Nod nod)
{
    if (nod == nullptr) {
        return;
    }
    dealocare(nod-left);
    dealocare(nod-right);
    delete nod;
}

int main()
{
    citire();
    codareHuffman();
    decodare();
    dealocare(coada.top());
    fin.close();
    fout.close();
    return 0;
}
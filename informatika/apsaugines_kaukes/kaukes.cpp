// Apsauginės kaukės
#include <bits/stdc++.h>
using namespace std;

const int CMax = 100;  // daugiausiai vaistinių

struct Vaistine {
    string pavadinimas;
    int kiekis;     // kaukių kiekis
    double kaina;   // vienos kaukės kaina
};

void Skaityti(Vaistine V[], int &n);
int Viso(Vaistine V[], int n);
double Suma(Vaistine V[], int n);
int Daugiausia(Vaistine V[], int n);
int Maziausia(Vaistine V[], int n);
void Rasyti(Vaistine V[], int n, int viso, double suma, int maxInd, int minInd);

int main()
{
    Vaistine V[CMax];
    int n;  // vaistinių skaičius

    Skaityti(V, n);
    int viso = Viso(V, n);
    double suma = Suma(V, n);
    int maxInd = Daugiausia(V, n);
    int minInd = Maziausia(V, n);
    Rasyti(V, n, viso, suma, maxInd, minInd);
    return 0;
}

// Nuskaito pradinius duomenis iš failo
void Skaityti(Vaistine V[], int &n)
{
    ifstream fd("vaistines.txt");
    fd >> n;
    for (int i = 0; i < n; i++)
        fd >> V[i].pavadinimas >> V[i].kiekis >> V[i].kaina;
    fd.close();
}

// Kiek iš viso kaukių yra rajone
int Viso(Vaistine V[], int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += V[i].kiekis;
    return s;
}

// Bendra visų kaukių kaina: kiekis * vieneto kaina
double Suma(Vaistine V[], int n)
{
    double s = 0;
    for (int i = 0; i < n; i++)
        s += V[i].kiekis * V[i].kaina;
    return s;
}

// Vaistinės, turinčios daugiausia kaukių, indeksas
int Daugiausia(Vaistine V[], int n)
{
    int ind = 0;
    for (int i = 1; i < n; i++)
        if (V[i].kiekis > V[ind].kiekis)
            ind = i;
    return ind;
}

// Vaistinės, turinčios mažiausia kaukių, indeksas
int Maziausia(Vaistine V[], int n)
{
    int ind = 0;
    for (int i = 1; i < n; i++)
        if (V[i].kiekis < V[ind].kiekis)
            ind = i;
    return ind;
}

// Įrašo rezultatus į failą
void Rasyti(Vaistine V[], int n, int viso, double suma, int maxInd, int minInd)
{
    ofstream fr("apskaita.txt");
    for (int i = 0; i < n; i++)
        fr << V[i].pavadinimas << " " << V[i].kiekis << " " << V[i].kaina << endl;
    fr << "Viso apsauginių kaukių rajone yra :" << viso << endl;
    fr << "Bendra suma :" << suma << endl;
    fr << "Daugiausia kaukių turi parduotuvė :" << V[maxInd].pavadinimas << endl;
    fr << "Mažiausia kaukių turi parduotuvė :" << V[minInd].pavadinimas << endl;
    fr.close();
}

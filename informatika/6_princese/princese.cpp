// 6. Įnoringiausia princesė
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int CMax = 50;  // daugiausiai princų

struct Princas {
    string vardas;  // vardas (iki 24 simbolių)
    int pedos;      // ūgis pėdomis
    int coliai;     // ir coliais
    int ugis;       // visas ūgis coliais (1 pėda = 12 colių)
};

void Skaityti(Princas P[], int &n);
int Rasti(Princas P[], int n);
void Rasyti(Princas P[], int ind);

int main()
{
    Princas P[CMax];
    int n;  // princų skaičius

    Skaityti(P, n);
    int ind = Rasti(P, n);
    Rasyti(P, ind);
    return 0;
}

// Nuskaito pradinius duomenis iš failo
void Skaityti(Princas P[], int &n)
{
    ifstream fd("princai-duom.txt");
    fd >> n;
    fd.ignore(256, '\n');

    for (int i = 0; i < n; i++) {
        char eilute[100];
        fd.getline(eilute, 100);   // skaitoma visa eilutė

        istringstream ss(eilute);
        ss >> P[i].vardas >> P[i].pedos >> P[i].coliai;

        P[i].ugis = P[i].pedos * 12 + P[i].coliai;
    }

    fd.close();
}

// Randa aukščiausią, bet ne patį aukščiausią princą.
// Grąžina jo indeksą arba -1, jei tokio nėra.
int Rasti(Princas P[], int n)
{
    // aukščiausias ūgis
    int maks = P[0].ugis;
    for (int i = 1; i < n; i++)
        if (P[i].ugis > maks)
            maks = P[i].ugis;

    // aukščiausias iš žemesnių už patį aukščiausią
    int ind = -1;
    for (int i = 0; i < n; i++)
        if (P[i].ugis < maks && (ind == -1 || P[i].ugis > P[ind].ugis))
            ind = i;
    return ind;
}

// Įrašo rezultatą į failą
void Rasyti(Princas P[], int ind)
{
    ofstream fr("princai-rez.txt");
    if (ind == -1)
        fr << 0 << endl;
    else
        fr << P[ind].vardas << endl;
    fr.close();
}

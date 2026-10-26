// Padangos
#include <bits/stdc++.h>
using namespace std;

const int CMax = 100;  // daugiausiai padangų sąraše

struct Padanga {
    int plotis;     // padangos plotis
    int aukstis;    // profilio aukštis
    string tipas;   // tipas, pvz. HR13
    double kaina;   // kaina eurais
};

void Skaityti(Padanga &T, Padanga P[], int &n);
void Skaiciuoti(Padanga T, Padanga P[], int n, int &k, double &suma);
void Rasyti(int k, double suma);

int main()
{
    Padanga T;        // tinkama padanga
    Padanga P[CMax];  // padangų sąrašas
    int n;            // padangų kiekis sąraše
    int k;            // tinkamų padangų skaičius
    double suma;      // kiek kainuotų tinkamos padangos

    Skaityti(T, P, n);
    Skaiciuoti(T, P, n, k, suma);
    Rasyti(k, suma);
    return 0;
}

// Nuskaito tinkamos padangos duomenis ir padangų sąrašą
void Skaityti(Padanga &T, Padanga P[], int &n)
{
    ifstream fd("Duomenys1.txt");
    fd >> T.plotis >> T.aukstis >> T.tipas;
    fd >> n;
    for (int i = 0; i < n; i++)
        fd >> P[i].plotis >> P[i].aukstis >> P[i].tipas >> P[i].kaina;
    fd.close();
}

// Suskaičiuoja, kiek sąrašo padangų tinka ir kiek jos kainuotų
void Skaiciuoti(Padanga T, Padanga P[], int n, int &k, double &suma)
{
    k = 0;
    suma = 0;
    for (int i = 0; i < n; i++)
        if (P[i].plotis == T.plotis && P[i].aukstis == T.aukstis && P[i].tipas == T.tipas) {
            k++;
            suma += P[i].kaina;
        }
}

// Įrašo rezultatus į failą
void Rasyti(int k, double suma)
{
    ofstream fr("Rezultatai1.txt");
    fr << "Tinkamų padangų skaičius: " << k << endl;
    fr << "Jos kainuotų: " << fixed << setprecision(2) << suma << " eurų" << endl;
    fr.close();
}

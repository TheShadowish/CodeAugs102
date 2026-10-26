// Užduotys 1: Padangos, Mokiniai, Apsauginės kaukės
#include <bits/stdc++.h>
using namespace std;

const int CMax = 100;  // daugiausiai įrašų faile
const int CPaz = 5;    // kiek pažymių turi kiekvienas mokinys

// ==================== 1. Padangos ====================

struct Padanga {
    int plotis;     // padangos plotis
    int aukstis;    // profilio aukštis
    string tipas;   // tipas, pvz. HR13
    double kaina;   // kaina eurais
};

// Nuskaito tinkamos padangos duomenis ir padangų sąrašą
void SkaitytiPadangas(Padanga &T, Padanga P[], int &n)
{
    ifstream fd("Duomenys1.txt");
    fd >> T.plotis >> T.aukstis >> T.tipas;
    fd >> n;
    for (int i = 0; i < n; i++)
        fd >> P[i].plotis >> P[i].aukstis >> P[i].tipas >> P[i].kaina;
    fd.close();
}

// Suskaičiuoja, kiek sąrašo padangų tinka ir kiek jos kainuotų
void SkaiciuotiPadangas(Padanga T, Padanga P[], int n, int &k, double &suma)
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
void RasytiPadangas(int k, double suma)
{
    ofstream fr("Rezultatai1.txt");
    fr << "Tinkamų padangų skaičius: " << k << endl;
    fr << "Jos kainuotų: " << fixed << setprecision(2) << suma << " eurų" << endl;
    fr.close();
}

void Padangos()
{
    Padanga T;        // tinkama padanga
    Padanga P[CMax];  // padangų sąrašas
    int n;            // padangų kiekis sąraše
    int k;            // tinkamų padangų skaičius
    double suma;      // kiek kainuotų tinkamos padangos

    SkaitytiPadangas(T, P, n);
    SkaiciuotiPadangas(T, P, n, k, suma);
    RasytiPadangas(k, suma);
}

// ==================== 2. Mokiniai ====================

struct Mokinys {
    string pavarde;
    string vardas;
    string klase;
    int paz[CPaz];     // gauti pažymiai
    double vidurkis;   // pažymių vidurkis
};

// Nuskaito pradinius duomenis iš failo
void SkaitytiMokinius(Mokinys M[], int &n)
{
    ifstream fd("Duomenys2.txt");
    fd >> n;
    for (int i = 0; i < n; i++) {
        fd >> M[i].pavarde >> M[i].vardas >> M[i].klase;
        for (int j = 0; j < CPaz; j++)
            fd >> M[i].paz[j];
    }
    fd.close();
}

// Apskaičiuoja kiekvieno mokinio vidurkį ir grąžina geriausio mokinio indeksą
int SkaiciuotiMokinius(Mokinys M[], int n)
{
    for (int i = 0; i < n; i++) {
        double suma = 0;
        for (int j = 0; j < CPaz; j++)
            suma += M[i].paz[j];
        M[i].vidurkis = suma / CPaz;
    }

    int ind = 0;
    for (int i = 1; i < n; i++)
        if (M[i].vidurkis > M[ind].vidurkis)
            ind = i;
    return ind;
}

// Įrašo geriausią mokinį į failą
void RasytiMokinius(Mokinys M[], int ind)
{
    ofstream fr("Rezultatai2.txt");
    fr << M[ind].pavarde << " " << M[ind].vardas << " " << M[ind].klase << " "
       << fixed << setprecision(1) << M[ind].vidurkis << endl;
    fr.close();
}

void Mokiniai()
{
    Mokinys M[CMax];
    int n;  // mokinių skaičius

    SkaitytiMokinius(M, n);
    int ind = SkaiciuotiMokinius(M, n);
    RasytiMokinius(M, ind);
}

// ==================== 3. Apsauginės kaukės ====================

struct Vaistine {
    string pavadinimas;
    int kiekis;     // kaukių kiekis
    double kaina;   // vienos kaukės kaina
};

// Nuskaito pradinius duomenis iš failo
void SkaitytiVaistines(Vaistine V[], int &n)
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
void RasytiVaistines(Vaistine V[], int n, int viso, double suma, int maxInd, int minInd)
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

void Kaukes()
{
    Vaistine V[CMax];
    int n;  // vaistinių skaičius

    SkaitytiVaistines(V, n);
    int viso = Viso(V, n);
    double suma = Suma(V, n);
    int maxInd = Daugiausia(V, n);
    int minInd = Maziausia(V, n);
    RasytiVaistines(V, n, viso, suma, maxInd, minInd);
}

// ==================== main ====================

int main()
{
    Padangos();  // Duomenys1.txt -> Rezultatai1.txt
    Mokiniai();  // Duomenys2.txt -> Rezultatai2.txt
    Kaukes();    // vaistines.txt -> apskaita.txt
    return 0;
}

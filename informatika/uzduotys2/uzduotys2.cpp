// Užduotys 2: Padangos, Mokiniai, Apsauginės kaukės
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

struct Dydis {
    int plotis;
    int aukstis;
    string tipas;
    int kiekis;     // kiek tokio dydžio padangų yra sąraše
};

// Nuskaito padangų sąrašą
void SkaitytiPadangas(Padanga P[], int &n)
{
    ifstream fd("Duomenys1.txt");
    fd >> n;
    for (int i = 0; i < n; i++)
        fd >> P[i].plotis >> P[i].aukstis >> P[i].tipas >> P[i].kaina;
    fd.close();
}

// Suskaičiuoja, kiek kokio dydžio padangų yra sąraše.
// D - skirtingi dydžiai, k - kiek skirtingų dydžių rasta.
void SkaiciuotiPadangas(Padanga P[], int n, Dydis D[], int &k)
{
    k = 0;
    for (int i = 0; i < n; i++) {
        int vieta = -1;  // kur masyve D jau yra toks dydis
        for (int j = 0; j < k; j++)
            if (D[j].plotis == P[i].plotis && D[j].aukstis == P[i].aukstis && D[j].tipas == P[i].tipas)
                vieta = j;

        if (vieta == -1) {  // tokio dydžio dar nebuvo - pridedame naują
            D[k].plotis = P[i].plotis;
            D[k].aukstis = P[i].aukstis;
            D[k].tipas = P[i].tipas;
            D[k].kiekis = 1;
            k++;
        }
        else                // toks dydis jau yra - padidiname kiekį
            D[vieta].kiekis++;
    }
}

// Įrašo rezultatus į failą
void RasytiPadangas(Dydis D[], int k)
{
    ofstream fr("Rezultatai1.txt");
    for (int i = 0; i < k; i++)
        fr << D[i].plotis << "  " << D[i].aukstis << "  " << D[i].tipas << "   " << D[i].kiekis << endl;
    fr.close();
}

void Padangos()
{
    Padanga P[CMax];  // padangų sąrašas
    Dydis D[CMax];    // skirtingi padangų dydžiai
    int n;            // padangų kiekis sąraše
    int k;            // skirtingų dydžių skaičius

    SkaitytiPadangas(P, n);
    SkaiciuotiPadangas(P, n, D, k);
    RasytiPadangas(D, k);
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

// Apskaičiuoja kiekvieno mokinio vidurkį ir grąžina mokinio su mažiausiu vidurkiu indeksą
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
        if (M[i].vidurkis < M[ind].vidurkis)
            ind = i;
    return ind;
}

// Įrašo mokinį su mažiausiu vidurkiu į failą
void RasytiMokinius(Mokinys M[], int ind)
{
    ofstream fr("Rezultatai2.txt");
    fr << M[ind].pavarde << " " << M[ind].vardas << " " << M[ind].klase << "  "
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

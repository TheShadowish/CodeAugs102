// Mokiniai
#include <bits/stdc++.h>
using namespace std;

const int CMax = 100;  // daugiausiai mokinių
const int CPaz = 5;    // kiek pažymių turi kiekvienas mokinys

struct Mokinys {
    string pavarde;
    string vardas;
    string klase;
    int paz[CPaz];     // gauti pažymiai
    double vidurkis;   // pažymių vidurkis
};

void Skaityti(Mokinys M[], int &n);
int Skaiciuoti(Mokinys M[], int n);
void Rasyti(Mokinys M[], int ind);

int main()
{
    Mokinys M[CMax];
    int n;  // mokinių skaičius

    Skaityti(M, n);
    int ind = Skaiciuoti(M, n);
    Rasyti(M, ind);
    return 0;
}

// Nuskaito pradinius duomenis iš failo
void Skaityti(Mokinys M[], int &n)
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
int Skaiciuoti(Mokinys M[], int n)
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
void Rasyti(Mokinys M[], int ind)
{
    ofstream fr("Rezultatai2.txt");
    fr << M[ind].pavarde << " " << M[ind].vardas << " " << M[ind].klase << " "
       << fixed << setprecision(1) << M[ind].vidurkis << endl;
    fr.close();
}

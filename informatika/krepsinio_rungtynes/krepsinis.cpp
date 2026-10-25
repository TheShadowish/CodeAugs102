// Krepšinio rungtynės
#include <bits/stdc++.h>
using namespace std;

const int CMax = 100;  // daugiausiai žaidėjų

struct Zaidejas {
    string vardas;
    string pavarde;
    int taskai;        // pelnyti taškai
    int perdavimai;    // rezultatyvūs perdavimai
    int atkovoti;      // atkovoti kamuoliai
    int naudingumas;   // naudingumo balai
};

void Skaityti(Zaidejas Z[], int &n);
void Atrinkti(Zaidejas Z[], int n, Zaidejas A[], int &k);
void Rikiuoti(Zaidejas A[], int k);
int Naudingiausias(Zaidejas Z[], int n);
void Rasyti(Zaidejas A[], int k, Zaidejas Z[], int ind);

int main()
{
    Zaidejas Z[CMax];  // visi žaidėjai
    Zaidejas A[CMax];  // pelnę ne mažiau nei 30 taškų
    int n, k;

    Skaityti(Z, n);
    Atrinkti(Z, n, A, k);
    Rikiuoti(A, k);
    int ind = Naudingiausias(Z, n);
    Rasyti(A, k, Z, ind);
    return 0;
}

// Nuskaito pradinius duomenis iš failo ir apskaičiuoja naudingumą
void Skaityti(Zaidejas Z[], int &n)
{
    ifstream fd("duomenys.txt");
    fd >> n;
    for (int i = 0; i < n; i++) {
        fd >> Z[i].vardas >> Z[i].pavarde
           >> Z[i].taskai >> Z[i].perdavimai >> Z[i].atkovoti;
        // taškas - 1 balas, perdavimas - 2 balai, atkovotas kamuolys - 1 balas
        Z[i].naudingumas = Z[i].taskai + 2 * Z[i].perdavimai + Z[i].atkovoti;
    }
    fd.close();
}

// Atrenka žaidėjus, pelniusius ne mažiau nei 30 taškų
void Atrinkti(Zaidejas Z[], int n, Zaidejas A[], int &k)
{
    k = 0;
    for (int i = 0; i < n; i++)
        if (Z[i].taskai >= 30) {
            A[k] = Z[i];
            k++;
        }
}

// Surikiuoja žaidėjus mažėjimo tvarka pagal taškus
void Rikiuoti(Zaidejas A[], int k)
{
    for (int i = 0; i < k - 1; i++)
        for (int j = i + 1; j < k; j++)
            if (A[j].taskai > A[i].taskai) {
                Zaidejas t = A[i];
                A[i] = A[j];
                A[j] = t;
            }
}

// Grąžina naudingiausio žaidėjo indeksą
int Naudingiausias(Zaidejas Z[], int n)
{
    int ind = 0;
    for (int i = 1; i < n; i++)
        if (Z[i].naudingumas > Z[ind].naudingumas)
            ind = i;
    return ind;
}

// Įrašo rezultatus į failą
void Rasyti(Zaidejas A[], int k, Zaidejas Z[], int ind)
{
    ofstream fr("rezultatai.txt");
    fr << "Žaidėjai, pelnę ne mažiau nei 30 taškų:" << endl;
    if (k == 0)
        fr << "Tokių žaidėjų nėra" << endl;
    for (int i = 0; i < k; i++)
        fr << A[i].vardas << " " << A[i].pavarde << " " << A[i].taskai << endl;
    fr << endl;
    fr << "Naudingiausias žaidėjas:" << endl;
    fr << Z[ind].vardas << " " << Z[ind].pavarde << " " << Z[ind].naudingumas << endl;
    fr.close();
}

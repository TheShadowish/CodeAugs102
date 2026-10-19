// 1. Stebėti orai
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int CMax = 31;  // daugiausiai dienų mėnesyje

struct Diena {
    string oras;  // koks buvo oras (19 simbolių)
    int diena;    // mėnesio diena
    int temp;     // tos dienos temperatūra
};

void Skaityti(Diena D[], int &n);
double Vidurkis(Diena D[], int n);
int Aukstesnes(Diena D[], int n, double vid);
void Rasyti(Diena D[], int n, double vid, int k);

int main()
{
    Diena D[CMax];
    int n;  // stebėtų dienų skaičius

    Skaityti(D, n);
    double vid = Vidurkis(D, n);
    int k = Aukstesnes(D, n, vid);
    Rasyti(D, n, vid, k);
    return 0;
}

// Nuskaito pradinius duomenis iš failo
void Skaityti(Diena D[], int &n)
{
    ifstream fd("Duome1.txt");
    char oras[20];
    fd >> n;
    fd.ignore(256, '\n');
    for (int i = 0; i < n; i++) {
        fd.get(oras, 20);  // nuskaitomi 19 oro aprašymo simbolių
        D[i].oras = oras;
        D[i].oras.erase(D[i].oras.find_last_not_of(' ') + 1);  // pašalinami tarpai gale
        fd >> D[i].diena >> D[i].temp;
        fd.ignore(256, '\n');
    }
    fd.close();
}

// Apskaičiuoja stebėtų dienų vidutinę temperatūrą
double Vidurkis(Diena D[], int n)
{
    double suma = 0;
    for (int i = 0; i < n; i++)
        suma += D[i].temp;
    return suma / n;
}

// Suskaičiuoja, kiek dienų temperatūra buvo aukštesnė už vidutinę
int Aukstesnes(Diena D[], int n, double vid)
{
    int k = 0;
    for (int i = 0; i < n; i++)
        if (D[i].temp > vid)
            k++;
    return k;
}

// Įrašo rezultatus į failą
void Rasyti(Diena D[], int n, double vid, int k)
{
    ofstream fr("Rezul1.txt");
    fr << "Vidutinė temperatūra: " << fixed << setprecision(1) << vid << endl;
    fr << endl;
    fr << "Dienų, kuomet oro temperatūra aukštesnė už vidutinę, yra " << k << ":" << endl;
    fr << endl;
    fr << "Lyginių dienų duomenys:" << endl;
    for (int i = 0; i < n; i++)
        if (D[i].diena % 2 == 0)
            fr << left << setw(20) << D[i].oras << D[i].temp << endl;
    fr.close();
}

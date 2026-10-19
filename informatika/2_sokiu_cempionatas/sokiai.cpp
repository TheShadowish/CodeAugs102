// 2. Šokių čempionatas
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int CMax = 100;  // daugiausiai porų

struct Pora {
    string vardai;  // šokėjų vardai (21 simbolis)
    string klubas;  // šokių klubo pavadinimas
    int balai[3];   // trijų teisėjų vertinimai
    int suma;       // surinkti balai
};

void Skaityti(Pora P[], int &n);
double Vidurkis(Pora P[], int n);
int Laimetojas(Pora P[], int n);
void Rasyti(Pora P[], int n, double vid, int ind);

int main()
{
    Pora P[CMax];
    int n;  // porų skaičius

    Skaityti(P, n);
    double vid = Vidurkis(P, n);
    int ind = Laimetojas(P, n);
    Rasyti(P, n, vid, ind);
    return 0;
}

// Nuskaito pradinius duomenis iš failo ir suskaičiuoja kiekvienos poros balus
void Skaityti(Pora P[], int &n)
{
    ifstream fd("Duomen2.txt");
    char vardai[22];
    fd >> n;
    fd.ignore(256, '\n');
    for (int i = 0; i < n; i++) {
        fd.get(vardai, 22);  // nuskaitomi 21 vardų simbolis
        P[i].vardai = vardai;
        P[i].vardai.erase(P[i].vardai.find_last_not_of(' ') + 1);  // pašalinami tarpai gale
        fd >> P[i].klubas;
        P[i].suma = 0;
        for (int j = 0; j < 3; j++) {
            fd >> P[i].balai[j];
            P[i].suma += P[i].balai[j];
        }
        fd.ignore(256, '\n');
    }
    fd.close();
}

// Apskaičiuoja visų porų taškų vidurkį
double Vidurkis(Pora P[], int n)
{
    double suma = 0;
    for (int i = 0; i < n; i++)
        suma += P[i].suma;
    return suma / n;
}

// Grąžina daugiausiai balų surinkusios poros indeksą
int Laimetojas(Pora P[], int n)
{
    int ind = 0;
    for (int i = 1; i < n; i++)
        if (P[i].suma > P[ind].suma)
            ind = i;
    return ind;
}

// Įrašo rezultatus į failą
void Rasyti(Pora P[], int n, double vid, int ind)
{
    ofstream fr("Rezult2.txt");
    for (int i = 0; i < n; i++)
        fr << left << setw(21) << P[i].vardai << P[i].suma << endl;
    fr << endl;
    fr << "Taškų vidurkis: " << fixed << setprecision(1) << vid << endl;
    fr << endl;
    fr << "Šokių čempionatą laimėjo:" << endl;
    fr << left << setw(21) << P[ind].vardai << P[ind].suma << endl;
    fr.close();
}

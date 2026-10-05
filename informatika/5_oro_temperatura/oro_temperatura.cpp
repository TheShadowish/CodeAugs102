// 5. Oro temperatūros matavimai
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int CMax = 12;   // daugiausiai mėnesių
const int CMat = 100;  // daugiausiai matavimų per mėnesį

struct Menuo {
    string pavadinimas;    // mėnesio pavadinimas
    double temp[CMat];     // temperatūros matavimai
    double vidurkis;       // mėnesio vidutinė temperatūra
};

void Skaityti(Menuo M[], int &n, int &m);
void Skaiciuoti(Menuo M[], int n, int m, double &bendras);
void Rasyti(Menuo M[], int n, double bendras);

int main()
{
    Menuo M[CMax];
    int n, m;          // mėnesių skaičius, matavimų skaičius
    double bendras;    // bendras visų matavimų vidurkis

    Skaityti(M, n, m);
    Skaiciuoti(M, n, m, bendras);
    Rasyti(M, n, bendras);
    return 0;
}

// Nuskaito pradinius duomenis iš failo
void Skaityti(Menuo M[], int &n, int &m)
{
    ifstream fd("Duomenys.txt");
    fd >> n >> m;
    for (int i = 0; i < n; i++) {
        fd >> M[i].pavadinimas;
        for (int j = 0; j < m; j++)
            fd >> M[i].temp[j];
    }
    fd.close();
}

// Apskaičiuoja kiekvieno mėnesio ir bendrą vidurkį
void Skaiciuoti(Menuo M[], int n, int m, double &bendras)
{
    double visuSuma = 0;
    for (int i = 0; i < n; i++) {
        double suma = 0;
        for (int j = 0; j < m; j++)
            suma += M[i].temp[j];
        M[i].vidurkis = suma / m;
        visuSuma += suma;
    }
    bendras = visuSuma / (n * m);
}

// Įrašo rezultatus į failą
void Rasyti(Menuo M[], int n, double bendras)
{
    ofstream fr("Rezultatai.txt");
    fr << fixed << setprecision(2);
    for (int i = 0; i < n; i++)
        fr << M[i].pavadinimas << " " << M[i].vidurkis << endl;
    fr << "Bendras matavimų vidurkis: " << bendras << endl;
    fr.close();
}

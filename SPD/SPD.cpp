#include <iostream>             //potrzebne biblioteki
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
using namespace std;
char in[] = "opt.txt";          //dokument z czasami

struct dane{            //struktura danych
    int Zadanie;
    int Maszyna;
    int a;
};

bool sortnr(const dane &dane_1, const dane &dane_2){
    return (dane_1.Zadanie < dane_2.Zadanie);
}

struct dataJonhson{             //struktura danych johnson
    int nZad;   
    int b1;
    int b2;
    bool operator<(dataJonhson zad) const {
        return min(b1, b2) < min(zad.b1, zad.b2);
    } 
};

vector<dataJonhson> algorytmJonhsona(vector<dataJonhson> zad);
int cmaxJonh(vector<dataJonhson> zad);
int cemax(vector<vector<dane>> zadanie);

vector<dataJonhson> algorytmJonhsona(vector<dataJonhson> zad) { //algorytm johnsona
    sort(zad.begin(), zad.end());                               //poczatek i koniec
    vector<dataJonhson> left, right;
    for (int j = 0; j < zad.size(); j++) {                      //dla kazdego j mniejszego od liczby zadan
        if (zad[j].b1 < zad[j].b2)
            left.push_back(zad[j]);
        else
            right.push_back(zad[j]);
    }
    left.insert(left.end(), right.rbegin(), right.rend());
    return left;
}

int cmaxJonh(vector<dataJonhson> zad) {     //cmax dla Johnsona
    int t1 = 0, t2 = 0;
    for (int j = 0; j < zad.size(); j++) {      //petrla j<liczba zadan
        t1 += zad[j].b1;
        t2 = max(t2, t1) + zad[j].b2;
    }   
    return max(t1, t2);
}

int cemax(vector<vector<dane>> zadania) {       //algorytm przegladu zupelnego
    int tmp_start = 0;
    int tmp_koniec = 0;
    int l_maszyn = zadania.size(); 
    int l_zad = zadania[0].size(); 
    int Cmax = 0;

    vector<vector<int>> v_start(l_maszyn, vector<int>(l_zad, 0));       //v vectorow dla start
    vector<vector<int>> v_koniec(l_maszyn, vector<int>(l_zad, 0));      //v vectorow dla koniec

    for (int i = 0; i < l_maszyn; i++) {
        for (int j = 0; j < l_zad; j++) {
            if (i == 0) {                           
                tmp_start = tmp_koniec;
                tmp_koniec = tmp_start + zadania[i][j].a;
            }
            else {                          
                if (j == 0) {
                    tmp_start = v_koniec[i - 1][j];                
                }
                else {
                    tmp_start = max(v_koniec[i - 1][j], v_koniec[i][j - 1]);  
                }
                tmp_koniec = tmp_start + zadania[i][j].a;
            }
            v_start[i][j] = tmp_start;
            v_koniec[i][j] = tmp_koniec;
        }
    }
    Cmax = v_koniec[l_maszyn - 1][l_zad - 1];
    return Cmax;
}

int main(){
fstream plik;               //strumien czytajacy
int lzadan, lmaszyn;        //zmienne   pomocnicze
plik.open(in, ios::in);        //wczytanie 
    if (plik.good() == true) {  //jesli dobry
    plik >> lzadan >> lmaszyn;  //przypisanie

    /*
    //cz1
    vector<vector<dane>> zadania(lzadan, vector<dane>(lzadan));
    for (int i = 0; i < lzadan; i++) {
        for (int j = 0; j < lmaszyn; j++) {
            zadania[j][i].Zadanie= i;
            plik >> zadania[j][i].Maszyna >> zadania[j][i].a;
        }
    }
    auto start = chrono::high_resolution_clock::now();      //start czasu
    cout << cemax(zadania) << endl;                         //dzialanie algorytmu
    auto end = chrono::high_resolution_clock::now();    //koniec czasu
    auto delta = chrono::duration_cast<chrono::microseconds>(end - start).count();  //obliczenie czasu
    cout << "Czas sortowania wyniosl: " << delta << "us" << endl;   //wypisanie na ekran czasu
    */
    //cz2 -algorytm johnsona

    /*
    vector<dataJonhson> zad(lzadan);        
    vector<dataJonhson> zrobione(lzadan);
    for (int j = 0; j < lzadan; j++)
    {
        zad[j].nZad = j;
        zad[j].b1 = zadania[0][j].a;
        zad[j].b2 = zadania[1][j].a;
    }
    zrobione = algorytmJonhsona(zad);
    for (int i = 0; i < lzadan; i++) {
        if (i == 0)
            cout << "NR " << "P1 " << "P2" << endl;
        cout << zrobione[i].nZad << "  "
            << zrobione[i].b1 << "  "
            << zrobione[i].b2 << " "
            << endl;
    }
    cout << "cmax = " << cmaxJonh(zrobione) << endl;
    */
    }
plik.close();
return 0;
}
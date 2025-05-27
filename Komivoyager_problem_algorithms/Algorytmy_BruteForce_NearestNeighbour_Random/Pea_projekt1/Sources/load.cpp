//
// Created by mateu on 09.10.2024.
//
#include "load.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int cities_number;                                      // zmienna przechowująca ilość miast

int** generate_loaded_matrix() {
    int** matrix = nullptr;
    ifstream file;
    string name;

    cout << "Podaj nazwe pliku, z ktorego chcesz wczytac tablice: ";
    cin >> name;
    file.open((name + ".txt").c_str());			            // otwieranie pliku o podanej nazwie

    if(file.good()==false) {					                // jeśli plik się nie otworzył
        cout << "Plik nie istnieje" << endl;
    } else {
        string line;
        int line_number = 1;

        while(getline(file, line)) {
            if(line_number == 1) {
                stringstream ss;				                // stringstream to typ danych, który pozwala na łatwe konwertowanie danych np. z string na int
                ss << line;
                ss >> cities_number;

                ss.clear();						                // czyszczenie ss
                // cout << cities_number << endl;
                matrix = new int*[cities_number];               // tworzenie dwuelementowej dynamicznej tablicy, która będzie przechowywała dane wczytanej instancji
                for(int i=0; i<cities_number; i++) {
                    matrix[i] = new int[cities_number];
                }
            } else if(line_number <= cities_number+1) {         // wczytywanie następnych linii z pliku, +1 bo zaczynam pobierać dane od 2 linii (ograniczenie, ponieważ na dole pliku znajduje się wynik)
                stringstream ss;
                ss << line;

                for(int i=0; i<cities_number; i++) {
                    ss >> matrix[line_number-2][i];
                }
            }

            line_number++;
        }
    }

    file.close();

    return matrix;
}

int getCitiesNumber_l() {
    return cities_number;
}
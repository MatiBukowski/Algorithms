//
// Created by mateu on 12.01.2025.
//

#include "load.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <utility>

using namespace std;

pair<int**, int> load_data(string file_name) {                                                          // funkcja wczytująca liczbę miast oraz macierz z pliku
    int** matrix = nullptr;
    ifstream file;
    int cities_number = 0;
    int row = 0;                        // aktualny wiersz macierzy
    int col = 0;                        // aktualna kolumna macierzy
    int elements_amount = 0;            // aktualny element macierzy

    file.open(file_name+".atsp");

    if(file.good()==false) {
        cout << "Plik nie istnieje" << endl;
    } else {
        string line;
        int line_number = 1;

        while (getline(file, line)) {
            if (line_number == 4) {
                string key_word = "DIMENSION:";
                int pos = line.find(key_word) + key_word.length() + 1;  // 1 - bo spacja po :

                string number = line.substr(pos);
                stringstream ss;				                // stringstream to typ danych, który pozwala na łatwe konwertowanie danych np. z string na int
                ss << number;
                ss >> cities_number;

                ss.clear();

                matrix = new int*[cities_number];                   // tworzenie dwuwymiarowej dynamicznej tablicy, która będzie przechowywała dane wczytanej instancji
                for(int i=0; i<cities_number; i++) {
                    matrix[i] = new int[cities_number];
                }
            } else if(line_number >= 8) {
                int element;                                        // dana liczba z pliku

                stringstream ss;
                ss << line;

                while(ss >> element) {
                    matrix[row][col] = element;

                    elements_amount++;
                    col = elements_amount%cities_number;                       // kolumny od 0 do cities_number-1

                    if(col==0) {                                                // jesli dla danego wiersza doda się juz cities_number liczb (cities_number kolumn) to przechodzi się do następnego wiersza
                        row++;
                    }
                }

                ss.clear();
            }

            line_number++;
        }
    }

    // for(int i=0; i<cities_number; i++) {
    //     for(int j=0; j<cities_number; j++) {
    //         cout << setw(3) << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    file.close();

    return {matrix, cities_number};
}
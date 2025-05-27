//
// Created by mateu on 09.10.2024.
//

#include "main_menu.h"
#include <iomanip>
#include <iostream>
#include <windows.h>
#include "load.h"
#include "generate.h"
#include "algorithm_menu.h"
#include "nearest_neighbour.h"
#include "complete_review.h"
#include "random_algorithm.h"
#include <fstream>

using namespace std;

void delete_matrix(int**& matrix, int cities_number) {       // usuwanie macierzy, o ile już istnieje, referencja do wskaźnika aby móć zmieniać sam wskaźnik
    if(matrix != nullptr) {
        for(int i = 0; i < cities_number; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

void show_main_menu() {
    cout << "------------------------------------MAIN-MENU-------------------------------------" << endl;
    cout << "1 - Wczytaj dane z pliku" << endl;
    cout << "2 - Wygeneruj dane losowe" << endl;
    cout << "3 - Wyswietl ostatnio wczytane lub wygenerowane dane" << endl;
    cout << "4 - Wybierz algorytm dla zapisanych danych" << endl;
    cout << "5 - Zakoncz program" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_switch(int**& matrix, int &cities_number) {              // wybór nastepnej akcji przez użytkownika, parametry funckji to zmienne przekazywane przez referencję
    int choice;

    cout << "Podaj wybor: ";
    cin >> choice;
    system("cls");

    switch(choice) {
        case 1: {
            if(matrix != nullptr) {                                  // zwalnianie pamięci przed załadowaniem nowego problemu
                delete_matrix(matrix, cities_number);
            }
            matrix = generate_loaded_matrix();
            cities_number = getCitiesNumber_l();
            break;
        }
        case 2: {
            if(matrix != nullptr) {                                  // zwalnianie pamięci przed wygenerowaniem nowego problemu
                delete_matrix(matrix, cities_number);
            }

            matrix = generate_random_matrix();
            cities_number = getCitiesNumber_g();
            break;
        }
        case 3: {
            cout << "MACIERZ MIAST:" << endl << endl;
            if(matrix != nullptr) {
                for(int i=0; i<cities_number; i++) {
                    for(int j=0; j<cities_number; j++) {
                        cout << setw(3) << matrix[i][j] << " ";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "Zaden problem nie istnieje" << endl;
            }
            break;
        }
        case 4: {
            show_algorithm_menu();
            choice_algorithm_menu(matrix, cities_number);

            break;
        }
        case 5: {
            if(matrix != nullptr) {                                 // zwalnianie pamięci przed wyjściem z programu
                delete_matrix(matrix, cities_number);
            }
            exit(0);
        }
        case 6: {
            ofstream plik_wynikowy;              // generowanie danych i wyników do sprawozdania
            plik_wynikowy.open("final_results_PEA1.csv", ios::app);

            for(int i=0; i<100; i++) {
                matrix = generate_random_matrix();
                cities_number = getCitiesNumber_g();

                CompleteReview *CR = new CompleteReview(matrix, cities_number);
                CR->algorithm_cr();
                double time1 = CR->getElapsedTime()*1e3;
                cout << time1 << endl;
                delete CR;

                NearestNeighbour *NN = new NearestNeighbour(matrix, cities_number);
                NN->algorithm_nn();
                double time2 = NN->getElapsedTime()*1e3;
                cout << time2 << endl;
                delete NN;

                RandomAlgorithm *RA = new RandomAlgorithm(matrix, cities_number);
                RA->algorithm_ra();
                double time3 = RA->getElapsedTime()*1e3;
                cout << time3 << endl;
                delete RA;

                plik_wynikowy << time1 << ";" << time2 << ";" << time3 << endl;
            }

            plik_wynikowy.close();
            break;
        }
        default: {
            cout << "Niepoprawny numer polecenia" << endl << endl;
        }

    }
}
//
// Created by mateu on 11.10.2024.
//

#include "complete_review.h"
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

CompleteReview::CompleteReview(int **Matrix, int Cities_number) {
    matrix = Matrix;
    cities_number = Cities_number;
}

CompleteReview::~CompleteReview() {}

void CompleteReview::swap(int& a, int& b) {
    int pom = a;
    a = b;
    b = pom;
}

void CompleteReview::reverse(int cities_index[], int beginning, int end) {                                  // zamiana elementów tablic na odwrót
    while (beginning < end) {
        swap(cities_index[beginning], cities_index[end]);
        beginning++;
        end--;
    }
}

void CompleteReview::permutation_generator(int cities_index[], int cities_number) {

    int k = -1;
    for (int i=0; i<cities_number-1; i++) {                                                                 // szukam takiego, największego indeksu k, że cities_index[k] < cities_index[k+1] (jeśli k nie znaleziono, to wszystkie permutacje zostały wygenerowane)
        if(cities_index[i] < cities_index[i + 1]) {
            k = i;
        }
    }

    int l = -1;
    for (int i=k+1; i<cities_number; i++) {                                                                 // szukam takiego, największego indeksu l większego od k (dlatego zaczynam szukanie od k+1), że cities_index[k] < cities_index[l]
        if(cities_index[k] < cities_index[i]) {
            l = i;
        }
    }

    swap(cities_index[k], cities_index[l]);                                                        // zamiana wartości cities_index[k] z cities_index[l]

    reverse(cities_index, k + 1, cities_number - 1);                                             // zamiana miejscami elemntów tablicy - na odwrót, od cities_index[k+1] do cities_index[cities_number-1] (do ostatniego elementu tablicy)
}

void CompleteReview::algorithm_cr() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceCounter(&start);									                                    // rozpoczęcie mierzenia czasu

    int cities_index[cities_number];                                                                        // tablica przechowująca indeksy miast
    int sum_path;                                                                                           // zmienna przechowująac aktualną sumę danej ścieżki
    int permutation_amount = 1;                                                                             // zmienna przechowująca liczbę wszystkich permutacji
    int *path = new int[cities_number+1];                                                                   // kolejne wierzchołki badanej ścieżki
    int *final_path = new int[cities_number+1];                                                             // kolejne wierzchołki końcowej, najkrótszej ścieżki

    for(int i = 0; i < cities_number; i++) {
        cities_index[i] = i;
    }

    for (int i = cities_number-1; i > 1; i--) {                                                               // obliczanie ilości permutacji, (n-1)! ponieważ wszystkie ścieżki dla permutacji dla danego wierzchołka poczatkowego zawierają się w reszcie permutacji
        permutation_amount *= i;
    }

    for(int i=0; i<permutation_amount; i++) {                                                               // przeszukiwanie wszytskich istneijących ścieżek (każdej permutacji)
        sum_path = 0;

        permutation_generator(cities_index, cities_number);

        for(int j=1; j<cities_number; j++) {
            sum_path = sum_path + matrix[cities_index[j-1]][cities_index[j]];                               // sumowanie długości dróg do miast
            path[j] = cities_index[j];                                                                      // zapisywanie ścieżki
        }
        path[0] = cities_index[0];                                                                          // zapisywanie ścieżki
        path[cities_number] = cities_index[0];                                                              // zapisywanie ścieżki

        sum_path = sum_path + matrix[cities_index[cities_number-1]][cities_index[0]];                       // na koniec dodajemy drogę: od miasta na którym skończyliśmy do miasta poczatkowego

        if(sum_path < final_sum_path) {
            final_sum_path = sum_path;

            for(int j=0; j<cities_number+1; j++) {                                                          // przypisanie wartości tablicy dynamicznej path do tablicy dynamicznej final_path
                final_path[j] = path[j];
            }
        }
    }
    QueryPerformanceCounter(&end);

    cout << "Dlugosc sciezki: " << final_sum_path << endl;
    cout << "Ciag wierzcholkow: ";
    for(int i = 0; i < cities_number; i++) {
        cout << final_path[i] << " -> ";
    }
    cout << final_path[cities_number] << endl;

    delete[] path;
    delete[] final_path;

    // QueryPerformanceCounter(&end);																			// zakończenie mierzenia czasu
    elapsedTime1 = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;		                // policzenie czasu wykonywania się algorytmu
    cout << "Algorytm przegladu zupelnego - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;

    ofstream results_file;
    results_file.open("results_PEA1.csv", ios::app);

    results_file << "Algorytm przegladu zupelnego; " << cities_number << " miast; " << "czas: " << elapsedTime1*1e3 << " ms" << endl;
    results_file.close();
}

int CompleteReview::getFinalSumPathCR() {
    return final_sum_path;
}

double CompleteReview::getElapsedTime() {
    return elapsedTime1;
}

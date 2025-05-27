//
// Created by mateu on 11.10.2024.
//
#include "nearest_neighbour.h"
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

NearestNeighbour::NearestNeighbour(int **Matrix, int Cities_number) {
    matrix = Matrix;
    cities_number = Cities_number;
}

NearestNeighbour::~NearestNeighbour() {}

void NearestNeighbour::algorithm_nn() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceCounter(&start);									        // rozpoczęcie mierzenia czasu

    bool *visited = new bool[cities_number];                                    // tablica odwiedzonych miast
    int *path = new int[cities_number+1];                                       // kolejne wierzchołki badanej ścieżki
    int *final_path = new int[cities_number+1];                                 // kolejne wierzchołki końcowej, najkrótszej ścieżki
    int current_city;
    int neighbour = 0;
    int sum_path;

    for(int i = 0; i < cities_number; i++) {
        visited[i] = false;
    }

    for(int i = 0; i < cities_number; i++) {
        visited[i] = true;                                                      // miasto, w którym się obecnie znajdujemy jest odwiedzone
        sum_path = 0;                                                           // na poczatku całkowita droga jest równa 0
        current_city = i;
        path[0] = current_city;                                                 // zapisywanie ścieżki
        path[cities_number] = current_city;                                     // ostatnie miasto to początkowe miasto, ponieważ na koniec do niego wracamy

        for(int j = 0; j < cities_number-1; j++) {                              // szukanie sąsiadów n-1 razy
            neighbour = findNearestNeighbour(visited, current_city);

            if(neighbour != -1) {
                sum_path = sum_path + matrix[current_city][neighbour];          // łączna droga
                current_city = neighbour;
                path[j+1] = current_city;                                       // zapisywanie ścieżki
            }
        }

        sum_path = sum_path + matrix[current_city][i];                          // na koniec dodajemy drogę: od miasta na którym skończyliśmy do miasta poczatkowego
        if(sum_path < final_sum_path) {
            final_sum_path = sum_path;

            for(int j = 0; j < cities_number+1; j++) {                          // przypisanie wartości tablicy dynamicznej path do tablicy dynamicznej final_path
                final_path[j] = path[j];
            }
        }

        for(int j = 0; j < cities_number; j++) {                                // dla kolejnego miasta początkowego czyścimy tablicę visited
            visited[j] = false;
        }
    }
    QueryPerformanceCounter(&end);

    cout << "Dlugosc sciezki: " << final_sum_path << endl;
    cout << "Ciag wierzcholkow: ";
    for(int i = 0; i < cities_number; i++) {
        cout << final_path[i] << " -> ";
    }
    cout << final_path[cities_number] << endl;

    delete[] visited;
    delete[] path;
    delete[] final_path;

    // QueryPerformanceCounter(&end);																			// zakończenie mierzenia czasu
    elapsedTime1 = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;		                // policzenie czasu wykonywania się algorytmu
    cout << "Algorytm najblizszego sasiada - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;

    ofstream results_file;
    results_file.open("results_PEA1.csv", ios::app);

    results_file << "Algorytm najblizszego sasiada; " << cities_number << " miast; " << "czas: " << elapsedTime1*1e3 << " ms" << endl;
    results_file.close();
}

int NearestNeighbour::findNearestNeighbour(bool* visited, int current_city) {
    int min_path = 200;                                                         // max path = 100
    int neighbour = -1;                                                         // najbliższe sąsiednie miasto

        for(int i=0; i<cities_number; i++) {
            if(i != current_city) {                                             // jeśli dane miasto nie jest tym, w którym się obecnie znajdujemy
                if(visited[i] == false) {                                       // jeśli dane miasto nie zostało już odwiedzone
                    if(matrix[current_city][i] < min_path) {                    // jeśli droga jest mniejsza od dotychczasowej najmniejszej drogi
                        min_path = matrix[current_city][i];
                        neighbour = i;                                          // sąsiadem jest i
                    }
                }
            }
        }

    visited[neighbour] = true;
    return neighbour;
}

int NearestNeighbour::getFinalSumPathNN() {
    return final_sum_path;
}

double NearestNeighbour::getElapsedTime() {
    return elapsedTime1;
}
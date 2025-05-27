//
// Created by mateu on 13.12.2024.
//

#include "nearest_neighbour.h"
#include <iostream>

using namespace std;

NearestNeighbour::NearestNeighbour(int **Matrix, int Cities_number) {
    matrix = Matrix;
    cities_number = Cities_number;
}

NearestNeighbour::~NearestNeighbour() {}

int* NearestNeighbour::algorithm_nn() {

    bool *visited = new bool[cities_number];                                    // tablica odwiedzonych miast
    int *path = new int[cities_number];                                       // kolejne wierzchołki badanej ścieżki (bez końcowego)
    int *final_path = new int[cities_number];                                 // kolejne wierzchołki końcowej, najkrótszej ścieżki (bez końcowego)
    int current_city;
    int neighbour = 0;
    int sum_path;

    for(int i = 0; i < cities_number; i++) {
        visited[i] = false;
    }

    // for(int i = 0; i < cities_number; i++) {
        // visited[i] = true;                                                      // miasto, w którym się obecnie znajdujemy jest odwiedzone
        visited[0] = true;
        sum_path = 0;                                                           // na poczatku całkowita droga jest równa 0
        current_city = 0;
        path[0] = current_city;                                                 // zapisywanie ścieżki
        // path[cities_number] = current_city;                                     // ostatnie miasto to początkowe miasto, ponieważ na koniec do niego wracamy

        for(int j = 0; j < cities_number-1; j++) {                              // szukanie sąsiadów n-1 razy
            neighbour = findNearestNeighbour(visited, current_city);

            if(neighbour != -1) {
                sum_path = sum_path + matrix[current_city][neighbour];          // łączna droga
                current_city = neighbour;
                path[j+1] = current_city;                                       // zapisywanie ścieżki
            }
        }

        // sum_path = sum_path + matrix[current_city][i];                          // na koniec dodajemy drogę: od miasta na którym skończyliśmy do miasta poczatkowego
        sum_path = sum_path + matrix[current_city][0];
        if(sum_path < final_sum_path) {
            final_sum_path = sum_path;

            for(int j = 0; j < cities_number; j++) {                            // przypisanie wartości tablicy dynamicznej path do tablicy dynamicznej final_path
                final_path[j] = path[j];
            }
        }

        for(int j = 0; j < cities_number; j++) {                                // dla kolejnego miasta początkowego czyścimy tablicę visited
            visited[j] = false;
        }
    // }


    delete[] visited;
    delete[] path;

    return final_path;
}

int NearestNeighbour::findNearestNeighbour(bool* visited, int current_city) {
    int min_path = INT_MAX;                                                         // max path = 100
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

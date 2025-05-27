//
// Created by mateu on 10.10.2024.
//
#include "generate.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int cities_number_2;

int** generate_random_matrix() {
    srand(time(NULL));

    int **matrix = nullptr;

    cout << "Podaj ilosc miast: ";
    cin >> cities_number_2;
    cout << endl;
    // cities_number_2 = 10;

    matrix = new int*[cities_number_2];               // tworzenie dwuelementowej dynamicznej tablicy, która będzie przechowywała dane wygenerowanej instancji
    for(int i=0; i<cities_number_2; i++) {
        matrix[i] = new int[cities_number_2];
    }

    for(int i=0; i<cities_number_2; i++) {
        for(int j=0; j<cities_number_2; j++) {
            matrix[i][j] = rand()%100 + 1;
        }
        matrix[i][i] = -1;
    }

    return matrix;
}

int getCitiesNumber_g() {
    return cities_number_2;
}
//
// Created by mateu on 03.11.2024.
//
#include "generate.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int** generate_random_asymmetric_matrix(int cities_number) {
    // srand(time(NULL)*clock());                                                         // clock() zwraca liczbę cykli, które upłynęły od włączenia programu
    srand(time(NULL));                                                         // clock() zwraca liczbę cykli, które upłynęły od włączenia programu

    int **matrix = nullptr;


    matrix = new int*[cities_number];               // tworzenie dwuwymiarowej dynamicznej tablicy, która będzie przechowywała dane wygenerowanej instancji
    for(int i=0; i<cities_number; i++) {
        matrix[i] = new int[cities_number];
    }

    for(int i=0; i<cities_number; i++) {
        for(int j=0; j<cities_number; j++) {
            matrix[i][j] = rand()%100 + 1;
        }
        matrix[i][i] = -1;
    }

    return matrix;
}

int* generate_random_symmetric_matrix(int cities_number) {
    // srand(time(NULL)*clock());
    srand(time(NULL));

    // int **matrix = nullptr;
    //
    //
    // matrix = new int*[cities_number];               // tworzenie dwuwymiarowej dynamicznej tablicy, która będzie przechowywała dane wygenerowanej instancji
    // for(int i=0; i<cities_number; i++) {
    //     matrix[i] = new int[cities_number];
    // }
    //
    // int pom = 0;
    //
    // for(int i=0; i<cities_number; i++) {
    //     for(int j=pom; j<cities_number; j++) {
    //         matrix[i][j] = rand()%100 + 1;
    //     }
    //     pom++;
    //     matrix[i][i] = -1;
    // }
    //
    // pom = 1;
    //
    // for(int i=pom-1; i<cities_number; i++) {
    //     for(int j=pom; j<cities_number; j++) {
    //         matrix[j][i] = matrix[i][j];
    //     }
    //     pom++;
    // }

    int *sym_array = nullptr;

    int elements_amount = (cities_number*(cities_number-1))/2;
    sym_array = new int[elements_amount];

    for(int i=0; i<elements_amount; i++) {
        sym_array[i] = rand()%100 + 1;
    }

    return sym_array;

    // return matrix;
}

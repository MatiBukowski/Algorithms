//
// Created by mateu on 29.12.2024.
//

#include "motion_rate_function.h"
#include "moves.h"
#include <iostream>


using namespace std;

int swap_motion_rate_function(int** matrix, int* permutation, int index_1, int index_2, int cities_number) {                  // funkcja oceny ruchu
    int* new_permutation = new int[cities_number];
    int new_distance = 0;                                                                                               // częściowa długość ścieżki, która się zmieniła po zamianie miejscami elementów
    int old_distance = 0;
    copy(permutation, permutation + cities_number, new_permutation);

    swap(new_permutation[index_1], new_permutation[index_2]);                                                   // funkcja ruchu - zamiana miejscami miast o zadanych indeksach

    // obliczane są części ścieżek, które się zmieniły aby nie obliczać za każdym razem całych scieżek
    if(index_2 != index_1+1) {                                                                                                                  // jeśli indeksy nie są obok siebie
        if(index_1 > 0 and index_2 < cities_number-1) {
            old_distance = matrix[permutation[index_1-1]][permutation[index_1]] + matrix[permutation[index_1]][permutation[index_1+1]]          // dla indeksu 1
            + matrix[permutation[index_2-1]][permutation[index_2]] + matrix[permutation[index_2]][permutation[index_2+1]];                       // dla indeksu 2

            new_distance = matrix[new_permutation[index_1-1]][new_permutation[index_1]] + matrix[new_permutation[index_1]][new_permutation[index_1+1]]
            + matrix[new_permutation[index_2-1]][new_permutation[index_2]] + matrix[new_permutation[index_2]][new_permutation[index_2+1]];
        } else if(index_1 == 0 and index_2 < cities_number-1) {
            old_distance = matrix[permutation[index_1]][permutation[index_1+1]]
            + matrix[permutation[index_2-1]][permutation[index_2]] + matrix[permutation[index_2]][permutation[index_2+1]]
            + matrix[permutation[cities_number-1]][permutation[0]];                                                                                         // dla przejscia z przedostatniego do ostatniego miasta (początkowego)

            new_distance = matrix[new_permutation[index_1]][new_permutation[index_1+1]]
            + matrix[new_permutation[index_2-1]][new_permutation[index_2]] + matrix[new_permutation[index_2]][new_permutation[index_2+1]]
            + matrix[new_permutation[cities_number-1]][new_permutation[0]];
        } else if(index_1 == 0 and index_2 == cities_number-1) {
            old_distance = matrix[permutation[index_1]][permutation[index_1+1]]
            + matrix[permutation[index_2-1]][permutation[index_2]]
            + matrix[permutation[cities_number-1]][permutation[0]];

            new_distance = matrix[new_permutation[index_1]][new_permutation[index_1+1]]
            + matrix[new_permutation[index_2-1]][new_permutation[index_2]]
            + matrix[new_permutation[cities_number-1]][new_permutation[0]];
        } else if(index_1 > 0 and index_2 == cities_number-1) {
            old_distance = matrix[permutation[index_1-1]][permutation[index_1]] + matrix[permutation[index_1]][permutation[index_1+1]]
            + matrix[permutation[index_2-1]][permutation[index_2]]
            + matrix[permutation[cities_number-1]][permutation[0]];

            new_distance = matrix[new_permutation[index_1-1]][new_permutation[index_1]] + matrix[new_permutation[index_1]][new_permutation[index_1+1]]
            + matrix[new_permutation[index_2-1]][new_permutation[index_2]]
            + matrix[new_permutation[cities_number-1]][new_permutation[0]];
        }
    } else {                                                                                                // jeśli indeksy są obok siebie
        if(index_1 > 0 and index_2 < cities_number-1) {
            old_distance = matrix[permutation[index_1-1]][permutation[index_1]] + matrix[permutation[index_1]][permutation[index_2]]
            + matrix[permutation[index_2]][permutation[index_2+1]];

            new_distance = matrix[new_permutation[index_1-1]][new_permutation[index_1]] + matrix[new_permutation[index_1]][new_permutation[index_2]]
            + matrix[new_permutation[index_2]][new_permutation[index_2+1]];
        } else if(index_1 == 0) {
            old_distance = matrix[permutation[index_1]][permutation[index_2]]
            + matrix[permutation[index_2]][permutation[index_2+1]]
            + matrix[permutation[cities_number-1]][permutation[0]];

            new_distance = matrix[new_permutation[index_1]][new_permutation[index_2]]
            + matrix[new_permutation[index_2]][new_permutation[index_2+1]]
            + matrix[new_permutation[cities_number-1]][new_permutation[0]];
        } else if(index_2 == cities_number-1) {
            old_distance = matrix[permutation[index_1-1]][permutation[index_1]] + matrix[permutation[index_1]][permutation[index_2]]
            + matrix[permutation[cities_number-1]][permutation[0]];

            new_distance = matrix[new_permutation[index_1-1]][new_permutation[index_1]] + matrix[new_permutation[index_1]][new_permutation[index_2]]
            + matrix[new_permutation[cities_number-1]][new_permutation[0]];
        }
    }

    int value = new_distance - old_distance;                                // wartość funkcji - różnica długości ścieżek
    // cout << new_distance << " " << old_distance << endl;

    delete []new_permutation;
    return value;
}

int invert_motion_rate_function(int** matrix, int *permutation, int start, int end, int cities_number) {
    int* new_permutation = new int[cities_number];
    int new_distance = 0;                                                                                               // częściowa długość ścieżki, która się zmieniła po ruchu
    int old_distance = 0;                                                                                               // stara częściowa długość ścieżki, która ulegnie zmianie po ruchu

    copy(permutation, permutation + cities_number, new_permutation);

    invert_move(new_permutation, start, end);                                                                           // funkcja ruchu - invert

    if(start == 0 && end == cities_number - 1) {
        for(int i=start; i<end; i++) {
            old_distance += matrix[permutation[i]][permutation[i+1]];
            new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
        }

        old_distance += matrix[permutation[cities_number-1]][permutation[0]];                                           // z ostatniego miasta do pierwszego
        new_distance += matrix[new_permutation[cities_number-1]][new_permutation[0]];
    } else if(start != 0 && end == cities_number - 1) {
        old_distance += matrix[permutation[start-1]][permutation[start]];
        new_distance += matrix[new_permutation[start-1]][new_permutation[start]];

        for(int i=start; i<end; i++) {
            old_distance += matrix[permutation[i]][permutation[i+1]];
            new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
        }

        old_distance += matrix[permutation[cities_number-1]][permutation[0]];                                           // z ostatniego miasta do pierwszego
        new_distance += matrix[new_permutation[cities_number-1]][new_permutation[0]];
    } else if(start == 0 && end != cities_number - 1) {
        for(int i=start; i<end; i++) {
            old_distance += matrix[permutation[i]][permutation[i+1]];
            new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
        }

        old_distance += matrix[permutation[end]][permutation[end+1]];
        new_distance += matrix[new_permutation[end]][new_permutation[end+1]];

        old_distance += matrix[permutation[cities_number-1]][permutation[0]];                                           // z ostatniego miasta do pierwszego
        new_distance += matrix[new_permutation[cities_number-1]][new_permutation[0]];
    } else if(start != 0 && end != cities_number - 1) {
        old_distance += matrix[permutation[start-1]][permutation[start]];
        new_distance += matrix[new_permutation[start-1]][new_permutation[start]];

        for(int i=start; i<end; i++) {
            old_distance += matrix[permutation[i]][permutation[i+1]];
            new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
        }

        old_distance += matrix[permutation[end]][permutation[end+1]];
        new_distance += matrix[new_permutation[end]][new_permutation[end+1]];

        old_distance += matrix[permutation[cities_number-1]][permutation[0]];                                           // z ostatniego miasta do pierwszego
        new_distance += matrix[new_permutation[cities_number-1]][new_permutation[0]];
    }

    int value = new_distance - old_distance;                                // wartość funkcji - różnica długości ścieżek

    delete []new_permutation;
    return value;
}

int insert_motion_rate_function(int** matrix, int *permutation, int from_index, int to_index, int cities_number) {
    int* new_permutation = new int[cities_number];
    int new_distance = 0;                                                                                               // częściowa długość ścieżki, która się zmieniła po ruchu
    int old_distance = 0;                                                                                               // stara częściowa długość ścieżki, która ulegnie zmianie po ruchu

    copy(permutation, permutation + cities_number, new_permutation);

    insert_move(new_permutation, from_index, to_index);

    if(from_index > to_index) {                                                                                         // dla ułatwienia obliczeń częściowej ścieżki
        int pom = from_index;
        from_index = to_index;
        to_index = pom;
    }

    // if(from_index > 0 && to_index < cities_number-1) {
    //     for(int i=from_index-1; i<to_index+1; i++) {
    //         old_distance += matrix[permutation[i]][permutation[i+1]];
    //         new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
    //     }
    // } else if(from_index == 0 && to_index < cities_number-1) {
    //     for(int i=from_index; i<to_index+1; i++) {
    //         old_distance += matrix[permutation[i]][permutation[i+1]];
    //         new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
    //     }
    //     old_distance += matrix[permutation[cities_number-1]][permutation[0]];
    //     new_distance += matrix[new_permutation[cities_number-1]][new_permutation[0]];
    // } else if(from_index > 0 && to_index == cities_number-1) {
    //     for(int i=from_index-1; i< to_index; i++) {
    //         old_distance += matrix[permutation[i]][permutation[i+1]];
    //         new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
    //     }
    //     old_distance += matrix[permutation[cities_number-1]][permutation[0]];
    //     new_distance += matrix[new_permutation[cities_number-1]][new_permutation[0]];
    // } else if(from_index == 0 && to_index == cities_number-1) {                         // całkowita ścieżka się nie zmieni
    //     old_distance = 0;
    //     new_distance = 0;
    // }

    for (int i=0; i<cities_number-1; i++) {
        old_distance += matrix[permutation[i]][permutation[i+1]];
        new_distance += matrix[new_permutation[i]][new_permutation[i+1]];
    }
    old_distance += matrix[permutation[cities_number-1]][permutation[0]];
    new_distance += matrix[new_permutation[cities_number-1]][new_permutation[0]];

    int value = new_distance - old_distance;                                // wartość funkcji - różnica długości ścieżek

    delete []new_permutation;
    return value;
}
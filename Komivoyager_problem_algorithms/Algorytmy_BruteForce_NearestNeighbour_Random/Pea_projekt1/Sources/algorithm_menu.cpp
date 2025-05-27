//
// Created by mateu on 11.10.2024.
//
#include "algorithm_menu.h"
#include <iostream>
#include "nearest_neighbour.h"
#include "complete_review.h"
#include "random_algorithm.h"

using namespace std;

void show_algorithm_menu() {                                                                                        // wyświetlenie menu algorytmów
    cout << "-------------------------------ALGORITHM-MENU-------------------------------------" << endl;
    cout << "1 - Przeglad zupelny" << endl;
    cout << "2 - Najblizszych sasiadow" << endl;
    cout << "3 - Losowy" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_algorithm_menu(int** matrix, int cities_number) {                                                       // wybór algorytmu przez użytkownika
    int choice;

    cout << "Podaj wybor: ";
    cin >> choice;
    system("cls");

    switch(choice) {
        case 1: {
            CompleteReview *CR = new CompleteReview(matrix, cities_number);
            CR->algorithm_cr();
            delete CR;

            break;
        }
        case 2: {
            NearestNeighbour *NN = new NearestNeighbour(matrix, cities_number);
            NN->algorithm_nn();
            delete NN;

            break;
        }
        case 3: {
            RandomAlgorithm *RA = new RandomAlgorithm(matrix, cities_number);
            RA->algorithm_ra();
            delete RA;

            break;
        }
        default: {
            cout << "Niepoprawny wybor";
            show_algorithm_menu();
            choice_algorithm_menu(matrix, cities_number);
        }
    }
}

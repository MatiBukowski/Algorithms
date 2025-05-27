//
// Created by mateu on 12.10.2024.
//
#include "random_algorithm.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <fstream>

using namespace std;

RandomAlgorithm::RandomAlgorithm(int **Matrix, int Cities_number) {
    matrix = Matrix;
    cities_number = Cities_number;
}

RandomAlgorithm::~RandomAlgorithm() {}

void RandomAlgorithm::generate_random_path(int* path) {

    for (int i = 0; i < cities_number+1; i++) {                                 // cities_number+1, ponieważ path ma cities_number+1 elementów
        path[i] = i;
    }

    for (int i = 0; i < cities_number; i++) {
        int random_number = rand() % cities_number;
        swap(path[i], path[random_number]);
    }
    path[cities_number] = path[0];                                              // ostatnie miasto w path to początkowe miasto
}

void RandomAlgorithm::algorithm_ra() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceCounter(&start);									        // rozpoczęcie mierzenia czasu

    srand(time(NULL));

    int *path = new int[cities_number+1];                                       // kolejne wierzchołki badanej ścieżki
    int *final_path = new int[cities_number+1];                                 // kolejne wierzchołki końcowej, najkrótszej ścieżki
    int sum_path;
    int permutation_amount = 1;

    for (int i = cities_number-2; i > 1; i--) {                                 // obliczanie ilości iteracji - (cities_number-2)!
        permutation_amount *= i;
    }

    for(int i = 0; i < permutation_amount; i++) {                               // (cities_number-2)! - iteracji losowego szukania najlepszej ścieżki
        generate_random_path(path);
        sum_path = 0;

        for(int j = 1; j < cities_number+1; j++) {
            sum_path = sum_path + matrix[path[j-1]][path[j]];                   // sumują się długości ścieżek między dwoma następnymi, sasiednimi miastami
        }

        if(sum_path < final_sum_path) {
            final_sum_path = sum_path;
            for(int j = 0; j < cities_number+1; j++) {
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
    cout << "Algorytm losowy - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;

    ofstream results_file;
    results_file.open("results_PEA1.csv", ios::app);

    results_file << "Algorytm losowy; " << cities_number << " miast; " << "czas: " << elapsedTime1*1e3 << " ms" << endl;
    results_file.close();
}

int RandomAlgorithm::getFinalSumPathRA() {
    return final_sum_path;
}

double RandomAlgorithm::getElapsedTime() {
    return elapsedTime1;
}





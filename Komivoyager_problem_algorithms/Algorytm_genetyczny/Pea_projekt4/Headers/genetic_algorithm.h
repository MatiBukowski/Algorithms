;//
// Created by mateu on 12.01.2025.
//

#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H
#include <iostream>

class Genetic_algorithm {                                       // klasa algorytmu genetycznego
    int** matrix;
    int cities_number;
    double wsp_krzyzowania;                                     // współczynnik krzyżowania
    double wsp_mutacji;                                         // współczynnik mutacji
    std::string crossover_method;                               // nazwa metody krzyżowania
    std::string mutation_method;                                // nazwa metody mutacji
    int stop_time;                                              // czas, po ktorym program zakończy działanie - kryterium stopu
    int populationSize;                                         // wielkość populacji
    std::string load_file_name;                                 // nazwa pliku, z którego pobierane są dane

public:
    Genetic_algorithm(int**, int, double, double, std::string, std::string, int, int, std::string);
    ~Genetic_algorithm();
    void geneticAlgorithm();
    int** generate_first_population(int**, int);                // funkcja generująca początkową populacje
    int rate_function(int*);                                    // funkcja oceny permutacji (wylicza długość ścieżki)
    int* single_point_crossover(int*, int*, int*);              // metoda krzyżowania - Single Point Crossover
    int* cycle_crossover(int*, int*, int*);                     // metoda krzyżowania - Cycle Crossover
    int* mutation_swap(int*);                                   // metoda mutacji - swap
    int* mutation_insert(int*);                                 // metoda mutacji - insert
    int tournament_selection(int, int**);                       // funkcja wyboru rodzica poprzez turniej

};
#endif //GENETIC_ALGORITHM_H

//
// Created by mateu on 12.01.2025.
//

#include "genetic_algorithm.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <windows.h>
#include "quicksort.h"
#include <fstream>
#include "nearest_neighbour.h"

using namespace std;

Genetic_algorithm::Genetic_algorithm(int** matrix, int cities_number, double wsp_krzyzowania, double wsp_mutacji, std::string crossover_method, std::string mutation_method, int stop_time, int population_size, std::string load_file_name) {
    this->matrix = matrix;
    this->cities_number = cities_number;
    this->wsp_krzyzowania = wsp_krzyzowania;
    this->wsp_mutacji = wsp_mutacji;
    this->crossover_method = crossover_method;
    this->mutation_method = mutation_method;
    this->stop_time = stop_time;
    this->populationSize = population_size;
    this->load_file_name = load_file_name;
}

Genetic_algorithm::~Genetic_algorithm() {}

void Genetic_algorithm::geneticAlgorithm() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceCounter(&start);

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);                                                    // CLOCK_MONOTONIC gwarantuje stały wzrost czasu
    srand(ts.tv_nsec ^ ts.tv_sec);

    int population_size = 0;

    if(populationSize == 1) {                                                   // ustawianie wielkości populacji
        population_size = floor(cities_number/4);
    } else if(populationSize == 2) {
        population_size = floor(cities_number/3);
    } else if(populationSize == 3) {
        population_size = floor(cities_number/2);
    } else population_size = 10;
    // ------------------------------------------------------------------------------------
    // int chosen_size = floor(population_size*0.2);                            // wielkość grupy wybranych osobników z populacji - 20%
    int chosen_size;                                                            // wielkość grupy wybranych osobników z populacji - 20%
    int pom = population_size - floor(population_size*0.2);
    if(pom%2 == 0) {
        chosen_size = floor(population_size*0.2);
    } else chosen_size = ceil(population_size*0.2);

    double elapsedTime = 0;
    double bestElapsedTime = 0;
    int best_distance = INT_MAX;
    int* best_permutation = new int[cities_number];
    string crossover_method_name;

    int** population = new int*[population_size];                     // tworzenie dwuwymiarowej dynamicznej tablicy, która będzie przechowywała populacje
    for(int i=0; i<population_size; i++) {
        population[i] = new int[cities_number];
    }

    int** new_population = new int*[population_size];                     // tworzenie dwuwymiarowej dynamicznej tablicy, która będzie przechowywała nową populacje
    for(int i=0; i<population_size; i++) {
        new_population[i] = new int[cities_number];
    }

    int** distance_matrix = new int*[population_size];                      // tablica długości ścieżek dla permutacji z populacji (pierwsza kolumna to indeks, druga to długość)
    for(int i=0; i<population_size; i++) {
        distance_matrix[i] = new int[2];
    }

    // vector<std::vector<int>> new_population;
    // new_population.resize(population_size, vector<int>(cities_number, 0));
    vector<int*> chosen_permutation_from_population;
    int* parent1;                                                            // rodzic1
    int* parent2;                                                            // rodzic2
    int* child1 = new int[cities_number];                                    // dziecko powstałe z dwóch rodziców
    int* child2 = new int[cities_number];                                    // dziecko powstałe z dwóch rodziców
    // ------------------------------------------------------------------------------------
    population = generate_first_population(population, population_size);

    while(elapsedTime < stop_time) {

        for(int i=0; i<population_size; i++) {                              // długości ścieżek dla każdej z permutacji w populacji
            distance_matrix[i][0] = i;
            distance_matrix[i][1] = rate_function(population[i]);
        }

        for(int i=0; i<floor((population_size-chosen_size)/2); i++) {                                          // krzyżowanie rodziców, tworzenie potomków i ich mutowanie - 90% nowje populacji to potomkowie

            int random1 = tournament_selection(population_size, distance_matrix);                                             // indeksy rodziców wybrane w turnieju
            int random2;
            do {
                random2 = tournament_selection(population_size, distance_matrix);
            } while(random1 == random2);

            parent1 = population[random1];                                          // wybór pierwszego, losowego rodzica z wybranych osobników
            parent2 = population[random2];                                          // wybór drugiego, losowego rodzica z wybranych osobników

            if ((rand()/(double)RAND_MAX) < wsp_krzyzowania) {                              // jeśli losowa liczba z przedziału 0-1 będzie mniejsza niż współczynnik krzyżowania
                if(crossover_method == "SPC") {
                    child1 = single_point_crossover(child1, parent1, parent2);                // utworzony z krzyżowania pierwszy potomek
                    child2 = single_point_crossover(child2, parent2, parent1);                // utworzony z krzyżowania drugi potomek
                } else if(crossover_method == "CC") {
                    child1 = cycle_crossover(child1, parent1, parent2);                       // utworzony z krzyżowania pierwszy potomek
                    child2 = cycle_crossover(child2, parent2, parent1);                       // utworzony z krzyżowania drugi potomek
                }
            } else {                                                                        // w przeciwnym razie dzieci to rodzice
                for (int g = 0; g < cities_number; g++) {
                    child1[g] = parent1[g];
                    child2[g] = parent2[g];
                }
            }

            if ((rand()/(double)RAND_MAX) < wsp_mutacji) {                  // jeśli losowa liczba z przedziału 0-1 będzie mniejsza niż współczynnik mutacji
                if(mutation_method == "swap") {
                    child1 = mutation_swap(child1);                                               // pierwszy potomek po mutacji
                    child2 = mutation_swap(child2);                                               // drugi potomek po mutacji
                } else if(mutation_method == "insert") {
                    child1 = mutation_insert(child1);                                             // pierwszy potomek po mutacji
                    child2 = mutation_insert(child2);                                             // drugi potomek po mutacji
                }
            }

            for(int g=0; g<cities_number; g++) {                                    // dodawanie potomków do nowej populacji
                new_population[i*2][g] = child1[g];
                new_population[i*2+1][g] = child2[g];
            }
        }

        sortowanie_quicksort(distance_matrix, population_size);             // sortowanie tablicy distance_matrix po długości ścieżek

        if(distance_matrix[0][1] < best_distance) {
            QueryPerformanceCounter(&end);
            bestElapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;              // w sekundach

            best_distance = distance_matrix[0][1];
            // cout << best_distance << endl;
            for(int i=0; i<cities_number; i++) {
                best_permutation[i] = population[distance_matrix[0][0]][i];
            }
        }

        for(int i=0; i<chosen_size; i++) {                                  // wybranymi osobnikami jest najlepsze 20% populacji
            chosen_permutation_from_population.push_back(population[distance_matrix[i][0]]);
        }

        for(int i=0; i<chosen_size; i++) {                                  // po dodaniu potomków do nowej populacji, dodawane są wybrane osobniki (20% najlepszych rodziców)
            for(int j=0; j<cities_number; j++) {
                new_population[i + population_size - chosen_size][j] = chosen_permutation_from_population[i][j];
            }
        }

        for(int i=0; i<population_size; i++) {                              // zapisywanie nowej populacji, jako głównej populacji
            for(int j=0; j<cities_number; j++) {
                population[i][j] = new_population[i][j];
            }
        }

        chosen_permutation_from_population.clear();                             // na koniec wykonuje się czyszczenie tablicy wybranych osobników

        QueryPerformanceCounter(&end);
        elapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;              // w sekundach
    }

    cout << "Najlepsza znaleziona sciezka: ";
    for(int i=0; i<cities_number; i++) {
        cout << best_permutation[i] << " ";
    } cout << best_permutation[0] << endl;
    cout << "Dlugosc najlepszej znalezionej sciezki: " << best_distance << endl;
    cout << "Czas znalezienia najlepszej sciezki: " << bestElapsedTime << " sek" << endl;

    if(crossover_method == "SPC") {
        crossover_method_name = "Single Point";
    } else if(crossover_method == "CC") {
        crossover_method_name = "Cycle";
    }

    // --------------------------------------------------------------------------------- Zapisywanie wyników
    ofstream results_file;
    results_file.open("Genetic_Algorithm_Results_All.csv", ios::app);                                                                                // zapisywanie wyników do pliku

    results_file << cities_number << ";" << population_size << ";" << wsp_krzyzowania << ";" << wsp_mutacji << ";" << crossover_method_name << ";" << mutation_method << ";" << best_distance << ";" << bestElapsedTime << ";";
    for(int i=0; i<cities_number; i++) {
        results_file << best_permutation[i] << " ";
    }
    results_file << best_permutation[0] << endl;
    results_file.close();

    if(load_file_name == "ftv47") {
        ofstream results_file;
        results_file.open("Genetic_Algorithm_Results_ftv47_best_2.csv", ios::app);                                                                                // zapisywanie wyników do pliku

        results_file << cities_number << ";" << population_size << ";" << wsp_krzyzowania << ";" << wsp_mutacji << ";" << crossover_method_name << ";" << mutation_method << ";" << best_distance << ";" << bestElapsedTime << ";";
        for(int i=0; i<cities_number; i++) {
            results_file << best_permutation[i] << " ";
        }
        results_file << best_permutation[0] << endl;
        results_file.close();
    } else if(load_file_name == "ftv170") {
        ofstream results_file;
        results_file.open("Genetic_Algorithm_Results_ftv170_best_2.csv", ios::app);                                                                                // zapisywanie wyników do pliku

        results_file << cities_number << ";" << population_size << ";" << wsp_krzyzowania << ";" << wsp_mutacji << ";" << crossover_method_name << ";" << mutation_method << ";" << best_distance << ";" << bestElapsedTime << ";";
        for(int i=0; i<cities_number; i++) {
            results_file << best_permutation[i] << " ";
        }
        results_file << best_permutation[0] << endl;
        results_file.close();
    } else if(load_file_name == "rbg403") {
        ofstream results_file;
        results_file.open("Genetic_Algorithm_Results_rbg403_best_2.csv", ios::app);                                                                                // zapisywanie wyników do pliku

        results_file << cities_number << ";" << population_size << ";" << wsp_krzyzowania << ";" << wsp_mutacji << ";" << crossover_method_name << ";" << mutation_method << ";" << best_distance << ";" << bestElapsedTime << ";";
        for(int i=0; i<cities_number; i++) {
            results_file << best_permutation[i] << " ";
        }
        results_file << best_permutation[0] << endl;
        results_file.close();
    }
    // -----------------------------------------------------------------------------------

    for(int i=0; i < population_size; i++) {
        delete[] population[i];
    }
    delete[] population;

    for(int i=0; i < population_size; i++) {
        delete[] new_population[i];
    }
    delete[] new_population;

    for(int i=0; i < population_size; i++) {
        delete[] distance_matrix[i];
    }
    delete[] distance_matrix;

    delete [] child1;
    delete [] child2;
    delete [] best_permutation;
}

int** Genetic_algorithm::generate_first_population(int** population, int population_size) {         // funkcja generująca początkową populacje
    // struct timespec ts;
    // clock_gettime(CLOCK_MONOTONIC, &ts);                                                    // CLOCK_MONOTONIC gwarantuje stały wzrost czasu
    // srand(ts.tv_nsec ^ ts.tv_sec);
    //
    // for(int i = 0; i < population_size; i++) {
    //     for(int j = 0; j < cities_number; j++) {
    //         population[i][j] = j;
    //     }
    //
    //     for (int j = cities_number - 1; j >= 0; j--) {                                              // zamiana miejscami elementów w permutacji, aby otrzymać różne, losowe permutacje w populacji
    //         int rd = rand() % (j + 1);
    //         swap(population[i][j], population[i][rd]);
    //     }
    // }


    for(int i=0; i<population_size; i++) {
        NearestNeighbour *nn = new NearestNeighbour(matrix, cities_number);
        int *permutation = nn->algorithm_nn(i);

        for(int j = 0; j < cities_number; j++) {
            population[i][j] = permutation[j];
        }
        delete[] permutation;
        delete nn;
    }

    return population;
}

int Genetic_algorithm::rate_function(int* permutation) {                                            // funkcja oceny permutacji (wylicza długość ścieżki)
    int sum = 0;

    for(int i = 0; i<cities_number-1; i++) {
        sum += matrix[permutation[i]][permutation[i+1]];
    }
    sum += matrix[permutation[cities_number-1]][permutation[0]];

    return sum;
}

int* Genetic_algorithm::single_point_crossover(int* child, int* parent1, int* parent2) {                       // metoda krzyżowania - Single Point Crossover
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);                                                    // CLOCK_MONOTONIC gwarantuje stały wzrost czasu
    srand(ts.tv_nsec ^ ts.tv_sec);

    int point = rand()%cities_number;

    for(int i = 0; i < point; i++) {
        child[i] = parent1[i];
    }

    int pom = point;

    for(int i = 0; i < cities_number; i++) {                                                    // unikanie duplikatów
        bool exists = false;
        for(int j=0; j<point; j++) {
            if(parent2[i] == child[j]) {
                exists = true;
                break;
            }
        }
        if(!exists) {
            child[pom] = parent2[i];
            pom++;
        }
    }

    return child;
}

int* Genetic_algorithm::cycle_crossover(int* child, int* parent1, int* parent2) {                       // metoda krzyżowania - Cycle Crossover
    int pos_in_parent2 = 1;
    int value_in_parent1 = parent1[0];
    bool* visited = new bool[cities_number];
    for(int i = 0; i < cities_number; i++) {
        visited[i] = false;
    }

    child[0] = parent1[0];
    visited[0] = true;

    while(pos_in_parent2 != 0) {
        for(int i = 0; i < cities_number; i++) {
            if(parent2[i] == value_in_parent1) {
                pos_in_parent2 = i;
                break;
            }
        }
        value_in_parent1 = parent1[pos_in_parent2];
        child[pos_in_parent2] = value_in_parent1;
        visited[pos_in_parent2] = true;
    }

    for(int i = 0; i < cities_number; i++) {
        if(!visited[i]) {
            child[i] = parent2[i];
        }
    }

    delete[] visited;
    return child;
}

int* Genetic_algorithm::mutation_swap(int* child) {                                                 // metoda mutacji - swap
    int point1 = rand()%cities_number;
    int point2;
    do {
        point2 = rand()%cities_number;
    } while(point1 == point2);

    swap(child[point1], child[point2]);

    return child;
}

int* Genetic_algorithm::mutation_insert(int* child) {                                                 // metoda mutacji - swap
    int from_index = rand()%cities_number;                                                            // indeks, z którego przenosimy miasto
    int to_index;                                                                                     // indeks, w miejsce którego przenosimy miasto
    do {
        to_index = rand()%cities_number;
    } while(from_index == to_index);


    int city = child[from_index];

    if(from_index < to_index) {
        for(int i=from_index; i<to_index; i++) {
            child[i] = child[i+1];
        }
    } else {
        for(int i=from_index; i>to_index; i--) {
            child[i] = child[i-1];
        }
    }

    child[to_index] = city;

    return child;
}

int Genetic_algorithm::tournament_selection(int population_size, int** distance_matrix) {     // funkcja wyboru rodzica poprzez turniej
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);                                                    // CLOCK_MONOTONIC gwarantuje stały wzrost czasu
    srand(ts.tv_nsec ^ ts.tv_sec);

    int best_distance = INT_MAX; ;
    int best_candidate_index = -1;

    for (int i = 0; i < 2; i++) {                                                                   // w trunieju porównywanych jest 3 osobników
        int candidate = rand() % population_size;                                                   // losowanie z całej populacji
        if (distance_matrix[candidate][1] < best_distance) {                                        // Wyższy fitness oznacza lepszego kandydata
            best_candidate_index = candidate;
            best_distance = distance_matrix[candidate][1];
        }
    }

    return best_candidate_index;
}
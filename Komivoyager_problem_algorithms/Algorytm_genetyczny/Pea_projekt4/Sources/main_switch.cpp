//
// Created by mateu on 12.01.2025.
//

#include "main_switch.h"
#include <utility>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include "genetic_algorithm.h"
#include "load.h"
#include "measurements.h"

using namespace std;

void delete_matrix(int **&, int);
void load_conf_file(int**&);

void main_switch(int**& matrix, string load_file_name, double wsp_krzyzowania, double wsp_mutacji, string crossover_method, string mutation_method, int stop_time, int population_size) {
    pair<int**, int> data = load_data(load_file_name);

    matrix = data.first;
    int cities_number = data.second;

    Genetic_algorithm *gen_alg = new Genetic_algorithm(matrix, cities_number, wsp_krzyzowania, wsp_mutacji, crossover_method, mutation_method, stop_time, population_size, load_file_name);
    gen_alg->geneticAlgorithm();
    delete gen_alg;

    // thread thread1(measure_ftv47);
    // thread thread2(measure_ftv170);
    // thread thread3(measure_rbg403);
    // thread thread1(measure_ftv47_for_best_population_size);
    // thread thread2(measure_ftv170_for_best_population_size);
    // thread thread3(measure_rbg403_for_best_population_size);

    // thread1.join();                                            // oczekiwanie na zakończenie wątków
    // thread2.join();
    // thread3.join();
}

void load_conf_file(int**& matrix) {
    ifstream conf_file;
    conf_file.open("conf.txt");                               // otwieranie pliku konfiguracyjnego

    string load_file_name = "";                                 // zmienna przechowująca nazwę pliku, z którego wczytywane są dane
    double wsp_krzyzowania = 0.0;                               // zmienna przechowująca współczynnik krzyżowania
    double wsp_mutacji = 0.0;                                   // zmienna przechowująca współczynnik mutacji
    string crossover_method = "";                               // zmienna przechowująca nazwę metody krzyżowania, która ma zostać wykonana
    string mutation_method = "";                                // zmienna przechowująca nazwę metody mutacji, która ma zostać wykonana
    int stop_time = 1;                                          // zmienna przechowująca czas, po ktorym program zakończy działanie - kryterium stopu (w sekundach)
    int population_size = 0;                                    // zmienna przechowująca wielkość populacji

    if(conf_file.good()==false) {                               // jeśli plik się nie otworzył
        cout << "Błąd" << endl;
    } else {
        string line;
        int line_number = 1;

        while(getline(conf_file, line)) {
            if(line_number == 4) {
                stringstream ss;                                // stringstream to typ danych, który pozwala na łatwe konwertowanie danych np. z string na int
                ss << line;
                ss >> load_file_name;
                ss.clear();                                     // czyszczenie ss
            }
            if(line_number == 7) {
                stringstream ss;
                ss << line;
                ss >> wsp_krzyzowania;
                ss.clear();
            }
            if(line_number == 10) {
                stringstream ss;
                ss << line;
                ss >> wsp_mutacji;
                ss.clear();
            }
            if(line_number == 13) {
                stringstream ss;
                ss << line;
                ss >> crossover_method;
                ss.clear();
            }
            if(line_number == 16) {
                stringstream ss;
                ss << line;
                ss >> mutation_method;
                ss.clear();
            }
            if(line_number == 19) {
                stringstream ss;
                ss << line;
                ss >> stop_time;
                ss.clear();
            }
            if(line_number == 22) {
                stringstream ss;
                ss << line;
                ss >> population_size;
                ss.clear();
            }

            line_number++;
        }
    }

    conf_file.close();

    main_switch(matrix, load_file_name, wsp_krzyzowania, wsp_mutacji, crossover_method, mutation_method, stop_time, population_size);
}

void delete_matrix(int**& matrix, int cities_number) {       // usuwanie macierzy, o ile już istnieje, referencja do wskaźnika aby móć zmieniać sam wskaźnik
    if(matrix != nullptr) {
        for(int i = 0; i < cities_number; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}
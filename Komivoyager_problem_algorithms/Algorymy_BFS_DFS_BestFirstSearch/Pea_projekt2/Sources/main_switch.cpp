//
// Created by mateu on 03.11.2024.
//

#include "main_switch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "load.h"
#include "generate.h"
#include "best_first_search.h"
#include "best_first_search_sym.h"
#include "breadth_first_search.h"
#include "breadth_first_search_sym.h"
#include "depth_first_search.h"
#include "depth_first_search_sym.h"

using namespace std;

int cities_number;                                           // liczba miast

void delete_matrix(int**& matrix, int cities_number) {       // usuwanie macierzy, o ile już istnieje, referencja do wskaźnika aby móć zmieniać sam wskaźnik
    if(matrix != nullptr) {
        for(int i = 0; i < cities_number; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

void load_conf_file(int**& matrix, int*& sym_array) {
    ifstream conf_file;
    conf_file.open("conf.txt");                               // otwieranie pliku konfiguracyjnego

    int load_or_generate = 0;                                   // zmienna przechowująca wartość mówiącą czy dane będą generowane czy wczytywane z pliku (1 - wczytywanie, 2 - generowanie)
    string load_file_name = "";                                 // zmienna przechowująca nazwę pliku, z którego wczytywane są dane
    int display_matrix = 0;                                     // zmienna przechowująca wartość mówiącą, czy macierz zostanie wyświetlona, czy nie (0 - nie, 1 - tak)
    int algorithm = 0;                                          // zmienna przechowująca wartość mówiącą, który algorytm zostanie wykorzystany (1 - BFS, 2 - DFS, 3 - BestFS)
    int for_report = 0;                                         // zmienna przechowująca wartość mówiącą, czy mają wykonać się pomiary do sprawozdania

    if(conf_file.good()==false) {                               // jeśli plik się nie otworzył
        cout << "Błąd" << endl;
    } else {
        string line;
        int line_number = 1;

        while(getline(conf_file, line)) {
            if(line_number == 2) {
                stringstream ss;                                // stringstream to typ danych, który pozwala na łatwe konwertowanie danych np. z string na int
                ss << line;
                ss >> load_or_generate;
                ss.clear();                                     // czyszczenie ss
            }
            if(line_number == 5) {
                stringstream ss;
                ss << line;
                ss >> load_file_name;
                ss.clear();
            }
            if(line_number == 8) {
                stringstream ss;
                ss << line;
                ss >> display_matrix;
                ss.clear();
            }
            if(line_number == 11) {
                if(load_or_generate == 2 || load_or_generate == 3) {    // jeśli dane będą generowane, a nie wczytywane
                    stringstream ss;
                    ss << line;
                    ss >> cities_number;
                    ss.clear();
                }
            }
            if(line_number == 14) {
                stringstream ss;
                ss << line;
                ss >> algorithm;
                ss.clear();
            }
            if(line_number == 17) {
                stringstream ss;
                ss << line;
                ss >> for_report;
                ss.clear();
            }

            line_number++;
        }
    }

    conf_file.close();

    main_switch(matrix, sym_array, load_or_generate, load_file_name, display_matrix, algorithm, for_report);
}

void main_switch(int**& matrix, int*& sym_array, int load_or_generate, string load_file_name, int display_matrix, int algorithm, int for_report) {
    switch(load_or_generate) {
        case 1: {
            if(matrix != nullptr || sym_array == nullptr) {                                  // zwalnianie pamięci przed załadowaniem nowego problemu
                delete_matrix(matrix, cities_number);
                delete[] sym_array;
            }

            matrix = generate_loaded_matrix(load_file_name);
            cities_number = getCitiesNumber_l();

            break;
        }
        case 2: {
            if(matrix != nullptr || sym_array == nullptr) {                                  // zwalnianie pamięci przed załadowaniem nowego problemu
                delete_matrix(matrix, cities_number);
                delete[] sym_array;
            }

            matrix = generate_random_asymmetric_matrix(cities_number);
            break;
        }
        case 3: {
            if(matrix != nullptr || sym_array == nullptr) {                                  // zwalnianie pamięci przed załadowaniem nowego problemu
                delete_matrix(matrix, cities_number);
                delete[] sym_array;
            }

            // matrix = generate_random_symmetric_matrix(cities_number);
            sym_array = generate_random_symmetric_matrix(cities_number);
            break;
        }
        default: {
            cout << "Błąd" << endl;
            break;
        }
    }

    if(display_matrix == 1) {
        if(load_or_generate == 1 || load_or_generate == 2) {
            if(matrix != nullptr) {
                cout << "MACIERZ ASYMETRYCZNA MIAST:" << endl << endl;
                for(int i=0; i<cities_number; i++) {
                    for(int j=0; j<cities_number; j++) {
                        cout << setw(3) << matrix[i][j] << " ";
                    }
                    cout << endl;
                }
            }
            else {
                cout << "Zaden problem nie istnieje" << endl;
            }
        } else {
            if(sym_array != nullptr) {
                cout << "MACIERZ SYMETRYCZNA MIAST - TABLICA:" << endl << endl;
                cout << "[ ";
                for(int i=0; i<(cities_number*(cities_number-1))/2; i++) {
                    cout << setw(3) << sym_array[i] << " ";
                }
                cout << " ]" << endl;
            }
        }
    }

    if(load_or_generate == 1 || load_or_generate == 2) {
        switch(algorithm) {
            case 1: {
                Breadth_first_search *BFS_class = new Breadth_first_search(matrix, cities_number);
                BFS_class->BFS_algorithm();
                delete BFS_class;
                break;
            }
            case 2: {
                Depth_first_search *DFS_class = new Depth_first_search(matrix, cities_number);
                DFS_class->DFS_algorithm();
                delete DFS_class;
                break;
            }
            case 3: {
                Best_first_search *BestFS_class = new Best_first_search(matrix, cities_number);
                BestFS_class->BFS_algorithm();
                delete BestFS_class;
                break;
            }
            default: {
                cout << "Błąd" << endl;
                break;
            }
        }
    } else {
        switch(algorithm) {
            case 1: {
                Breadth_first_search_sym *BFS_sym_class = new Breadth_first_search_sym(sym_array, cities_number);
                BFS_sym_class->BFS_algorithm();
                delete BFS_sym_class;
                break;
            }
            case 2: {
                Depth_first_search_sym *DFS_sym_class = new Depth_first_search_sym(sym_array, cities_number);
                DFS_sym_class->DFS_algorithm();
                delete DFS_sym_class;
                break;
            }
            case 3: {
                Best_first_search_sym *BestFS_sym_class = new Best_first_search_sym(sym_array, cities_number);
                BestFS_sym_class->BFS_algorithm();
                delete BestFS_sym_class;

                break;
            }
            default: {
                cout << "Błąd" << endl;
                break;
            }
        }
    }

    if(for_report == 1 && (load_or_generate == 1 || load_or_generate == 2)) {                                               // pomiary do sprawozdania
        ofstream plik_wynikowy;                                         // generowanie danych i wyników do sprawozdania
        plik_wynikowy.open("final_results_PEA2.csv", ios::app);

        for(int i=0; i<100; i++) {
            matrix = generate_random_asymmetric_matrix(cities_number);

            Breadth_first_search *BFS_class = new Breadth_first_search(matrix, cities_number);
            BFS_class->BFS_algorithm();
            double time1 = BFS_class->getElapsedTime()*1e3;
            // cout << time1 << endl;
            delete BFS_class;

            Depth_first_search *DFS_class = new Depth_first_search(matrix, cities_number);
            DFS_class->DFS_algorithm();
            double time2 = DFS_class->getElapsedTime()*1e3;
            // cout << time2 << endl;
            delete DFS_class;

            Best_first_search *BestFS_class = new Best_first_search(matrix, cities_number);
            BestFS_class->BFS_algorithm();
            double time3 = BestFS_class->getElapsedTime()*1e3;
            // cout << time3 << endl;
            delete BestFS_class;

            plik_wynikowy << time1 << ";" << time2 << ";" << time3 << endl;

            if(matrix != nullptr) {                                  // zwalnianie pamięci
                delete_matrix(matrix, cities_number);
            }
        }

        plik_wynikowy.close();
    } else if(for_report == 1 && load_or_generate == 3) {
        ofstream plik_wynikowy;                                         // generowanie danych i wyników do sprawozdania
        plik_wynikowy.open("final_SYM__results_PEA2.csv", ios::app);

        for(int i=0; i<100; i++) {
            sym_array = generate_random_symmetric_matrix(cities_number);

            Breadth_first_search_sym *BFS_sym_class = new Breadth_first_search_sym(sym_array, cities_number);
            BFS_sym_class->BFS_algorithm();
            double time1 = BFS_sym_class->getElapsedTime()*1e3;
            // cout << time1 << endl;
            delete BFS_sym_class;

            Depth_first_search_sym *DFS_sym_class = new Depth_first_search_sym(sym_array, cities_number);
            DFS_sym_class->DFS_algorithm();
            double time2 = DFS_sym_class->getElapsedTime()*1e3;
            // cout << time2 << endl;
            delete DFS_sym_class;

            Best_first_search_sym *BestFS_sym_class = new Best_first_search_sym(sym_array, cities_number);
            BestFS_sym_class->BFS_algorithm();
            double time3 = BestFS_sym_class->getElapsedTime()*1e3;
            // cout << time3 << endl;
            delete BestFS_sym_class;

            plik_wynikowy << time1 << ";" << time2 << ";" << time3 << endl;

            if(matrix != nullptr) {                                  // zwalnianie pamięci
                delete_matrix(matrix, cities_number);
            }
        }

        plik_wynikowy.close();
    }

    if(matrix != nullptr || sym_array != nullptr) {                                  // zwalnianie pamięci przed wyjściem z programu
        delete_matrix(matrix, cities_number);
        delete[] sym_array;
    }
}

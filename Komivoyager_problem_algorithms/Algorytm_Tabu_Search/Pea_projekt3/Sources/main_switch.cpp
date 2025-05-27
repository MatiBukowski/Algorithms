//
// Created by mateu on 13.12.2024.
//
#include "load.h"
#include "tabu_search.h"
#include <utility>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void delete_matrix(int **&, int);
void load_conf_file(int**&);

void main_switch(int**& matrix, string load_file_name, int kadencja, string move_name, int stop_criterion, int iterations_number, int stop_time, int criticalEvent_par) {     // funkcja wyboru algorytmów
    pair<int**, int> data = load_data(load_file_name);

    matrix = data.first;
    int cities_number = data.second;

    Tabu_search *ts = new Tabu_search(matrix, cities_number, kadencja, move_name, criticalEvent_par);
    ts->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    delete ts;

    // -------------------------------------------------
    // Tabu_search *ts1 = new Tabu_search(matrix, cities_number, 202, "swap", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts1->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts1;
    // Tabu_search *ts2 = new Tabu_search(matrix, cities_number, 202, "swap", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts2->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts2;
    // Tabu_search *ts15 = new Tabu_search(matrix, cities_number, 403, "swap", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts15->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts15;
    // Tabu_search *ts16 = new Tabu_search(matrix, cities_number, 403, "swap", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts16->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts16;
    // Tabu_search *ts17 = new Tabu_search(matrix, cities_number, 806, "swap", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts17->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts17;
    // Tabu_search *ts18 = new Tabu_search(matrix, cities_number, 806, "swap", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts18->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts18;

    // ---------------------------------------------------
    // Tabu_search *ts3 = new Tabu_search(matrix, cities_number, 202, "invert", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts3->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts3;
    // Tabu_search *ts4 = new Tabu_search(matrix, cities_number, 202, "invert", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts4->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts4;
    // Tabu_search *ts5 = new Tabu_search(matrix, cities_number, 403, "invert", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts5->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts5;
    // Tabu_search *ts6 = new Tabu_search(matrix, cities_number, 403, "invert", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts6->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts6;
    // Tabu_search *ts7 = new Tabu_search(matrix, cities_number, 806, "invert", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts7->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts7;
    // Tabu_search *ts8 = new Tabu_search(matrix, cities_number, 806, "invert", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts8->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts8;

    //------------------------------------------------------------------------------

    // Tabu_search *ts9 = new Tabu_search(matrix, cities_number, 202, "insert", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts9->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts9;
    // Tabu_search *ts10 = new Tabu_search(matrix, cities_number, 202, "insert", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts10->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts10;
    // Tabu_search *ts11 = new Tabu_search(matrix, cities_number, 403, "insert", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts11->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts11;
    // Tabu_search *ts12 = new Tabu_search(matrix, cities_number, 403, "insert", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts12->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts12;
    // Tabu_search *ts13 = new Tabu_search(matrix, cities_number, 806, "insert", 2);
    //
    // for(int i=0; i<10; i++) {
    //     ts13->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts13;
    // Tabu_search *ts14 = new Tabu_search(matrix, cities_number, 806, "insert", 7);
    //
    // for(int i=0; i<10; i++) {
    //     ts14->tabu_algorithm(stop_criterion, iterations_number, stop_time);
    // }
    // delete ts14;

    if(matrix != nullptr) {                                  // zwalnianie pamięci przed wyjściem z programu
        delete_matrix(matrix, cities_number);
    }
}

void load_conf_file(int**& matrix) {
    ifstream conf_file;
    conf_file.open("conf.txt");                               // otwieranie pliku konfiguracyjnego

    string load_file_name = "";                                 // zmienna przechowująca nazwę pliku, z którego wczytywane są dane
    int kadencja = 0;                                           // kadencja (czas zakazu ruchu):
    string move_name = "";                                      // zmienna przechowująca nazwę ruchu, który ma być wykonywany
    int stop_criterion = 0;                                     // zmienna przechowująca rodzaj kryterium stopu
    int iterations_number = 1;                                  // zmienna przechowująca liczbę iteracji, po ktorej program zakończy działanie - kryterium stopu
    int stop_time = 1;                                          // zmienna przechowująca czas, po ktorym program zakończy działanie - kryterium stopu
    int criticalEvent_par = 0;                                  // zmienna przechowująca ilość nielepszych wyników, dla których wygeneruje się nowa bazowa ścieżka - dla strategii dywersyfikacji

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
                ss >> kadencja;
                ss.clear();
            }
            if(line_number == 10) {
                stringstream ss;
                ss << line;
                ss >> move_name;
                ss.clear();
            }
            if(line_number == 13) {
                stringstream ss;
                ss << line;
                ss >> stop_criterion;
                ss.clear();
            }
            if(stop_criterion == 1) {
                if(line_number == 16) {
                    stringstream ss;
                    ss << line;
                    ss >> iterations_number;
                    ss.clear();
                }
            } else if(stop_criterion == 2) {
                if(line_number == 19) {
                    stringstream ss;
                    ss << line;
                    ss >> stop_time;
                    ss.clear();
                }
            }
            if(line_number == 22) {
                stringstream ss;
                ss << line;
                ss >> criticalEvent_par;
                ss.clear();
            }

            line_number++;
        }
    }

    conf_file.close();

    main_switch(matrix, load_file_name, kadencja, move_name, stop_criterion, iterations_number, stop_time, criticalEvent_par);
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
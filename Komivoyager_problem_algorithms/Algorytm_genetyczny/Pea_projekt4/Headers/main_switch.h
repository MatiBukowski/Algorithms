//
// Created by mateu on 12.01.2025.
//

#ifndef MAIN_SWITCH_H
#define MAIN_SWITCH_H
#include <string>

void main_switch(int**&, std::string, double, double, std::string, std::string, int, int);              // funkcja wyboru algorytmów
void load_conf_file(int**&);                                                                            // funkcja wczytująca plik konfiguracyjny
void delete_matrix(int**&, int);

#endif //MAIN_SWITCH_H

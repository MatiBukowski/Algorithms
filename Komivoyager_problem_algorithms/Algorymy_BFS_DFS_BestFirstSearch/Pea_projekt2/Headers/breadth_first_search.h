//
// Created by mateu on 08.11.2024.
//

#include "node.h"

#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

class Breadth_first_search {
    int **matrix;
    int cities_number;                                  // liczba miast
    int nodes_amount;                                   // liczba węzłów
    double elapsedTime1;                                // czas wykonywania się algorytmu


    public:
    Breadth_first_search(int**, int);
    ~Breadth_first_search();
    int search_bound(int, int, bool*, int);             // funkcja obliczająca dolną granicę dla częściowej trasy
    void BFS_algorithm();
    Node** add_to_array(Node**, Node*, int&);           // funkcja dodająca nowy węzeł grafu do tablicy dynamicznej
    Node** remove_first_from_array(Node**, int&);           // funkcja usuwająca najlpeszy węzeł grafu z tablicy dynamicznej
    double getElapsedTime();
};
#endif //BREADTH_FIRST_SEARCH_H

//
// Created by mateu on 15.11.2024.
//
#include "node.h"

#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

class Depth_first_search {
    int **matrix;
    int cities_number;                                  // liczba miast
    int nodes_amount;                                   // liczba węzłów
    double elapsedTime1;                                // czas wykonywania się algorytmu


public:
    Depth_first_search(int**, int);
    ~Depth_first_search();
    int search_bound(int, int, bool*, int);             // funkcja obliczająca dolną granicę dla częściowej trasy
    void DFS_algorithm();
    Node** add_to_array(Node**, Node*, int&);           // funkcja dodająca nowy węzeł grafu do tablicy dynamicznej
    Node** remove_top_from_array(Node**, int&);           // funkcja usuwająca najlpeszy węzeł grafu z tablicy dynamicznej
    double getElapsedTime();
};

#endif //DEPTH_FIRST_SEARCH_H

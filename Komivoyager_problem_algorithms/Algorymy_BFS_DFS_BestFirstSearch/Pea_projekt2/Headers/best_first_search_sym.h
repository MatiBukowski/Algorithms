//
// Created by mateu on 25.11.2024.
//

#include "node.h"

#ifndef BEST_FIRST_SEARCH_SYM_H
#define BEST_FIRST_SEARCH_SYM_H
class Best_first_search_sym {
    int *sym_array;
    int cities_number;                                  // liczba miast
    int nodes_amount;                                   // liczba węzłów
    double elapsedTime1;                                // czas wykonywania się algorytmu

public:
    Best_first_search_sym(int*, int);
    ~Best_first_search_sym();
    int search_bound(int, int, bool*, int);             // funkcja obliczająca dolną granicę dla częściowej trasy
    void BFS_algorithm();
    void heap_making(Node**, int);                      // funkcja tworząca kopiec
    void heap(Node**, int, int);                        // funkcja przywracająca kopiec po dodaniu elementu
    Node** add_to_array(Node**, Node*, int&);           // funkcja dodająca nowy węzeł grafu do tablicy dynamicznej
    Node** remove_best_from_array(Node**, int&);           // funkcja usuwająca najlpeszy węzeł grafu z tablicy dynamicznej
    double getElapsedTime();
};
#endif //BEST_FIRST_SEARCH_SYM_H

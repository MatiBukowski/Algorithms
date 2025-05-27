//
// Created by mateu on 13.12.2024.
//

#ifndef NEAREST_NEIGHBOUR_H
#define NEAREST_NEIGHBOUR_H

class NearestNeighbour {                                        // klasa algorytmu najbliższego sąsiada
    int **matrix;                                               // macierz długości dróg między miastami
    int cities_number;                                          // ilość miast badanego problemu
    int final_sum_path=100000;                                  // łączna droga w problemie komiwojażera

public:
    NearestNeighbour(int**, int);                               // konstruktor
    ~NearestNeighbour();                                        // destruktor
    int* algorithm_nn(int);                                     // główna metoda algorytmu
    int findNearestNeighbour(bool*, int);                       // metoda szukająca najbliższego, nieodwiedzonego sąsiada dla danego miasta
    int getFinalSumPathNN();                                    // metoda zwracająca całkowitą, końcową długość ścieżki
};

#endif //NEAREST_NEIGHBOUR_H

//
// Created by mateu on 11.10.2024.
//

#ifndef NEAREST_NEIGHBOUR_H
#define NEAREST_NEIGHBOUR_H

class NearestNeighbour {                                        // klasa algorytmu najbliższego sąsiada
    int **matrix;                                               // macierz długości dróg między miastami
    int cities_number;                                          // ilość miast badanego problemu
    int final_sum_path=100000;                                  // łączna droga w problemie komiwojażera
    double elapsedTime1;                                        // czas wykonywania się algorytmu

    public:
    NearestNeighbour(int **matrix, int cities_number);          // konstruktor
    ~NearestNeighbour();                                        // destruktor
    void algorithm_nn();                                        // główna metoda algorytmu
    int findNearestNeighbour(bool*, int);                       // metoda szukająca najbliższego, nieodwiedzonego sąsiada dla danego miasta
    int getFinalSumPathNN();                                    // metoda zwracająca całkowitą, końcową długość ścieżki
    double getElapsedTime();                                   // metoda zwracająca czas wykonywania się programu


};
#endif //NEAREST_NEIGHBOUR_H

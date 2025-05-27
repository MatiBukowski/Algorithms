//
// Created by mateu on 11.10.2024.
//

#ifndef COMPLETE_REVIEW_H
#define COMPLETE_REVIEW_H

class CompleteReview {                                          // klasa lgorytmu przeglądu zupełnego
    int **matrix;                                               // macierz długości dróg między miastami
    int cities_number;                                          // ilość miast badanego problemu
    int final_sum_path=100000;                                  // łączna droga w problemie komiwojażera
    double elapsedTime1;                                        // czas wykonywania się algorytmu

    public:
    CompleteReview(int**, int);
    ~CompleteReview();
    void swap(int&, int&);                                      // funckja zamieniająca miejscami dwie wartości
    void reverse(int*, int, int);                               // funckja zamianiająca miejscami elementy tablicy - na odwórt
    void permutation_generator(int*, int);                      // funkcja generująca wszystkie permutacje zbioru miast
    void algorithm_cr();                                        // główna metoda algorytmu
    int getFinalSumPathCR();                                    // metoda zwracająca całkowitą, końcową długość ścieżki
    double getElapsedTime();                                    // metoda zwracająca czas wykonywania się programu

};
#endif //COMPLETE_REVIEW_H

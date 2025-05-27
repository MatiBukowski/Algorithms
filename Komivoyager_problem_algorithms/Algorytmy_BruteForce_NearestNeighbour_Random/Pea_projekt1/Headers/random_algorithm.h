//
// Created by mateu on 12.10.2024.
//

#ifndef RANDOM_ALGORITHM_H
#define RANDOM_ALGORITHM_H

class RandomAlgorithm {
    int **matrix;                                               // macierz długości dróg między miastami
    int cities_number;                                          // ilość miast badanego problemu
    int final_sum_path=100000;                                  // łączna droga w problemie komiwojażera
    double elapsedTime1;                                        // czas wykonywania się algorytmu


    public:
    RandomAlgorithm(int**, int);
    ~RandomAlgorithm();
    void generate_random_path(int*);                            // tworzenie losowej ścieżki
    void algorithm_ra();                                        // główna metoda algorytmu
    int getFinalSumPathRA();                                    // metoda zwracająca całkowitą, końcową długość ścieżki
    double getElapsedTime();                                   // metoda zwracająca czas wykonywania się programu

};

#endif //RANDOM_ALGORITHM_H

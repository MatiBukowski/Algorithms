//
// Created by mateu on 12.12.2024.
//

#include "tabu_search.h"
#include <iostream>
#include <limits.h>
#include "nearest_neighbour.h"
#include "quicksort.h"
#include "motion_rate_function.h"
#include <ctime>
#include <windows.h>
#include <cmath>
#include <fstream>
#include "moves.h"


using namespace std;

Tabu_search::Tabu_search(int** matrix, int cities_number, int kadencja, string move_name, int criticalEvent_par) {
    this->matrix = matrix;
    this->cities_number = cities_number;
    this->kadencja = kadencja;
    this->move_name = move_name;
    this->criticalEvent_par = criticalEvent_par;
}

Tabu_search::~Tabu_search() {
}

void Tabu_search::tabu_algorithm(int stop_criterion, int iterations_number, int stop_time) {                                // funkcja znajdująca pierwszą permutację algorytmem najbliższych sąsiadów
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceCounter(&start);                                                                                         // rozpoczęcie mierzenia czasu

    NearestNeighbour *nn = new NearestNeighbour(matrix, cities_number);
    int* permutation = nn->algorithm_nn();                      // pierwsza, początkowa permutacja
    int* best_permutation = new int[cities_number];             // najlepsza ścieżka
    int best_distance = nn->getFinalSumPathNN();                // póki co najlepsza długość ścieżki - długość początkowej ścieżki
    int distance = best_distance;                               // długość uszeregowania - długość aktualnej permutacji
    int value = 0;                                              // wartość funckji oceny ruchu
    int* tabu_array;                                            // tablica tabu
    int iteration_number = 0;                                   // liczba iteracji
    int value_counter = 0;                                      // licznik powtórzonych tych samych wartości funkcji oceny ruchu dla kolejnych iteracji
    struct timespec ts;
    float percent_fill_tabu_array = 0;                          // procent zapełnienia tablicy tabu
    double elapsedTime = 0;
    double bestElapsedTime = 0;                                 // czas znalezenia najlepszego znalezionego rozwiązania
    int best_iterations = 0;                                    // numer iteracji najlepszego znalezionego rozwiązania

    for(int i=0; i<cities_number; i++) {
        best_permutation[i] = permutation[i];
    }

    if(move_name == "insert") {
        tabu_array = new int[cities_number*(cities_number-1)];       // tablica tabu - dla inserta wstawianie np. indeksu 5 w miejsce 10 da inny wynik niż wstawnie 10 w 5
        for (int i = 0; i < cities_number*(cities_number-1); i++) {       // wypełneinie tablicy tabu zerami - cities_number*(cities_number-1) - tyle jest możliwych ruchów dla każdej z permutacji dla insert
            tabu_array[i] = 0;
        }
    }
    else {
        tabu_array = new int[cities_number*(cities_number-1)/2];
        for (int i = 0; i < cities_number*(cities_number-1)/2; i++) {       // wypełneinie tablicy tabu zerami - cities_number*(cities_number-1)/2 - tyle jest możliwych ruchów dla każdej z permutacji dla swap i invert
            tabu_array[i] = 0;
        }
    }

    cout << "Pierwsza sciezka znaleziona metoda zachlanna: ";
    for(int i = 0; i < cities_number; i++) {
        cout << permutation[i] << " ";
    } cout << permutation[0] << endl;
    cout << "Dlugosc pierwszej sciezki znalezionej metoda zachlanna: " << distance << endl << endl;

    int** motion_table = new int*[10*cities_number];                        // tworzenie dwuwymiarowej dynamicznej tablicy, która będzie przechowywała wszystkie możliwe ruchy dla danej permutacji oraz wartości funkcji oceny ruchu dla każdego z tych ruchów
    for(int i=0; i<10*cities_number; i++) {
        motion_table[i] = new int[3];
    }

//----------------------------------------------------------------------- początek wykonywania algorytmu - pętla while

    clock_gettime(CLOCK_MONOTONIC, &ts);                            // CLOCK_MONOTONIC gwarantuje stały wzrost czasu
    srand(ts.tv_nsec ^ ts.tv_sec);
    int it = 0;                                                            // liczba iteracji
    double max_it = 380000*stop_time/pow(cities_number, 1.27);
    while((iteration_number < iterations_number && elapsedTime < stop_time) /*&& it < max_it*/) {
        int index1, index2, pom;

        if(move_name == "swap") {
            for(int i=0; i<10*cities_number; i++) {                             // znajduje indeksy do zamiany - sprawdzanie 10*cities_number elementowego sąsiedztwa

                index1 = rand() % cities_number;
                do {                                                            // index1 i index2 nie mogą być równe
                    index2 = rand() % cities_number;
                } while (index2 == index1);

                if(index1 > index2) {                                           // zamiana, aby indeks2 był większy niż indeks1
                    pom = index1;
                    index1 = index2;
                    index2 = pom;
                }

                value = swap_motion_rate_function(matrix, permutation, index1, index2, cities_number);
                motion_table[i][0] = index1;                                    // indeks 1 elementu ruchu (zamiany)
                motion_table[i][1] = index2;                                    // indeks 2 elementu ruchu (zamiany)
                motion_table[i][2] = value;                                     // wartość funkcji oceny ruchu dla danego ruchu
            }
        } else if(move_name == "invert") {
            for(int i=0; i<10*cities_number; i++) {                             // znajduje indeksy do zamiany - sprawdzanie 10*cities_number elementowego sąsiedztwa

                index1 = rand() % cities_number;
                do {                                                            // index1 i index2 nie mogą być równe
                    index2 = rand() % cities_number;
                } while (index2 == index1);

                if(index1 > index2) {                                           // zamiana, aby indeks2 był większy niż indeks1
                    pom = index1;
                    index1 = index2;
                    index2 = pom;
                }

                value = invert_motion_rate_function(matrix, permutation, index1, index2, cities_number);
                motion_table[i][0] = index1;                                    // indeks 1 elementu ruchu
                motion_table[i][1] = index2;                                    // indeks 2 elementu ruchu
                motion_table[i][2] = value;                                     // wartość funkcji oceny ruchu dla danego ruchu
            }
        } else if(move_name == "insert") {
            for(int i=0; i<10*cities_number; i++) {                             // znajduje indeksy do zamiany - sprawdzanie 10*cities_number elementowego sąsiedztwa

                index1 = rand() % cities_number;
                do {                                                            // index1 i index2 nie mogą być równe
                    index2 = rand() % cities_number;
                } while (index2 == index1);

                value = insert_motion_rate_function(matrix, permutation, index1, index2, cities_number);
                motion_table[i][0] = index1;                                    // indeks 1 elementu ruchu
                motion_table[i][1] = index2;                                    // indeks 2 elementu ruchu
                motion_table[i][2] = value;                                     // wartość funkcji oceny ruchu dla danego ruchu
            }
        } else cout << "Niepoprawna nazwa ruchu" << endl;

        sortowanie_quicksort(motion_table, 10*cities_number);              // sortowanie tablicy dwuwymiarowej motion_table po wartościach funkcji oceny ruchu dla każdego sprawdzanego ruchu

        int i1, i2;                                                                                 // indeksy najlepszego ruchu
        int index;                                                                                  // index w tablicy tabu dla danego, najlepszego ruchu
        int pom2 = 0;                                                                               // zmienna pomocnicza - idzie po kolejnych wierszach tablicy tabu
        int distance_pom;

        do {
            i1 = motion_table[pom2][0];
            i2 = motion_table[pom2][1];
            value = motion_table[pom2][2];

            if(move_name == "insert") {
                if(i1 < i2) {
                    index = i1*(cities_number-1)+(i2-1);
                } else if(i1 > i2) {
                    index = i1*(cities_number-1)+i2;
                }
            } else {
                index = ((i2 - 1)*i2)/2+i1;
            }

            distance_pom = distance;
            distance_pom += value;

            pom2++;
        } while (tabu_array[index] != 0 && !aspiration(distance_pom, best_distance));      // jeśli dany ruch nie jest zakazany lub jeśli zakazany ruch daje rozwiązanie lepsze niż dotychczas najlepsze
        // cout << distance << endl;
        // cout << value << endl;

        distance = distance_pom;                                                // zapisywanie nowej wartości uszeregowania - długości ściezki po dokonaniu ruchu

        // wykonanie ruchu
        if(move_name == "swap") {
            swap(permutation[i1], permutation[i2]);
        } else if(move_name == "invert") {
            invert_move(permutation, i1, i2);
        } else if(move_name == "insert") {
            insert_move(permutation, i1, i2);
        }

        if(distance < best_distance) {                                          // jeśli nowa długośc ścieżki jest krótsza od dotychczasowej najlepszej, zapisuje nową najlepszą długość ścieżki
            best_distance = distance;
            for(int i=0; i<cities_number; i++) {
                best_permutation[i] = permutation[i];
            }
            QueryPerformanceCounter(&end);
            bestElapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;              // w sekundach
            best_iterations = it;
        }

        if(move_name == "insert") {
            for (int i = 0; i < cities_number*(cities_number-1); i++) {           // kolejny ruch minął - czas trawnia zakazu ruchów skraca się
                if(tabu_array[i] > 0)
                    tabu_array[i]--;
            }
        } else {
            for (int i = 0; i < cities_number*(cities_number-1)/2; i++) {           // kolejny ruch minął - czas trawnia zakazu ruchów skraca się
                if(tabu_array[i] > 0)
                    tabu_array[i]--;
            }
        }
        tabu_array[index] = kadencja;                                                 // zapisywanie czasu zakazu ruchu dla wykonanego ruchu


        // ------------------------------------------------------------------------------- strategia dywersyfikacji - metoda zdarzeń krytycznych
        if(value > 0)                                                                          // liczy ilość niekorzystnych wartości funckji oceny ruchu pod rząd dla kolejnych iteracji - do strategii dywersyfikacji
            value_counter ++;
        else value_counter = 0;

        bool critical_event = criticalEvent(value_counter);
        if(critical_event) {                                                                       // generowanie nowej permutacji
            permutation = restart(permutation, best_permutation);
            distance=0;
            for(int i=0; i<cities_number-1; i++) {                                                  // wyliczanie długości ścieżki nowej permutacji
                distance += matrix[permutation[i]][permutation[i+1]];
            }
            distance += matrix[permutation[cities_number-1]][permutation[0]];

            if(move_name == "insert") {
                for (int i = 0; i < cities_number*(cities_number-1); i++) {           // kolejny ruch minął - czas trawnia zakazu ruchów skraca się
                    tabu_array[i] = 0;
                }
            } else {
                for (int i = 0; i < cities_number*(cities_number-1)/2; i++) {           // kolejny ruch minął - czas trawnia zakazu ruchów skraca się
                    tabu_array[i] = 0;
                }
            }
        }

        // cout << value_counter << endl;
        // cout << value << endl
        // --------------------------------------------------------------------------

        int tabu_counter = 0;

        if(stop_criterion == 1) {
            iteration_number ++;
        } else if(stop_criterion == 2) {
            QueryPerformanceCounter(&end);

            elapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;              // w sekundach
        }

        it++;
    }

    ofstream results_file;
    results_file.open("Tabu_Search_Results_All.csv", ios::app);                                                                                // zapisywanie wyników do pliku

    results_file << cities_number << ";" << kadencja << ";" << move_name << ";" << criticalEvent_par << ";" << best_distance << ";" << bestElapsedTime << ";" << best_iterations << ";";
    for(int i=0; i<cities_number; i++) {
        results_file << best_permutation[i] << " ";
    }
    results_file << best_permutation[0] << endl;
    results_file.close();

    cout << "Najlepsza znalezniona sciezka: ";
    for(int i=0; i<cities_number; i++) {
        cout << best_permutation[i] << " ";
    } cout << best_permutation[0] << endl;

    // int d = 0;
    // for(int i=0; i<cities_number-1; i++) {
    //     d += matrix[best_permutation[i]][best_permutation[i+1]];
    // }
    // d += matrix[best_permutation[cities_number-1]][best_permutation[0]];

    cout << "Dlugosc najlepszej znalezionej sciezki: "<< best_distance << endl;

    delete nn;
    for(int i = 0; i < 10*cities_number; i++) {        // usuwanie tablicy dwuwymiarowej
        delete[] motion_table[i];
    }
    delete[] motion_table;
    delete[] tabu_array;
    delete[] best_permutation;
    delete[] permutation;

}
                                                                                                // stara częściowa długość ścieżki, która ulegnie zmianie po zamianie miejscami elementów
bool Tabu_search::aspiration(int new_distance, int best_distance) {                             // kryterium aspiracji - pozwala na wykonanie ruchu mimo, że jest zakazany

    if(new_distance < best_distance)
        return true;

    return false;
}

// Strategia dywersyfikacji - metoda zdarzeń krytycznych

bool Tabu_search::criticalEvent(int& value_counter) {                                           // funkcja przyjmuje wartosć TRUE jeżeli zaszły określone warunki wymagające wygenerowania nowego rozwiązania startowego
    if(value_counter >= criticalEvent_par) {
        value_counter = 0;
        return true;
    }

    return false;
}

int* Tabu_search::restart(int* permutation, int* best_permutation) {                                               // funkcja generuje nowe rozwiązanie początkowe - przypisuje dotychcczas najlepsze znalezione rozwiązanie
    for(int i=0; i<cities_number; i++) {
        permutation[i] = best_permutation[i];
    }

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);                    // CLOCK_MONOTONIC gwarantuje stały wzrost czasu
    srand(ts.tv_nsec ^ ts.tv_sec);
    for(int i=0; i<cities_number/20; i++) {                          // wykonanie cities_number/20 losowych swapów
        int index1 = rand() % cities_number;
        int index2 = rand() % cities_number;

        swap(permutation[index1], permutation[index2]);
    }

    return permutation;
}





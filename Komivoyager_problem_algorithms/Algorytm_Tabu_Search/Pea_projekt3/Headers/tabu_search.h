//
// Created by mateu on 12.12.2024.
//

#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H
#include <iostream>

class Tabu_search {                                     // klasa algorytmu tabu_search
    int** matrix;
    int cities_number;
    int kadencja;                                       // kadencja - czas zakazu ruchu dla danych indeksów
    std::string move_name;                              // nazwa wykonywanego ruchu
    int criticalEvent_par;                              //

    public:
    Tabu_search(int**, int, int, std::string, int);
    ~Tabu_search();
    void tabu_algorithm(int, int, int);
    bool aspiration(int, int);                          // kryterium aspiracji

    // Strategia dywersyfikacji - metoda zdarzeń krytycznych
    bool criticalEvent(int&);                           // funkcja przyjmuje wartosć TRUE jeżeli zaszły określone warunki wymagające wygenerowania nowego rozwiązania startowego
    int* restart(int*, int*);                           // funkcja generuje nowe rozwiązanie początkowe - przypisuje dotychcczas najlepsze znalezione rozwiązanie
};
#endif //TABU_SEARCH_H

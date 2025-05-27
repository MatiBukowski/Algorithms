//
// Created by mateu on 08.11.2024.
//

#include "breadth_first_search.h"
#include <iostream>
#include <windows.h>
#include "node.h"
#include <fstream>

using namespace std;

Breadth_first_search::Breadth_first_search(int **Matrix, int Cities_number) {
    matrix = Matrix;
    cities_number = Cities_number;
}

Breadth_first_search::~Breadth_first_search() {}

int Breadth_first_search::search_bound(int current_city, int distance, bool visited[], int first_city) {                     // funkcja obliczająca dolną granicę dla częściowej trasy, distance - koszt dotychczas przebytej drogi
    int bound = distance;                                                                   // granica
    int min_cities_distance = INT_MAX;                                                      // minimalna długość krawędzi wychodząca z obecnego miasta, która jeszcze może być użyta

    for(int i=0; i<cities_number; i++) {                                                    // szukanie najkrotszej mozliwej sciezki wyjscia z obecnego miasta
        if(i != current_city && !visited[i] && matrix[current_city][i] < min_cities_distance) {
            min_cities_distance = matrix[current_city][i];
        }
    }
    if(min_cities_distance != INT_MAX) {                    // jeśli to ostatnie miasto, ktore nie zostalo odwiedzone, to nie znjadzie min_cities_distance i bedzie ono rowne INT_MAX
        bound += min_cities_distance;
        visited[current_city] = true;                       // obecne miasto można uznać za odwiedzone
    }

    for(int i=0; i<cities_number; i++) {                                                    // szukanie najkrotszej mozliwej sciezki wyjscia z kolejnych miast
        if(!visited[i]) {                                                                   // jeśli miasto nei jest odwiedzone
             min_cities_distance = INT_MAX;                                                 // minimalna długość krawędzi wychodząca z obecnego miasta, która jeszcze może być użyta

            for(int j=0; j<cities_number; j++) {
                if(i != j && (!visited[j] || j == first_city) && matrix[i][j] < min_cities_distance) {
                    min_cities_distance = matrix[i][j];
                }
            }
            bound += min_cities_distance;
        }
    }

    return bound;
}

void Breadth_first_search::BFS_algorithm() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceCounter(&start);                                                                            // rozpoczęcie mierzenia czasu

    // int cities_index[cities_number];
    bool *visited = new bool[cities_number];
    int start_city = 0;
    nodes_amount = 1;                                                                                           // liczba wierzchołków grafu
    Node** array = nullptr;                                                                                    // dynamiczna tablica wskaźników na obiekty Node (wierzchołki)
    int level = 0;                                                                                              // poziomów grafu jest tyle ile miast
    int final_distance;                                                                         // końcowa długość całej ścieżki
    // int min_last_level_bound = 0;                                                        // zmienna przechowująca minimalną dolną granicę węzła z ostatniego levelu grafu
    int min_last_level_bound = INT_MAX;                                                        // zmienna przechowująca minimalną dolną granicę węzła z ostatniego levelu grafu
    Node* best_node = nullptr;                                                                 // węzeł z najlepszą ścieżką

    // for(int i=1; i<cities_number; i++) {                                                        // aby usprawnic algorytm na poczatku szukam dlugosc sciezki a->b->c...->a aby zapisać ją w min_last_level_bound
    //     min_last_level_bound += matrix[i-1][i];
    // }
    // min_last_level_bound += matrix[cities_number-1][0];

    for (int i = 0; i < cities_number; i++) {
        // cities_index[i] = i;
        visited[i] = false;
    }

    int bound = search_bound(start_city, 0, visited, start_city);                   // dolna granica obliczona dla korzenia
    Node* root = new Node(level, 0, bound, cities_number, 1);
    root->create_visited_array(visited);                                                                         // dodawanie tablicy visited do obiektu typu Node
    root->add_to_path(start_city);                                                              // dodanie do ścieżki wierzchołka początkowego
    array = add_to_array(array, root, nodes_amount);

    int current_city;                                                           // obecne miasto
    int* current_path;                                                          // wskaźnik na tablice z dotychczasową ścieżką
    int current_distance = 0;                                                      // dystans dotychczasowej ścieżki
    int current_cities_in_path = 0;                                                // ilość miast w obecnej ścieżce
    bool added = false;                                                             // zmienna mówiąca, czy został dodany już węzeł z ostatniego poziomu drzewa

    while(level < cities_number-1) {
        level++;

        if(array[0]->getBound() < min_last_level_bound) {
            for(int i=0; i<cities_number; i++) {

                if(i == 0) {                                                       // wykona się raz na początku pętli for
                    current_city = array[0]->getPathArray()[array[0]->getPathSize() - 1];    // obecne miasto to ostatnie miasto w ścieżce z pierwszego węzła z kolejki
                    current_path = array[0]->getPathArray();                        // zapisuje obecną ścieżke (czyli z pierwszego węzła z kolejki)
                    current_distance = array[0]->getDistance();
                    current_cities_in_path = array[0]->getPathSize();               // ilość wierzchołków w ścieżce w węźle - rodzicu
                }

                if(!visited[i]) {
                    int distance =  matrix[current_city][i] + current_distance;                      // odległość od obecnego miasta do miasta sprawdzanego + dotychczasowa odległość
                    bound = search_bound(i, distance, visited, start_city);
                    Node* new_node = new Node(level, distance, bound, cities_number, current_cities_in_path+1);
                    new_node->create_visited_array(visited);                                                                // dodawanie tablicy visited do obiektu typu Node
                    visited[i] = false;                                                                                     // w funkcji search_bound visited[i] zmienia się na true, jednak później sprawdzane są ścieżki dla i nieodwiedzonego
                    new_node->make_path(current_path);                                                                          // skopiowanie do potomka ścieżki rodzica
                    new_node->add_to_path(i);                                                                            // dodanie do ścieżki nowego miasta
                    // array = add_to_array(array, new_node, nodes_amount);
                    if(level == cities_number - 1 && bound < min_last_level_bound) {    // jesli sprawdzany jest węzeł z ostatniego poziomu i jego granica jest mneijsza niż min_last_level_bound
                        min_last_level_bound = bound;                                   // ustawienie nowej, najniższej granicy węzła z pełną ścieżką
                        best_node = new_node;                                                           // ustawienie nowego, najlepszego węzła
                        if(!added) {                                                    // węzeł z ostatniego poziomu wystarczy dodać raz do tablicy i gdy do niego dojdzie kolej to while konczy działanie (a węzły z ostatniego poziomu są sprawdzane w trakcie szukania potomków rodziców)
                            added = true;
                            array = add_to_array(array, new_node, nodes_amount);
                        }
                    } else if(level != cities_number - 1) {                                     // jeśli węzeł nie jest z ostatniego poziomu
                        array = add_to_array(array, new_node, nodes_amount);                 // dodaj węzeł do tablicy array
                    }
                }

            } // po obliczeniu wszytskich potomków, pierwszy węzełw tablicy jest usuwany - idziemy dalej w kolejce
        }
        // array = remove_first_from_array(array, nodes_amount);                          // usuwa pierwszy węzeł z tablicy, aby nie był już brany pod uwagę w porównaniu

        if(nodes_amount > 1) {                                                  // jeśli tablica array nie jest pusta
            array = remove_first_from_array(array, nodes_amount);                          // usuwa pierwszy węzeł z tablicy, aby nie był już brany pod uwagę w porównaniu
            for(int j=0; j<cities_number; j++) {                                                //  wyciąganie tablicy visited z pierwszego węzła w kolejce
                visited[j] = array[0]->getVisited()[j];
            }

            level = array[0]->getLevel();                                                       // wyciąganie poziomu z pierwszego węzła w kolejce
        }
    }
    // for(int i=0; i<nodes_amount-1; i++) {
    //     for(int j=0; j<array[i]->path.size(); j++) {
    //         cout << array[i]->path[j] << " -> ";
    //     }
    //     cout << endl;
    // }

    // wszystkie węzły zostały zapisane w tablicy, teraz trzeba sprawdzić te, które nadal się w niej znajdują (są to te z ostatniego poziomu)
    // for(int i=0; i<nodes_amount-1; i++) {
    //     if(array[i]->getLevel() == cities_number-1) {                                       // jeśli węzeł jest z ostatniego poziomu (zawieraca całą ścieżkę bez powrotu do początkowego miasta)
    //         if(array[i]->getBound() < min_last_level_bound) {
    //             min_last_level_bound = array[i]->getBound();                                   // ustawienie nowej, najniższej granicy węzła z pełną ścieżką
    //             best_node = array[i];                                                           // ustawienie nowego, najlepszego węzła
    //         }
    //     }
    // }

    current_city = best_node->getPathArray()[best_node->getPathSize() - 1];                                  // obecne miasto, w którym się znajdujemy (ostatnie przed miastem początkowym) - koncówka algorytmu
    final_distance = best_node->getDistance() + matrix[current_city][start_city];                 // odległość do ostatniego miasta + odległość od tego miasta do miasta początkowego

    QueryPerformanceCounter(&end);                                                              // zakończenie mierzenia czasu

    cout << endl << "Dlugosc sciezki: " << final_distance << endl;                               // wyświetlanie ścieżki
    cout << "Ciag wierzcholkow: ";

    for(int j=0; j<best_node->getPathSize(); j++) {
        cout << best_node->getPathArray()[j] << " -> ";
    }
    cout << start_city << endl;

    elapsedTime1 = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;		                // policzenie czasu wykonywania się algorytmu
    cout << "Algorytm Breath First Search - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;

    ofstream results_file;
    results_file.open("BFS_results_PEA2.csv", ios::app);                                                                // zapisywanie wyników do pliku

    results_file << "Algorytm Breath First Search; " << cities_number << " miast; " << "Długość ścieżki: " << final_distance << "; "<< "Czas: " << elapsedTime1*1e3 << " ms" << endl;
    results_file.close();

    delete[] visited;
    for (int i = 0; i < nodes_amount-1; i++) {                                                                      // nodes_amount-1, ponieważ po ostatnim wywołaniu add_to_array, nodes_amount się zwiększyło, ale tablica jest stworzona dla poprzedniej wielkości
        delete array[i];
    }
    delete[] array;
}

Node** Breadth_first_search::add_to_array(Node** array, Node* node, int &nodes_amount) {

    Node** new_array = new Node*[nodes_amount];

    for(int i = 0; i < nodes_amount-1; i++) {
        new_array[i] = array[i];
    }
    new_array[nodes_amount-1] = node;
    nodes_amount ++;

    delete [] array;

    return new_array;
}

Node** Breadth_first_search::remove_first_from_array(Node** array, int &nodes_amount) {

    Node** new_array = new Node*[nodes_amount-2];                   // nodes_amount jest zawesze o 1 większy od aktualnej wielkości array, ale usuwamy element, więc tworzymy array dla nodes_amount-2 elementów

    for(int i = 0; i < nodes_amount-2; i++) {
        new_array[i] = array[i+1];
    }

    nodes_amount --;

    delete [] array;

    return new_array;
}

double Breadth_first_search::getElapsedTime() {
    return elapsedTime1;
}

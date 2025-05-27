//
// Created by mateu on 04.11.2024.
//

#include "best_first_search.h"

#include <array>
#include <iostream>
#include <random>
#include "node.h"
#include <windows.h>
#include <fstream>

using namespace std;

Best_first_search::Best_first_search(int **Matrix, int Cities_number) {
    matrix = Matrix;
    cities_number = Cities_number;
}

Best_first_search::~Best_first_search() {}

int Best_first_search::search_bound(int current_city, int distance, bool visited[], int first_city) {                     // funkcja obliczająca dolną granicę dla częściowej trasy, distance - koszt dotychczas przebytej drogi
    int bound = distance;                                                                   // granica
    int min_cities_distance = INT_MAX;                                                      //  minimalna długość krawędzi wychodząca z obecnego miasta, która jeszcze może być użyta

    for(int i=0; i<cities_number; i++) {                                                    // szukanie najkrotszej mozliwej sciezki wyjscia z obecnego miasta
        if(i != current_city && !visited[i] && matrix[current_city][i] < min_cities_distance) {
            min_cities_distance = matrix[current_city][i];
        }
    }
    bound += min_cities_distance;
    visited[current_city] = true;                                                           // obecne miasto można uznać za odwiedzone

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

void Best_first_search::BFS_algorithm() {
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

    for (int i = 0; i < cities_number; i++) {
        // cities_index[i] = i;
        visited[i] = false;
    }

    int bound = search_bound(start_city, 0, visited, start_city);                   // dolna granica obliczona dla korzenia
    Node* root = new Node(level, 0, bound*bound, cities_number, 1);                                                 // 1 - długość ścieżki
    root->create_visited_array(visited);                                                                         // dodawanie tablicy visited do obiektu typu Node
    root->add_to_path(start_city);                                              // dodanie do ścieżki wierzchołka początkowego
    array = add_to_array(array, root, nodes_amount);

    int current_city;                                                           // obecne miasto
    int* current_path;                                                          // wskaźnik na tablice z dotychczasową ścieżką
    int current_distance = 0;                                                      // dystans dotychczasowej ścieżki
    int current_cities_in_path = 0;                                                // ilość miast w obecnej ścieżce

    while(level < cities_number-1) {
        level++;

        for(int i=0; i<cities_number; i++) {

            if(i == 0) {                                                       // wykona się raz na początku pętli for
                current_city = array[0]->getPathArray()[array[0]->getPathSize() - 1];    // obecne miasto to ostatnie miasto w ścieżce z najlpeszego węzła
                current_path = array[0]->getPathArray();                        // zapisuje obecną ścieżke (czyli z najlpeszego węzła)
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
                new_node->add_to_path(i);                                                                                   // dodanie do ścieżki nowego miasta
                array = add_to_array(array, new_node, nodes_amount);;
            }
        } // po obliczeniu wszytskich potomków wykonuje się kopiec, dla wszystkich istniejących węzłów
        array = remove_best_from_array(array, nodes_amount);                          // usuwa najlepszy węzeł z tablicy, aby nie był już brany pod uwagę w porównaniu
        heap_making(array, nodes_amount-1);                                               // tworzenie kopca dla wszystkich węzłów (na podstawie wartości dolnych granic), nodes_amount-1, ponieważ po ostatnim wywołaniu add_to_array, nodes_amount się zwiększyło, ale tablica jest stworzona dla poprzedniej wielkości

        for(int j=0; j<cities_number; j++) {                                                //wyciąganie tablicy visited z najlepszego węzła
            visited[j] = array[0]->getVisited()[j];
        }

        level = array[0]->getLevel();
    }

    current_city = array[0]->getPathArray()[array[0]->getPathSize() - 1];                              // obecne miasto, w którym się znajdujemy (ostatnie przed miastem początkowym) - koncówka algorytmu
    final_distance = array[0]->getDistance() + matrix[current_city][start_city];                 // odległość do ostatniego miasta + odległość od tego miasta do miasta początkowego

    QueryPerformanceCounter(&end);                                                              // zakończenie mierzenia czasu

    cout << endl << "Dlugosc sciezki: " << final_distance << endl;
    cout << "Ciag wierzcholkow: ";                                                                  // wyświetlanie ścieżki

    for(int j=0; j<array[0]->getPathSize(); j++) {
        cout << array[0]->getPathArray()[j] << " -> ";
    }
    cout << start_city << endl;

    elapsedTime1 = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;		                // policzenie czasu wykonywania się algorytmu
    cout << "Algorytm Best First Search - czas: " << elapsedTime1*1e3 << " ms"<< endl << endl;

    ofstream results_file;
    results_file.open("Best_results_PEA2.csv", ios::app);                                                                                // zapisywanie wyników do pliku

    results_file << "Algorytm Best First Search; " << cities_number << " miast; " << "Długość ścieżki: " << final_distance << "; "<< "Czas: " << elapsedTime1*1e3 << " ms" << endl;
    results_file.close();


    delete[] visited;
    for (int i = 0; i < nodes_amount-1; i++) {                                                                      // nodes_amount-1, ponieważ po ostatnim wywołaniu add_to_array, nodes_amount się zwiększyło, ale tablica jest stworzona dla poprzedniej wielkości
        delete array[i];
    }
    delete[] array;
}

void Best_first_search::heap_making(Node** array, int size) {                     // funckja tworząca kopiec

    for(int i=(size/2)-1; i>=0; i--) {								// sprawdzanie "trójkątów" (rodzic i potomkowie) dla każdego rodzica, idąc od ostatniego rodzica
        heap(array, size, i);
    }
}

void Best_first_search::heap(Node** array, int size, int parentIndex) {       // funkcja przywracająca kopiec po dodaniu elementu
    int left_child_index = 2*parentIndex + 1;					// indeks lewego dziecka
    int right_child_index = 2*parentIndex + 2;					// indeks prawego dziecka

    int largest_value_index = parentIndex;						// początkowe założenie
    // porównanie rodzica z potomkakmi o ile istnieją i przypisanie do largest_value_index indeksu porównywanego elementu o największej wartości
    if(left_child_index < size && array[left_child_index]->getBound() < array[largest_value_index]->getBound())         // porównywanie na podstawie dolnych granic
        largest_value_index = left_child_index;

    if(right_child_index < size && array[right_child_index]->getBound() < array[largest_value_index]->getBound())
        largest_value_index = right_child_index;

    if(largest_value_index != parentIndex) {					// jeśli któryś z potomków był większy od rodzica to zamienia się go z rodzicem i wywołuje się rekurencyjnie funkcje kopiec dla indeksu gdzie znajduje się stary rodzic (wcześniej - zamieniony element)
        swap(array[largest_value_index], array[parentIndex]);
        heap(array, size, largest_value_index);					// sam indeks największej wartości po zamianie zostaje na starym miejscu i dla niego wywoływana jest funkcja kopiec i idzie się po kolei w dół drzewa}
    }
}

Node** Best_first_search::add_to_array(Node** array, Node* node, int &nodes_amount) {

    Node** new_array = new Node*[nodes_amount];

    for(int i = 0; i < nodes_amount-1; i++) {
        new_array[i] = array[i];
    }
    new_array[nodes_amount-1] = node;
    nodes_amount ++;

    delete [] array;

    return new_array;
}

Node** Best_first_search::remove_best_from_array(Node** array, int &nodes_amount) {

    Node** new_array = new Node*[nodes_amount-2];                                       // nodes_amount jest zawesze o 1 większy od aktualnej wielkości array, ale usuwamy element, więc tworzymy array dla nodes_amount-2 elementów

    for(int i = 0; i < nodes_amount-2; i++) {
        new_array[i] = array[i+1];
    }

    nodes_amount --;

    delete [] array;

    return new_array;
}

double Best_first_search::getElapsedTime() {
    return elapsedTime1;
}
//
// Created by mateu on 05.11.2024.
//

using namespace std;

#ifndef NODE_H
#define NODE_H
class Node {
    int level;          // poziom w drzewie
    int distance;       // całkowity koszt ścieżki do tego punktu
    int bound;           // dolna granica dla danego wierzchołka
    bool *visited;          // tablica miast odwiedzonych
    int cities_number;
    int path_size;
    int* path_array = nullptr;

    public:
    Node(int, int, int, int, int);
    Node();                 // konstruktor domyslny, bo inaczej nie będzie możlwiości stworzenia tablicy dynamicznej przechwoującej obiekty Noode
    ~Node();
    int getLevel();
    int getDistance();
    int getBound();
    void create_visited_array(bool*);
    bool* getVisited();
    void displayVisited();
    int* make_path(int*);           // kopiuje ścieżkę rodzica do ścieżki potomka
    void add_to_path(int);
    int* getPathArray();
    int getPathSize();
};
#endif //NODE_H

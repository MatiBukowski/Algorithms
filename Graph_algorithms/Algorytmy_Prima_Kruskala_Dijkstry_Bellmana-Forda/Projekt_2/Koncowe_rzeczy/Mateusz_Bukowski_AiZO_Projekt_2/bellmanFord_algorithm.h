#include <iostream>

using namespace std;

class BellmanFord_Algorithm {
	int a;						// wierzchołek startowy
	int b;						// wierzchołek końcowy
	int n;						// liczba wierzchołków
	int edges_number;			// liczba wierzchołków
	int* U;						// tablica dynamiczna z pierwszym wierzchołkiem krawędzi
	int* V;						// tablica dynamiczna z drugim wierzchołkiem krawędzi
	int** incidence_matrix;		// macierz incydencji
	int** successor_list;		// lista następników
	int* weight_edges;			// tablica dynamiczna z wagami
	
	public:
		BellmanFord_Algorithm(int, int, int**, int*, int**, int, int);
		~BellmanFord_Algorithm();
		void bellmanFord_matrix();
		void bellmanFord_list();
		void show_shortest_path(int*, int*);
};

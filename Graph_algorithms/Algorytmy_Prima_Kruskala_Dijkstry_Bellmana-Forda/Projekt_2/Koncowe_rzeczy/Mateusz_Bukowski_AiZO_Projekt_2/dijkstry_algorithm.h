#include <iostream>

using namespace std;

class Dijkstry_Algorithm {
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
		Dijkstry_Algorithm(int, int, int**, int*, int**, int, int);
		~Dijkstry_Algorithm();
		void dijkstry_matrix();
		void dijkstry_list();
		int minD(int*, bool*);
		void show_shortest_path(int*, int*);
};

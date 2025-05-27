#include <iostream>

using namespace std;

class BellmanFord_Algorithm {
	int a;						// wierzcho³ek startowy
	int b;						// wierzcho³ek koñcowy
	int n;						// liczba wierzcho³ków
	int edges_number;			// liczba wierzcho³ków
	int* U;						// tablica dynamiczna z pierwszym wierzcho³kiem krawêdzi
	int* V;						// tablica dynamiczna z drugim wierzcho³kiem krawêdzi
	int** incidence_matrix;		// macierz incydencji
	int** successor_list;		// lista nastêpników
	int* weight_edges;			// tablica dynamiczna z wagami
	
	public:
		BellmanFord_Algorithm(int, int, int**, int*, int**, int, int);
		~BellmanFord_Algorithm();
		void bellmanFord_matrix();
		void bellmanFord_list();
		void show_shortest_path(int*, int*);
};

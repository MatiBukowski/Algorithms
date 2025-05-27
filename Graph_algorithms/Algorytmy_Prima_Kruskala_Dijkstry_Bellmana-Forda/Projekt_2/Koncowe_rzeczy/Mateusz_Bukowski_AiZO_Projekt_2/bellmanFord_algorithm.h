#include <iostream>

using namespace std;

class BellmanFord_Algorithm {
	int a;						// wierzcho�ek startowy
	int b;						// wierzcho�ek ko�cowy
	int n;						// liczba wierzcho�k�w
	int edges_number;			// liczba wierzcho�k�w
	int* U;						// tablica dynamiczna z pierwszym wierzcho�kiem kraw�dzi
	int* V;						// tablica dynamiczna z drugim wierzcho�kiem kraw�dzi
	int** incidence_matrix;		// macierz incydencji
	int** successor_list;		// lista nast�pnik�w
	int* weight_edges;			// tablica dynamiczna z wagami
	
	public:
		BellmanFord_Algorithm(int, int, int**, int*, int**, int, int);
		~BellmanFord_Algorithm();
		void bellmanFord_matrix();
		void bellmanFord_list();
		void show_shortest_path(int*, int*);
};

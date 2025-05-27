#include <iostream>

using namespace std;

class Prim_Algorithm {
	int n;						// liczba wierzcho�k�w
	int edges_number;			// liczba wierzcho�k�w
	int* U;						// tablica dynamiczna z pierwszym wierzcho�kiem kraw�dzi
	int* V;						// tablica dynamiczna z drugim wierzcho�kiem kraw�dzi
	int** incidence_matrix;		// macierz incydencji
	int** adjacency_list;		// lista s�siedztwa
	int* weight_edges;			// tablica dynamiczna z wagami
	
	public:
		Prim_Algorithm(int, int, int**, int*, int**);
		~Prim_Algorithm();
		void prim_matrix();				// funkcja szukaj�ca MST u�ywaj�c macierzy incydencji i algorytmu Prima
		void prim_list();				// funkcja szukaj�ca MST u�ywaj�c listy s�siedztwa i algorytmu Prima
		int minKey(int*, bool*);		// funkcja zwracaj�ca wierzcho�ek z minimaln� warto�ci� key
		void show_MST(int*, int*);		// funkcja wy�wietlaj�ca MST
};

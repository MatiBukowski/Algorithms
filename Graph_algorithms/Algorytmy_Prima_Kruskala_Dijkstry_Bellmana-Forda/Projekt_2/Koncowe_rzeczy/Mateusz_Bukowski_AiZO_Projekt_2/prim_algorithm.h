#include <iostream>

using namespace std;

class Prim_Algorithm {
	int n;						// liczba wierzcho³ków
	int edges_number;			// liczba wierzcho³ków
	int* U;						// tablica dynamiczna z pierwszym wierzcho³kiem krawêdzi
	int* V;						// tablica dynamiczna z drugim wierzcho³kiem krawêdzi
	int** incidence_matrix;		// macierz incydencji
	int** adjacency_list;		// lista s¹siedztwa
	int* weight_edges;			// tablica dynamiczna z wagami
	
	public:
		Prim_Algorithm(int, int, int**, int*, int**);
		~Prim_Algorithm();
		void prim_matrix();				// funkcja szukaj¹ca MST u¿ywaj¹c macierzy incydencji i algorytmu Prima
		void prim_list();				// funkcja szukaj¹ca MST u¿ywaj¹c listy s¹siedztwa i algorytmu Prima
		int minKey(int*, bool*);		// funkcja zwracaj¹ca wierzcho³ek z minimaln¹ wartoœci¹ key
		void show_MST(int*, int*);		// funkcja wyœwietlaj¹ca MST
};

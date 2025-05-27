#include <iostream>

using namespace std;

class ShowP {
	int *U;							// tablica z pierwszy wierzcho³kiem krawêdzi
	int *V;							// tablica z drugim wierzcvho³kiem krawêdzi
	int *weight_edges;				// tablica z wagami krawêdzi
	int** incidence_matrix;			// macierz incydencji
	int n;							// liczba wierzcho³ków
	int density_edges;				// liczba krawêdzi grafu zgodnie z podan¹ gêstoœcia przez u¿ytkownika
	int** successor_list;
	
	public:
		ShowP(int*, int*, int*, int, int, int**, int**);
		~ShowP();
		void show_graph();
};

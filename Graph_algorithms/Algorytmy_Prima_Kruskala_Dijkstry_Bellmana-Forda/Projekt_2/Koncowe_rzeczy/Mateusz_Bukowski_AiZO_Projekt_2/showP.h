#include <iostream>

using namespace std;

class ShowP {
	int *U;							// tablica z pierwszy wierzcho�kiem kraw�dzi
	int *V;							// tablica z drugim wierzcvho�kiem kraw�dzi
	int *weight_edges;				// tablica z wagami kraw�dzi
	int** incidence_matrix;			// macierz incydencji
	int n;							// liczba wierzcho�k�w
	int density_edges;				// liczba kraw�dzi grafu zgodnie z podan� g�sto�cia przez u�ytkownika
	int** successor_list;
	
	public:
		ShowP(int*, int*, int*, int, int, int**, int**);
		~ShowP();
		void show_graph();
};

#include <iostream>

using namespace std;

class Show {
	int *U;							// tablica z pierwszy wierzcho³kiem krawêdzi
	int *V;							// tablica z drugim wierzcvho³kiem krawêdzi
//	int *vertex;					// tablica z wierzcho³kami
	int *weight_edges;				// tablica z wagami krawêdzi
	int** incidence_matrix;			// macierz incydencji
	int n;							// liczba wierzcho³ków
	int density_edges;				// liczba krawêdzi grafu zgodnie z podan¹ gêstoœcia przez u¿ytkownika
	int** adjacency_list;
	
	public:
		Show(int*, int*, int*, int, int, int**, int**);
		~Show();
		void show_graph();
};

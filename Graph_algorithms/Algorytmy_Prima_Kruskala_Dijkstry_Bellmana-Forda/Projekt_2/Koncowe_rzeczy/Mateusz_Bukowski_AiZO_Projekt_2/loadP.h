#include <iostream>

using namespace std;

class LoadP {
	int n;							// ilo�� wierzcho�k�w
	int g;							// g�sto��
	int *U;							// tablica z pierwszy wierzcho�kiem kraw�dzi
	int *V;							// tablica z drugim wierzcvho�kiem kraw�dzi
	int *vertex;					// tablica z wierzcho�kami
	int *weight_edges;				// tablica z wagami kraw�dzi
	int **incidence_matrix;			// macierz incydencji
	int edges_number;				// liczba kraw�dzi grafu
	
	public:
		LoadP();
		~LoadP();
		void load_graph();
		void generate_incidence_matrix();
		int* getU();
		int* getV();
		int* getVertex();
		int* getWeight();
		int** getIncidenceMatrix();
		int getN();
		int getEdgesNumber();
		int** get_Suc_List();		// funckja, kt�ra zwraca list� nast�pnik�w
};

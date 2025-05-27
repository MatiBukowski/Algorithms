#include <iostream>

using namespace std;

class LoadP {
	int n;							// iloœæ wierzcho³ków
	int g;							// gêstoœæ
	int *U;							// tablica z pierwszy wierzcho³kiem krawêdzi
	int *V;							// tablica z drugim wierzcvho³kiem krawêdzi
	int *vertex;					// tablica z wierzcho³kami
	int *weight_edges;				// tablica z wagami krawêdzi
	int **incidence_matrix;			// macierz incydencji
	int edges_number;				// liczba krawêdzi grafu
	
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
		int** get_Suc_List();		// funckja, która zwraca listê nastêpników
};

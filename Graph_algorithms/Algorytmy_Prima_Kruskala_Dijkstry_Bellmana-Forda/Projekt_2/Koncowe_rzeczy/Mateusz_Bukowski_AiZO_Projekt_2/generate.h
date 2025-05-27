#include <iostream>

using namespace std;

class Generate {
	int n;							// iloœæ wierzcho³ków
	int g;							// gêstoœæ
	int *U;							// tablica z pierwszy wierzcho³kiem krawêdzi
	int *V;							// tablica z drugim wierzcvho³kiem krawêdzi
	int *vertex;					// tablica z wierzcho³kami
	int *weight_edges;				// tablica z wagami krawêdzi
	int **incidence_matrix;			// macierz incydencji
	int density_edges;
	
	public:
		Generate(int, int);												// konstruktor
		~Generate();											// destruktor
		void generate_graph();									// funkcja tworz¹ca najpierw losowe drzewo rozpinaj¹ce, a potem uzupe³niaj¹ce je o kolejne losowe krawêdzie aby graf zgadza³ siê z gêstoœci¹
		bool check_edge_exist(int, int, int, int*, int*);		// funkcja sprawdzaj¹ca czy krawêdŸ o danych wierzcho³kach ju¿ istnieje
		void generate_incidence_matrix();						// generuje macierz incydencji
		int* getU();
		int* getV();
		int* getVertex();
		int* getWeight();										// zwraca tablicê z wagami
		int** getIncidenceMatrix();
		int getN();
		int getDensityEdges();
		int** get_Adj_List();
};


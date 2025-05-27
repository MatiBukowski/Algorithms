#include <iostream>

using namespace std;

class Generate {
	int n;							// ilo�� wierzcho�k�w
	int g;							// g�sto��
	int *U;							// tablica z pierwszy wierzcho�kiem kraw�dzi
	int *V;							// tablica z drugim wierzcvho�kiem kraw�dzi
	int *vertex;					// tablica z wierzcho�kami
	int *weight_edges;				// tablica z wagami kraw�dzi
	int **incidence_matrix;			// macierz incydencji
	int density_edges;
	
	public:
		Generate(int, int);												// konstruktor
		~Generate();											// destruktor
		void generate_graph();									// funkcja tworz�ca najpierw losowe drzewo rozpinaj�ce, a potem uzupe�niaj�ce je o kolejne losowe kraw�dzie aby graf zgadza� si� z g�sto�ci�
		bool check_edge_exist(int, int, int, int*, int*);		// funkcja sprawdzaj�ca czy kraw�d� o danych wierzcho�kach ju� istnieje
		void generate_incidence_matrix();						// generuje macierz incydencji
		int* getU();
		int* getV();
		int* getVertex();
		int* getWeight();										// zwraca tablic� z wagami
		int** getIncidenceMatrix();
		int getN();
		int getDensityEdges();
		int** get_Adj_List();
};


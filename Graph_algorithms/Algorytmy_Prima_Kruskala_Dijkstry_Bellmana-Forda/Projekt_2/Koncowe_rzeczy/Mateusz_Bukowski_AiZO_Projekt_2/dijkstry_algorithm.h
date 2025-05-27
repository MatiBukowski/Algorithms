#include <iostream>

using namespace std;

class Dijkstry_Algorithm {
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
		Dijkstry_Algorithm(int, int, int**, int*, int**, int, int);
		~Dijkstry_Algorithm();
		void dijkstry_matrix();
		void dijkstry_list();
		int minD(int*, bool*);
		void show_shortest_path(int*, int*);
};

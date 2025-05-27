#include <iostream>

using namespace std;

class Kruskal_Algorithm {
	int n;						// liczba wierzcho�k�w
	int edges_number;			// liczba wierzcho�k�w
	int* U;						// tablica dynamiczna z pierwszym wierzcho�kiem kraw�dzi
	int* V;						// tablica dynamiczna z drugim wierzcho�kiem kraw�dzi
	int** incidence_matrix;		// macierz incydencji
	int** adjacency_list;		// lista s�siedztwa
	int* weight_edges;			// tablica dynamiczna z wagami
	
	public:
		Kruskal_Algorithm(int, int, int**, int*, int**);
		~Kruskal_Algorithm();
		void kruskal_matrix();						// funkcja szukaj�ca MST u�ywaj�c macierzy incydencji i algorytmu Kruskala
		void kruskal_list();						// funkcja szukaj�ca MST u�ywaj�c listy s�siedztwa i algorytmu Kruskala
		int** sort(int**);							// funkcja, kt�ra za pomoc� algorytmu shella rostuje tablice dynamiczna dwuwymiarow� z karwedziami wedlug wag
		int find(int, int*);						// funkcja, kt�ra zwraca max_rodzica (identyfiaktor) danego wierzcho�ka
		int* Union(int, int, int*);					// funkcja, ktora laczy dwa zbiory (przypisanie jakby tych samych identyfikator�w)
		void show_MST(int*, int*, int*);			// funkcja wy�wietlaj�ca MST
		void kopiec(int**, int, int);
		void tworzenie_kopca(int**, int);
		int** sortowanie_przez_kopcowanie(int**, int);
};


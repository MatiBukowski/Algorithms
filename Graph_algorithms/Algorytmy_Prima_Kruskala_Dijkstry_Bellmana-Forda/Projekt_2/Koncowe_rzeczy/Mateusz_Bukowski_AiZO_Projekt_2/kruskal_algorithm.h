#include <iostream>

using namespace std;

class Kruskal_Algorithm {
	int n;						// liczba wierzcho³ków
	int edges_number;			// liczba wierzcho³ków
	int* U;						// tablica dynamiczna z pierwszym wierzcho³kiem krawêdzi
	int* V;						// tablica dynamiczna z drugim wierzcho³kiem krawêdzi
	int** incidence_matrix;		// macierz incydencji
	int** adjacency_list;		// lista s¹siedztwa
	int* weight_edges;			// tablica dynamiczna z wagami
	
	public:
		Kruskal_Algorithm(int, int, int**, int*, int**);
		~Kruskal_Algorithm();
		void kruskal_matrix();						// funkcja szukaj¹ca MST u¿ywaj¹c macierzy incydencji i algorytmu Kruskala
		void kruskal_list();						// funkcja szukaj¹ca MST u¿ywaj¹c listy s¹siedztwa i algorytmu Kruskala
		int** sort(int**);							// funkcja, która za pomoc¹ algorytmu shella rostuje tablice dynamiczna dwuwymiarow¹ z karwedziami wedlug wag
		int find(int, int*);						// funkcja, która zwraca max_rodzica (identyfiaktor) danego wierzcho³ka
		int* Union(int, int, int*);					// funkcja, ktora laczy dwa zbiory (przypisanie jakby tych samych identyfikatorów)
		void show_MST(int*, int*, int*);			// funkcja wyœwietlaj¹ca MST
		void kopiec(int**, int, int);
		void tworzenie_kopca(int**, int);
		int** sortowanie_przez_kopcowanie(int**, int);
};


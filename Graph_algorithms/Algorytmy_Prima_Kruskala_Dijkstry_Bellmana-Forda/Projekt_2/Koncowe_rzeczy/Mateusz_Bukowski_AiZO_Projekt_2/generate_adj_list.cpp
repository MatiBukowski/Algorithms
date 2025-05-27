#include <iostream>

#include "generate_adj_list.h"

using namespace std;

Gen_Adj_List::Gen_Adj_List(int** matrix, int N, int Edges, int* weight) {
	incidence_matrix = matrix;
	n = N;
	edges_number = Edges;
	weight_edges = weight;
}

Gen_Adj_List::~Gen_Adj_List() {
	for(int i=0; i<n; i++) {
		delete [] adjacency_list[i];
	}
	delete [] adjacency_list;
}

void Gen_Adj_List::generate_adjacency_list() {
	adjacency_list = new int*[n];						// n-elementowa tablica wska�nik�w na listy s�siedztwa danych wierzcho�k�w - lista s�siedztwa
	int *adjacency;
	int adjacency_number;								// ilos� s�siad�w danego wierzcho�ka
	int counter;										// indeks tablicy dynamicznej adjancy;
	
	for(int i=0; i<n; i++) {
		adjacency_number = 0;
		counter = 1;									// od 1 bo dla 0 jest ilo�� s�siad�w
		
		for(int j=0; j<edges_number; j++) {	
			if(incidence_matrix[i][j] != 0)	adjacency_number++;				// oblicza ilo�� s�siad�w wierzcho�ka i
		}	
		adjacency = new int[(adjacency_number*2) + 1];						// adjacency_number*2 - bo s�siad + waga, +1 - bo ilo�� element�w
		adjacency[0] = (adjacency_number*2) + 1;							// dla indeksu 0 jest ilo��: s�siad�w danego wierzcho�ka + indeks zerowy + wagi - czyli (adjacency_number*2) + 1	element�w
		
		for(int j=0; j<edges_number; j++) {									// idzie po wszystkich kraw�dziach i szuka s�siad�w (if poni�ej) i dla nich sprawdza dalsze warunki
			if(incidence_matrix[i][j] != 0) {
				for(int v=0; v<n; v++) {
					if(incidence_matrix[v][j] !=0 && v != i) {
						adjacency[counter] = v;
						counter++;
						adjacency[counter] = weight_edges[j];
						counter++;
					}
				}
			}
		}
		adjacency_list[i] = adjacency;
	}
	
//	cout << endl;														// wy�wietlanie listy s�siedztwa
//	for(int i=0; i<n; i++) {
//		cout << i << " : ";
//		for(int j=1; j<adjacency_list[i][0]; j=j+2) {
//			cout << adjacency_list[i][j] << " ";						// od indeksu 1 zaczynaj� si� s�siedzi, bo wczesneij jest rozmiar. j = j+2, poniewa� co drugi element jest waga
//		}
//		cout << endl;
//	}
}

int** Gen_Adj_List::get_Adj_List() {
	return adjacency_list;
}



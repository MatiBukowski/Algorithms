#include <iostream>

#include "generate_suc_list.h"

using namespace std;

Gen_Suc_List::Gen_Suc_List(int** matrix, int N, int Edges, int* weight) {
	incidence_matrix = matrix;
	n = N;
	edges_number = Edges;
	weight_edges = weight;
}

Gen_Suc_List::~Gen_Suc_List() {
	for(int i=0; i<n; i++) {
		delete [] successor_list[i];
	}
	delete [] successor_list;
}

void Gen_Suc_List::generate_successor_list() {
	successor_list = new int*[n];						// n-elementowa tablica wska�nik�w na listy nast�pnik�w danych wierzcho�k�w - lista nast�pnik�w
	int *successors;
	int succesors_number;								// ilos� nast�pnik�w danego wierzcho�ka
	int counter;										// indeks tablicy dynamicznej cussessors;
	
	for(int i=0; i<n; i++) {
		succesors_number = 0;
		counter = 1;									// od 1 bo dla 0 jest ilo�� nast�pnik�w
		
		for(int j=0; j<edges_number; j++) {	
			if(incidence_matrix[i][j] == 1)	succesors_number++;				// oblicza ilo�� nast�pnik�w wierzcho�ka i
		}
		successors = new int[(succesors_number*2) + 1];						// succesors_number*2 - bo nast�pnik + waga, +1 - bo ilo�� element�w
		successors[0] = (succesors_number*2) + 1;							// dla indeksu 0 jest ilo��: nast�pnik�w danego wierzcho�ka + indeks zerowy + wagi - czyli (succesors_number*2) + 1	element�w
		
		for(int j=0; j<edges_number; j++) {									// idzie po wszystkich kraw�dziach i szuka s�siad�w (if poni�ej) i dla nich sprawdza dalsze warunki
			if(incidence_matrix[i][j] == 1) {
				for(int v=0; v<n; v++) {
					if(incidence_matrix[v][j] == -1) {
						successors[counter] = v;
						counter++;
						successors[counter] = weight_edges[j];
						counter++;
					}
				}
			}
		}
		successor_list[i] = successors;
	}
	
//	cout << endl;														// wy�wietlanie listy nast�pnik�w
//	for(int i=0; i<n; i++) {
//		cout << i << " : ";
//		for(int j=1; j<successor_list[i][0]; j=j+2) {
//			cout << successor_list[i][j] << " ";						// od indeksu 1 zaczynaj� si� s�siedzi, bo wczesneij jest rozmiar. j = j+2, poniewa� co drugi element jest waga
//		}
//		cout << endl;
//	}
}

int** Gen_Suc_List::get_Suc_List() {
	return successor_list;
}

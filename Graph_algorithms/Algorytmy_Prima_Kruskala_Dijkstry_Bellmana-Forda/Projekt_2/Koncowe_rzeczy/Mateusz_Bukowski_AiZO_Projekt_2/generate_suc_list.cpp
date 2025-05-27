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
	successor_list = new int*[n];						// n-elementowa tablica wskaŸników na listy nastêpników danych wierzcho³ków - lista nastêpników
	int *successors;
	int succesors_number;								// ilosæ nastêpników danego wierzcho³ka
	int counter;										// indeks tablicy dynamicznej cussessors;
	
	for(int i=0; i<n; i++) {
		succesors_number = 0;
		counter = 1;									// od 1 bo dla 0 jest iloœæ nastêpników
		
		for(int j=0; j<edges_number; j++) {	
			if(incidence_matrix[i][j] == 1)	succesors_number++;				// oblicza iloœæ nastêpników wierzcho³ka i
		}
		successors = new int[(succesors_number*2) + 1];						// succesors_number*2 - bo nastêpnik + waga, +1 - bo iloœæ elementów
		successors[0] = (succesors_number*2) + 1;							// dla indeksu 0 jest iloœæ: nastêpników danego wierzcho³ka + indeks zerowy + wagi - czyli (succesors_number*2) + 1	elementów
		
		for(int j=0; j<edges_number; j++) {									// idzie po wszystkich krawêdziach i szuka s¹siadów (if poni¿ej) i dla nich sprawdza dalsze warunki
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
	
//	cout << endl;														// wyœwietlanie listy nastêpników
//	for(int i=0; i<n; i++) {
//		cout << i << " : ";
//		for(int j=1; j<successor_list[i][0]; j=j+2) {
//			cout << successor_list[i][j] << " ";						// od indeksu 1 zaczynaj¹ siê s¹siedzi, bo wczesneij jest rozmiar. j = j+2, poniewa¿ co drugi element jest waga
//		}
//		cout << endl;
//	}
}

int** Gen_Suc_List::get_Suc_List() {
	return successor_list;
}

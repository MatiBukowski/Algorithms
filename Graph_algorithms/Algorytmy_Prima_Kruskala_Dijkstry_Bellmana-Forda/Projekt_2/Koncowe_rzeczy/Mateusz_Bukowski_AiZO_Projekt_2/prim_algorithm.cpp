#include <iostream>
#include <limits>

#include "prim_algorithm.h"

const int INF = numeric_limits<int>::max();  
 
using namespace std;

Prim_Algorithm::Prim_Algorithm(int N, int Edges, int** matrix, int* weight, int** adj_list) {
	n = N;
	edges_number = Edges;
	incidence_matrix = matrix;
	adjacency_list = adj_list;
	weight_edges = weight;
}

Prim_Algorithm::~Prim_Algorithm() {}

void Prim_Algorithm::prim_matrix() {
	int key[n];							// tablica przechwouj¹ca wartoœæ key dla ka¿dego wierzcho³ka
	bool zwn[n];						// zbiór wierzcho³ków nierozpatrzonych - jeœli true to wierzcho³ek nierozpatrzony, jeœli false to wierzcho³ek rozpatrzony
	int p[n];							// tablica poprzedników;
	
	for(int i=0; i<n; i++) {
		key[i] = INF;					// ustawienie klucza ka¿dego wierzcho³ka na nieskoñczonoœæ
		zwn[i] = true;					// ustawienie ka¿dego wierzcho³ka na nierozpatrzony
	}
	
	key[0] = 0;
	p[0] = -1;							// pierwszy wierzcho³ek nie ma poprzednika
	
	for(int i=0; i<n-1; i++) {			// MST ma n-1 wierzcho³ków
		int u = minKey(key, zwn);		// zwraca wierzcho³ek z minimalnym kluczem
		zwn[u] = false;					// ostatni wierzcho³ek mo¿e mieæ zwn = true, poniewa¿ i tak nic siê nie wykoan póŸniej dla niego
		
		for(int j=0; j<edges_number; j++) {															// idzie po wszystkich krawêdziach i szuka s¹siadów (if poni¿ej) i dla nich sprawdza dalsze warunki
			if(incidence_matrix[u][j] != 0) {
				for(int v=0; v<n; v++) {
					if(incidence_matrix[v][j] != 0 && zwn[v] && weight_edges[j] < key[v] ) {			// idzie w dó³ kolumny dla danej krawêdzi i szuka po³¹czonego wierzcho³ka i sprawdza warunki
						p[v] = u;
						key[v] = weight_edges[j];
					}
				}
			}
		}
	}
	
	cout << "-- MACIERZOWO --" <<endl;
	show_MST(key, p);
}

int Prim_Algorithm::minKey(int *key, bool *zwn) {		// funkcja zwracaj¹ca wierzcho³ek maj¹cy minimalny klucz z wierzcho³kow jeszcze nierozpatrzonych 
    int min = INF;
	int min_vertex;
	
    for (int i=0; i<n; i++) {
        if (key[i] < min && zwn[i]) {
            min = key[i];
            min_vertex = i;
        }
    }
    return min_vertex;
}

//---------------------------------------------------------------------------------------------------------------------

void Prim_Algorithm::prim_list() {
	int key[n];							// tablica przechwouj¹ca wartoœæ key dla ka¿dego wierzcho³ka
	bool zwn[n];						// zbiór wierzcho³ków nierozpatrzonych - jeœli true to wierzcho³ek nierozpatrzony, jeœli false to wierzcho³ek rozpatrzony
	int p[n];							// tablica poprzedników;
	
	for(int i=0; i<n; i++) {
		key[i] = INF;					// ustawienie klucza ka¿dego wierzcho³ka na nieskoñczonoœæ
		zwn[i] = true;					// ustawienie ka¿dego wierzcho³ka na nierozpatrzony
	}
	
	key[0] = 0;
	p[0] = -1;							// pierwszy wierzcho³ek nie ma poprzednika
	
	for(int i=0; i<n-1; i++) {			// MST ma n-1 wierzcho³ków
		int u = minKey(key, zwn);		// zwraca wierzcho³ek z minimalnym kluczem
		zwn[u] = false;					// ostatni wierzcho³ek mo¿e mieæ zwn = true, poniewa¿ i tak nic siê nie wykoan póŸniej dla niego
		
		for(int j=1; j<adjacency_list[u][0]; j=j+2) {						// adjacency_list[i][0] przechowuje rozmiar tablicy jednowymiarowej dla danego wierzcho³ka, +2 poniewa¿ co drugi element jest wag¹
			int v = adjacency_list[u][j];									// od 1 indeksu jest pierwszy s¹siad danego wierzcho³ka
			if(zwn[v] && adjacency_list[u][j+1] < key[v] ) {				// adjacency_list[u][j+1] - waga krawêdzi u-v
				p[v] = u;
				key[v] = adjacency_list[u][j+1];
			}
		}
	}

//	cout << endl;														// wyœwietlanie listy s¹siedztwa
//	for(int i=0; i<n; i++) {
//		cout << i << " : ";
//		for(int j=1; j<adjacency_list[i][0]; j++) {
//			cout << adjacency_list[i][j] << " ";						// od indeksu 1 zaczynaj¹ siê s¹siedzi, bo wczeœniej jest rozmiar
//		}
//		cout << endl;
//	}
	cout << endl;
	cout << endl << "-- LISTOWO --" <<endl;
	show_MST(key, p);
}


void Prim_Algorithm::show_MST(int *key, int* p) {
	int sum_weight = 0;
	
	cout<<"MINIMALNE DRZEWO ROZPINAJ¥CE:" << endl << endl;
	
	for(int i=1; i<n; i++) {			// n-1 krawêdzi, zaczynamy od wierzcho³ka drugiego, poniewa¿ pierwszy nie ma poprzednika
		cout<<"KrawêdŸ " << i << ": " << p[i] << " - " << i << " : " << key[i] << endl;
		sum_weight = sum_weight + key[i];
	}
	
	cout << endl << "Waga MST: " << sum_weight << endl;
}



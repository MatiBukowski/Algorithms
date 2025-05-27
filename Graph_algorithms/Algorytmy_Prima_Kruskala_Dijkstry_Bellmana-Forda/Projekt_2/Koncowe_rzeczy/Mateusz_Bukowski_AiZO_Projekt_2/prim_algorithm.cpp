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
	int key[n];							// tablica przechwouj�ca warto�� key dla ka�dego wierzcho�ka
	bool zwn[n];						// zbi�r wierzcho�k�w nierozpatrzonych - je�li true to wierzcho�ek nierozpatrzony, je�li false to wierzcho�ek rozpatrzony
	int p[n];							// tablica poprzednik�w;
	
	for(int i=0; i<n; i++) {
		key[i] = INF;					// ustawienie klucza ka�dego wierzcho�ka na niesko�czono��
		zwn[i] = true;					// ustawienie ka�dego wierzcho�ka na nierozpatrzony
	}
	
	key[0] = 0;
	p[0] = -1;							// pierwszy wierzcho�ek nie ma poprzednika
	
	for(int i=0; i<n-1; i++) {			// MST ma n-1 wierzcho�k�w
		int u = minKey(key, zwn);		// zwraca wierzcho�ek z minimalnym kluczem
		zwn[u] = false;					// ostatni wierzcho�ek mo�e mie� zwn = true, poniewa� i tak nic si� nie wykoan p�niej dla niego
		
		for(int j=0; j<edges_number; j++) {															// idzie po wszystkich kraw�dziach i szuka s�siad�w (if poni�ej) i dla nich sprawdza dalsze warunki
			if(incidence_matrix[u][j] != 0) {
				for(int v=0; v<n; v++) {
					if(incidence_matrix[v][j] != 0 && zwn[v] && weight_edges[j] < key[v] ) {			// idzie w d� kolumny dla danej kraw�dzi i szuka po��czonego wierzcho�ka i sprawdza warunki
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

int Prim_Algorithm::minKey(int *key, bool *zwn) {		// funkcja zwracaj�ca wierzcho�ek maj�cy minimalny klucz z wierzcho�kow jeszcze nierozpatrzonych 
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
	int key[n];							// tablica przechwouj�ca warto�� key dla ka�dego wierzcho�ka
	bool zwn[n];						// zbi�r wierzcho�k�w nierozpatrzonych - je�li true to wierzcho�ek nierozpatrzony, je�li false to wierzcho�ek rozpatrzony
	int p[n];							// tablica poprzednik�w;
	
	for(int i=0; i<n; i++) {
		key[i] = INF;					// ustawienie klucza ka�dego wierzcho�ka na niesko�czono��
		zwn[i] = true;					// ustawienie ka�dego wierzcho�ka na nierozpatrzony
	}
	
	key[0] = 0;
	p[0] = -1;							// pierwszy wierzcho�ek nie ma poprzednika
	
	for(int i=0; i<n-1; i++) {			// MST ma n-1 wierzcho�k�w
		int u = minKey(key, zwn);		// zwraca wierzcho�ek z minimalnym kluczem
		zwn[u] = false;					// ostatni wierzcho�ek mo�e mie� zwn = true, poniewa� i tak nic si� nie wykoan p�niej dla niego
		
		for(int j=1; j<adjacency_list[u][0]; j=j+2) {						// adjacency_list[i][0] przechowuje rozmiar tablicy jednowymiarowej dla danego wierzcho�ka, +2 poniewa� co drugi element jest wag�
			int v = adjacency_list[u][j];									// od 1 indeksu jest pierwszy s�siad danego wierzcho�ka
			if(zwn[v] && adjacency_list[u][j+1] < key[v] ) {				// adjacency_list[u][j+1] - waga kraw�dzi u-v
				p[v] = u;
				key[v] = adjacency_list[u][j+1];
			}
		}
	}

//	cout << endl;														// wy�wietlanie listy s�siedztwa
//	for(int i=0; i<n; i++) {
//		cout << i << " : ";
//		for(int j=1; j<adjacency_list[i][0]; j++) {
//			cout << adjacency_list[i][j] << " ";						// od indeksu 1 zaczynaj� si� s�siedzi, bo wcze�niej jest rozmiar
//		}
//		cout << endl;
//	}
	cout << endl;
	cout << endl << "-- LISTOWO --" <<endl;
	show_MST(key, p);
}


void Prim_Algorithm::show_MST(int *key, int* p) {
	int sum_weight = 0;
	
	cout<<"MINIMALNE DRZEWO ROZPINAJ�CE:" << endl << endl;
	
	for(int i=1; i<n; i++) {			// n-1 kraw�dzi, zaczynamy od wierzcho�ka drugiego, poniewa� pierwszy nie ma poprzednika
		cout<<"Kraw�d� " << i << ": " << p[i] << " - " << i << " : " << key[i] << endl;
		sum_weight = sum_weight + key[i];
	}
	
	cout << endl << "Waga MST: " << sum_weight << endl;
}



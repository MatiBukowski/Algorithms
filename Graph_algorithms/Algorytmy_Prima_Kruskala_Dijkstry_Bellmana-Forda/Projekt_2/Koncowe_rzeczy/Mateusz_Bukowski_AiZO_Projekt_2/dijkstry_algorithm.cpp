#include <iostream>
#include <limits>

#include "dijkstry_algorithm.h"

const int INF = numeric_limits<int>::max();  
 
using namespace std;

Dijkstry_Algorithm::Dijkstry_Algorithm(int N, int Edges, int** matrix, int* weight, int** suc_list, int A, int B) {
	n = N;
	edges_number = Edges;
	incidence_matrix = matrix;
	successor_list = suc_list;
	weight_edges = weight;
	a = A;
	b = B;
}

Dijkstry_Algorithm::~Dijkstry_Algorithm() {}

void Dijkstry_Algorithm::dijkstry_matrix() {
	int d[n];							// tablica przechwouj�ca warto�� d (drogi) dla ka�dego wierzcho�ka
	bool zwn[n];						// zbi�r wierzcho�k�w nierozpatrzonych - je�li true to wierzcho�ek nierozpatrzony, je�li false to wierzcho�ek rozpatrzony
	int p[n];							// tablica poprzednik�w;
	
	for(int i=0; i<n; i++) {
		d[i] = INF;						// ustawienie drogi ka�dego wierzcho�ka na niesko�czono��
		zwn[i] = true;
	}
	
	d[a] = 0;
	p[a] = -1;
	
	for(int i=0; i<n; i++) {			// trzeba przej�� po ka�dym wierzcho�ku
		int u = minD(d, zwn);
		zwn[u] = false;					// wierzcho�ek rozpatrzony
		
		for(int j=0; j<edges_number; j++) {															// idzie po wszystkich kraw�dziach i szuka nast�pnik�w (if poni�ej) i dla nich sprawdza dalsze warunki
			if(incidence_matrix[u][j] == 1) {
				for(int v=0; v<n; v++) {
					if(incidence_matrix[v][j] == -1 && d[u]+weight_edges[j] < d[v] ) {			// idzie w d� kolumny dla danej kraw�dzi i szuka po��czonego wierzcho�ka i sprawdza warunki
						p[v] = u;
						d[v] = d[u] + weight_edges[j];
//						cout << u << " " << v << " " << d[v] << endl;
					}
				}
			}
		}
	}
	cout << "-- MACIERZOWO --" <<endl;
	show_shortest_path(p, d);
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

void Dijkstry_Algorithm::dijkstry_list() {
	int d[n];							// tablica przechwouj�ca warto�� d (drogi) dla ka�dego wierzcho�ka
	bool zwn[n];						// zbi�r wierzcho�k�w nierozpatrzonych - je�li true to wierzcho�ek nierozpatrzony, je�li false to wierzcho�ek rozpatrzony
	int p[n];							// tablica poprzednik�w;
	
	for(int i=0; i<n; i++) {
		d[i] = INF;					// ustawienie drogi ka�dego wierzcho�ka na niesko�czono��
		zwn[i] = true;
	}
	
	d[a] = 0;
	p[a] = -1;
	
	for(int i=0; i<n; i++) {		// trzeba przej�� po ka�dym wierzcho�ku
		int u = minD(d, zwn);
		zwn[u] = false;				// wierzcho�ek rozpatrzony
		
		for(int j=1; j<successor_list[u][0]; j=j+2) {						// successor_list[i][0] przechowuje rozmiar tablicy jednowymiarowej dla danego wierzcho�ka, +2 poniewa� co drugi element jest wag�
			int v = successor_list[u][j];									// od 1 indeksu jest pierwszy nast�pnik danego wierzcho�ka
			if(d[u]+successor_list[u][j+1] < d[v]) {
				p[v] = u;
				d[v] = d[u] + successor_list[u][j+1];
			}
		}
	}
	cout << endl;
	cout << "-- LISTOWO --" <<endl;
	show_shortest_path(p, d);
	
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

int Dijkstry_Algorithm::minD(int *d, bool *zwn) {		// funkcja zwracaj�ca wierzcho�ek maj�cy minimaln� drog� z wierzcho�kow jeszcze nierozpatrzonych 
    int min = INF;
	int min_vertex;
	
    for (int i=0; i<n; i++) {
        if (d[i] < min && zwn[i]) {
            min = d[i];
            min_vertex = i;
        }
    }
    return min_vertex;
}

void Dijkstry_Algorithm::show_shortest_path(int *p, int *d) {
	int pomB = b;																		// zmienna pomocnicza
	
	if(d[b] == INF) {
		cout << "�cie�ka nie istnieje" << endl;
	} else {
		while(p[pomB] != a) {												// maksymalna droga ma n-1 kraw�dzi
			cout << "Kraw�d�: " << p[pomB] << " - " << pomB << " : " << d[pomB] << endl;
			pomB = p[pomB];																	// idziemy po poprzednikach do wierzcho�ka startowego
		}
		cout << "Kraw�d�: " << p[pomB] << " - " << pomB << " : " << d[pomB];
		
		cout << endl << "Ca�kowity koszt �cie�ki mi�dzy wierzcho�kiem " << a << " i wierzcho�kiem " << b << " wynosi: " << d[b] << endl << endl;
	}
}

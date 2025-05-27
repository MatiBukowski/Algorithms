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
	int d[n];							// tablica przechwouj¹ca wartoœæ d (drogi) dla ka¿dego wierzcho³ka
	bool zwn[n];						// zbiór wierzcho³ków nierozpatrzonych - jeœli true to wierzcho³ek nierozpatrzony, jeœli false to wierzcho³ek rozpatrzony
	int p[n];							// tablica poprzedników;
	
	for(int i=0; i<n; i++) {
		d[i] = INF;						// ustawienie drogi ka¿dego wierzcho³ka na nieskoñczonoœæ
		zwn[i] = true;
	}
	
	d[a] = 0;
	p[a] = -1;
	
	for(int i=0; i<n; i++) {			// trzeba przejœæ po ka¿dym wierzcho³ku
		int u = minD(d, zwn);
		zwn[u] = false;					// wierzcho³ek rozpatrzony
		
		for(int j=0; j<edges_number; j++) {															// idzie po wszystkich krawêdziach i szuka nastêpników (if poni¿ej) i dla nich sprawdza dalsze warunki
			if(incidence_matrix[u][j] == 1) {
				for(int v=0; v<n; v++) {
					if(incidence_matrix[v][j] == -1 && d[u]+weight_edges[j] < d[v] ) {			// idzie w dó³ kolumny dla danej krawêdzi i szuka po³¹czonego wierzcho³ka i sprawdza warunki
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
	int d[n];							// tablica przechwouj¹ca wartoœæ d (drogi) dla ka¿dego wierzcho³ka
	bool zwn[n];						// zbiór wierzcho³ków nierozpatrzonych - jeœli true to wierzcho³ek nierozpatrzony, jeœli false to wierzcho³ek rozpatrzony
	int p[n];							// tablica poprzedników;
	
	for(int i=0; i<n; i++) {
		d[i] = INF;					// ustawienie drogi ka¿dego wierzcho³ka na nieskoñczonoœæ
		zwn[i] = true;
	}
	
	d[a] = 0;
	p[a] = -1;
	
	for(int i=0; i<n; i++) {		// trzeba przejœæ po ka¿dym wierzcho³ku
		int u = minD(d, zwn);
		zwn[u] = false;				// wierzcho³ek rozpatrzony
		
		for(int j=1; j<successor_list[u][0]; j=j+2) {						// successor_list[i][0] przechowuje rozmiar tablicy jednowymiarowej dla danego wierzcho³ka, +2 poniewa¿ co drugi element jest wag¹
			int v = successor_list[u][j];									// od 1 indeksu jest pierwszy nastêpnik danego wierzcho³ka
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

int Dijkstry_Algorithm::minD(int *d, bool *zwn) {		// funkcja zwracaj¹ca wierzcho³ek maj¹cy minimaln¹ drogê z wierzcho³kow jeszcze nierozpatrzonych 
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
		cout << "Œcie¿ka nie istnieje" << endl;
	} else {
		while(p[pomB] != a) {												// maksymalna droga ma n-1 krawêdzi
			cout << "KrawêdŸ: " << p[pomB] << " - " << pomB << " : " << d[pomB] << endl;
			pomB = p[pomB];																	// idziemy po poprzednikach do wierzcho³ka startowego
		}
		cout << "KrawêdŸ: " << p[pomB] << " - " << pomB << " : " << d[pomB];
		
		cout << endl << "Ca³kowity koszt œcie¿ki miêdzy wierzcho³kiem " << a << " i wierzcho³kiem " << b << " wynosi: " << d[b] << endl << endl;
	}
}

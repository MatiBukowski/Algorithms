#include <iostream>

#include "showP.h"

using namespace std;

ShowP::ShowP(int *u, int *v, int *weight, int N, int den_edges, int** Incidence_matrix, int** suc_list) {
	U = u;
	V = v;
	weight_edges = weight;
	n = N;
	density_edges = den_edges;
	incidence_matrix = Incidence_matrix;
	successor_list = suc_list;
}

ShowP::~ShowP() {}

void ShowP::show_graph() {
	cout<< endl << "LISTA KRAWÊDZI" << endl;
	for(int i=0; i<density_edges; i++) {
		cout << "KrawêdŸ " << i+1 << ":  " << U[i] << " - " << V[i] << "    :   " << weight_edges[i] << endl;
	}
	
	cout << endl << "MACIERZ INCYDENCJI" << endl;
	cout << endl << "W/K ";									// wyœwietlenie macierzy incydencji
	for(int i=0; i<density_edges; i++) {
		cout << U[i] << "-" << V[i] << " ";
	}
	cout << endl;
	for(int i=0; i<density_edges; i++) {
		cout << "-----";
	}
	cout << endl;
	
	for(int i=0; i<n; i++) {
		cout << i << "|   ";
		for(int j=0; j<density_edges; j++) {
			cout << incidence_matrix[i][j] << "   ";
		}
		cout << endl;
	}
	cout << endl;
	
	cout << endl << "LISTA NASTÊPNIKÓW" << endl;
	for(int i=0; i<n; i++) {
		cout << i << " : ";
		for(int j=1; j<successor_list[i][0]; j=j+2) {
			cout << successor_list[i][j] << "(" << successor_list[i][j+1] << ")" << ", ";
		}	
		cout << endl;
	}
	
}

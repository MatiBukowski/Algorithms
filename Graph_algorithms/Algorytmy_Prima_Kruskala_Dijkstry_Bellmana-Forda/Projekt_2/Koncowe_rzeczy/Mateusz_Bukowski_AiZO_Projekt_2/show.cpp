#include <iostream>

#include "show.h"

using namespace std;

Show::Show(int *u, int *v, int *weight, int N, int den_edges, int** Incidence_matrix, int** adj_list) {
	U = u;
	V = v;
	weight_edges = weight;
	n = N;
	density_edges = den_edges;
	incidence_matrix = Incidence_matrix;
	adjacency_list = adj_list;
}

Show::~Show() {}

void Show::show_graph() {
	cout<< endl << "LISTA KRAWÊDZI" << endl;
	for(int i=0; i<density_edges; i++) {
		cout << "KrawêdŸ " << i+1 << ":  " << U[i] << " - " << V[i] << "    :   " << weight_edges[i] << endl;
	}
	
	
															// tworzenie dwuwymiarowej tablicy dynamicznej
//	int **incidence_matrix = new int*[n];					// n - wiersze
//	for(int i=0; i<n; i++) {
//		incidence_matrix[i] = new int[density_edges];		// density_edges - kolumny
//	}
//	for(int i=0; i<n; i++) {								// wype³nienie macierzy incydencji 0
//		for(int j=0; j<density_edges; j++) {
//			incidence_matrix[i][j] = 0;
//		}
//	}
//	
//	for(int i=0; i<n; i++) {
//		for(int j=0; j<density_edges; j++) {
//			if(U[j] == i || V[j] == i)						// jeœli któryœ wierzcho³ek krawêdzi j jest wierzcho³kiem i to wpisz 1
//				incidence_matrix[i][j] = 1;
//		}
//	}
	
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
	
	
	cout << endl << "LISTA S¥SIEDZTWA" << endl;
	for(int i=0; i<n; i++) {
		cout << i << " : ";
		for(int j=1; j<adjacency_list[i][0]; j=j+2) {
			cout << adjacency_list[i][j] << "(" << adjacency_list[i][j+1] << ")" << ", ";
		}	
		cout << endl;
	}
	
//	for(int i=0; i<n; i++) {
//		delete [] incidence_matrix[i];
//	}
//	delete [] incidence_matrix;
}


#include <iostream>

#include "show.h"

using namespace std;

int *U;							// tablica dynamiczna z wierzcho³kiem U krawêdzi
int *V;							// tablica dynamiczna z wierzcho³keim V krawêdzi
int *vertex;					// tablica dynamiczna z wierzcho³kami
int *weight_edges;				// tablica dynamiczna z wagami krawêdzi			
int density_edges;				// liczba krawêdzi dla podanej gêstoœci przez u¿ywtkownika
int n;							// liczba wierzcho³ków

void show_graph() {
	
//	int *weight_edges = new int[density_edges];				// tworzenie tabeli dynamicznej z losowymi wagami dla ka¿dej z krawêdzi (od 1 do 30)
//	for(int i=0; i<density_edges; i++) {
//		weight_edges[i] = rand()%30 + 1;
//	}
	
	cout<< endl << "LISTA KRAWÊDZI" << endl;
	for(int i=0; i<density_edges; i++) {
		cout << "KrawêdŸ " << i+1 << ":  " << U[i] << " - " << V[i] << "    :   " << weight_edges[i] << endl;
	}
	
	
															// tworzenie dwuwymiarowej tablicy dynamicznej
	int **incidence_matrix = new int*[n];					// n - wiersze
	for(int i=0; i<n; i++) {
		incidence_matrix[i] = new int[density_edges];		// density_edges - kolumny
	}
	for(int i=0; i<n; i++) {								// wype³nienie macierzy incydencji 0
		for(int j=0; j<density_edges; j++) {
			incidence_matrix[i][j] = 0;
		}
	}
	
	for(int i=0; i<n; i++) {
		for(int j=0; j<density_edges; j++) {
			if(U[j] == i || V[j] == i)						// jeœli któryœ wierzcho³ek krawêdzi j jest wierzcho³kiem i to wpisz 1
				incidence_matrix[i][j] = 1;
		}
	}
	
	cout<< endl << "MACIERZ INCYDENCJI" << endl;
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
	
	for(int i=0; i<n; i++) {
		delete [] incidence_matrix[i];
	}
	delete [] incidence_matrix;
	
//	delete [] weight_edges;
}

void setU(int *a) {
	U = a;
}

void setV(int *b) {
	V = b;
}

void setVertex(int *c) {
	vertex = c;
}

void setDensity_edges(int d) {
	density_edges = d;
}

void setN(int e) {
	n = e;
}

void setWeightEdges(int *f) {
	weight_edges = f;
}

#include <iostream>

#include "show.h"

using namespace std;

int *U;							// tablica dynamiczna z wierzcho�kiem U kraw�dzi
int *V;							// tablica dynamiczna z wierzcho�keim V kraw�dzi
int *vertex;					// tablica dynamiczna z wierzcho�kami
int *weight_edges;				// tablica dynamiczna z wagami kraw�dzi			
int density_edges;				// liczba kraw�dzi dla podanej g�sto�ci przez u�ywtkownika
int n;							// liczba wierzcho�k�w

void show_graph() {
	
//	int *weight_edges = new int[density_edges];				// tworzenie tabeli dynamicznej z losowymi wagami dla ka�dej z kraw�dzi (od 1 do 30)
//	for(int i=0; i<density_edges; i++) {
//		weight_edges[i] = rand()%30 + 1;
//	}
	
	cout<< endl << "LISTA KRAW�DZI" << endl;
	for(int i=0; i<density_edges; i++) {
		cout << "Kraw�d� " << i+1 << ":  " << U[i] << " - " << V[i] << "    :   " << weight_edges[i] << endl;
	}
	
	
															// tworzenie dwuwymiarowej tablicy dynamicznej
	int **incidence_matrix = new int*[n];					// n - wiersze
	for(int i=0; i<n; i++) {
		incidence_matrix[i] = new int[density_edges];		// density_edges - kolumny
	}
	for(int i=0; i<n; i++) {								// wype�nienie macierzy incydencji 0
		for(int j=0; j<density_edges; j++) {
			incidence_matrix[i][j] = 0;
		}
	}
	
	for(int i=0; i<n; i++) {
		for(int j=0; j<density_edges; j++) {
			if(U[j] == i || V[j] == i)						// je�li kt�ry� wierzcho�ek kraw�dzi j jest wierzcho�kiem i to wpisz 1
				incidence_matrix[i][j] = 1;
		}
	}
	
	cout<< endl << "MACIERZ INCYDENCJI" << endl;
	cout << endl << "W/K ";									// wy�wietlenie macierzy incydencji
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

#include <iostream>
#include <ctime>

#include "generateP.h"
#include "generate_suc_list.h"

using namespace std;

Gen_Suc_List *gen_suc_list = NULL;

GenerateP::GenerateP(int N, int G) {
	n = N;
	g = G;
}

GenerateP::~GenerateP() {
	for(int i=0; i<n; i++) {
		delete [] incidence_matrix[i];
	}
	delete [] incidence_matrix;
	
	delete [] U;
	delete [] V;
	delete [] vertex;
	delete [] weight_edges;
}

void GenerateP::generate_graph() {
	srand(time(NULL));
	
	U = new int[n-1];						// drzewo rozpinaj¹ce ma n-1 krawêdzi. U to jeden wierzcho³ek danej krawêdzi 
	V = new int[n-1];						// drzewo rozpinaj¹ce ma n-1 krawêdzi. V to drugi wierzcho³ek danej krawêdzi 
	
	vertex = new int[n];					// tablica przechowuj¹ca wierzcho³ki grafu
	
	for(int i=0; i<n; i++) {
		vertex[i] = i;							// ustawianie wartoœci (nazw) wierzcho³ków od 0 do n-1
	}
	
	for(int i=0; i<n; i++) {					// pomieszanie wierzcho³ków w tablicy wierzcho³ków
		int j = rand()%n;						// od 0 do n-1
		swap(vertex[i], vertex[j]);
	}
	
	for(int i=1; i<n; i++) {					// generowanie krawêdzi drzewa - od 1 bo dla indeksu 0 wierzcho³ek jest pierwszym rodzicem - korzeniem
		int parent = vertex[rand()%i];			// rodzic jest wierzcho³kiem, po którym ju¿ ta iteracja przesz³a
		int child = vertex[i];					// dziecko to wierzcho³ek dla i z iteracji
		U[i-1] = parent; 
		V[i-1] = child;
	}
	
//	for(int i=0; i<n-1; i++) {
//		cout << "KrawêdŸ " << i+1 << ":  " << U[i] << " - " << V[i] << endl;
//	}
	
	int max_edges = (n*(n-1))/2;				// liczba krawêdzi w grafie pe³nym dla n wierzcho³ków
	density_edges = max_edges*(g*0.01);			// liczba krawêdzi dla podanej przez u¿ytkownika gêstoœci
	
	int *Unew = new int[density_edges];			// tworzone s¹ nowe tablice dla wiêkszej iloœci krawêdzi (dla U i V)
	int *Vnew = new int[density_edges];
	
	for(int i=0; i<density_edges; i++) {
		Unew[i] = 0;
		Vnew[i] = 0;	
	}
	
	for(int i=0; i<n-1; i++) {					// ze starych tablic kopiowane s¹ ju¿ istniej¹ce krawêdzie do nowych tablic
		Unew[i] = U[i];
		Vnew[i] = V[i];
	}
	
	for(int i=n-1; i<density_edges; i++) {		// tworzone s¹ nowe krawêdzie aby iloœæ krawêdzi zgadza³a siê z iloœci¹ krawêdzi dla podanej gêstoœci
		int random1 = rand()%n;
		int random2 = rand()%n;
		
		while(random1 == random2 || check_edge_exist(random1, random2, density_edges, Unew, Vnew)) {	// jeœli wylosowane wierzcho³ki krawêdzi s¹ takie same lub jeœli taka krawêdŸ ju¿ istnieje - wylosuj nowe wierzcho³ki
			random1 = rand()%n;
			random2 = rand()%n;
		}
		
		Unew[i] = random1;						// przypisywanie nowych wierzcho³ków (do zbioru krawêdzi)
		Vnew[i] = random2;
	}
	
	delete [] U;								// usuwanie starych tablic
	delete [] V;
	
	U = Unew;									// przypisywanie starego wskaŸnika na nowe tablice
	V = Vnew;
	
//	cout << endl;
//	for(int i=0; i<density_edges; i++) {
//		cout << "KrawêdŸ " << i+1 << ":  " << U[i] << " - " << V[i] << endl;
//	}
	
	weight_edges = new int[density_edges];				// tworzenie tabeli dynamicznej z losowymi wagami dla ka¿dej z krawêdzi (od 1 do 30)
	for(int i=0; i<density_edges; i++) {
		weight_edges[i] = rand()%30 + 1;
	}
	
	generate_incidence_matrix();
	
	gen_suc_list = new Gen_Suc_List(incidence_matrix, n, density_edges, weight_edges);
	gen_suc_list->generate_successor_list();
}

bool GenerateP::check_edge_exist(int a, int b, int n, int *Unew, int *Vnew) {
	for(int i=0; i<n; i++) {
		if(a == Unew[i] && b == Vnew[i]) {
			return true;
		}
	}
	return false;
}

void GenerateP::generate_incidence_matrix() {
	incidence_matrix = new int*[n];							// n - wiersze
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
			if(U[j] == i)	{							// jeœli pierwszy wierzcho³ek krawêdzi j jest wierzcho³kiem i to wpisz 1
				incidence_matrix[i][j] = 1;
			} else if(V[j] == i) {						// jeœli drugi wierzcho³ek krawêdzi j jest wierzcho³kiem i to wpisz -1
				incidence_matrix[i][j] = -1;
			}
		}
	}
}

int* GenerateP::getU() {
	return U;
}

int* GenerateP::getV() {
	return V;
}

int* GenerateP::getVertex() {
	return vertex;
}

int* GenerateP::getWeight() {
	return weight_edges;
}

int** GenerateP::getIncidenceMatrix() {
	return incidence_matrix;
}

int GenerateP::getN() {
	return n;
}

int GenerateP::getDensityEdges() {
	return density_edges;
}

int** GenerateP::get_Suc_List() {
	return gen_suc_list->get_Suc_List();
}

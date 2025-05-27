#include <iostream>
#include <ctime>

//#include "generate.h"
//#include "show.h"

using namespace std;

void generate_graph(int n, int g) {				// n - ilo�� wierzcho�k�w, g - g�sto��
	srand(time(NULL));
	int *U = new int[n-1];						// drzewo rozpinaj�ce ma n-1 kraw�dzi. U to jeden wierzcho�ek danej kraw�dzi 
	int *V = new int[n-1];						// drzewo rozpinaj�ce ma n-1 kraw�dzi. V to drugi wierzcho�ek danej kraw�dzi 
	
	int *vertex = new int[n];					// tablica przechowuj�ca wierzcho�ki grafu
	
	for(int i=0; i<n; i++) {
		vertex[i] = i;							// ustawianie warto�ci (nazw) wierzcho�k�w od 0 do n-1
	}
	
	for(int i=0; i<n; i++) {					// pomieszanie wierzcho�k�w w tablicy wierzcho�k�w
		int j = rand()%n;						// od 0 do n-1
		swap(vertex[i], vertex[j]);
	}
	
	for(int i=1; i<n; i++) {					// generowanie kraw�dzi drzewa - od 1 bo dla indeksu 0 wierzcho�ek jest pierwszym rodzicem - korzeniem
		int parent = vertex[rand()%i];			// rodzic jest wierzcho�kiem, po kt�rym ju� ta iteracja przesz�a
		int child = vertex[i];					// dziecko to wierzcho�ek dla i z iteracji
		U[i-1] = parent; 
		V[i-1] = child;
	}
	
	for(int i=0; i<n-1; i++) {
		cout << "Kraw�d� " << i+1 << ":  " << U[i] << " - " << V[i] << endl;
	}
	
	int max_edges = (n*(n-1))/2;				// liczba kraw�dzi w grafie pe�nym dla n wierzcho�k�w
	int density_edges = max_edges*(g*0.01);		// liczba kraw�dzi dla podanej przez u�ytkownika g�sto�ci
	
	int *Unew = new int[density_edges];			// tworzone s� nowe tablice dla wi�kszej ilo�ci kraw�dzi (dla U i V)
	int *Vnew = new int[density_edges];
	
	for(int i=0; i<density_edges; i++) {
		Unew[i] = 0;
		Vnew[i] = 0;	
	}
	
	for(int i=0; i<n-1; i++) {					// ze starych tablic kopiowane s� ju� istniej�ce kraw�dzie do nowych tablic
		Unew[i] = U[i];
		Vnew[i] = V[i];
	}
	
	for(int i=n-1; i<density_edges; i++) {		// tworzone s� nowe kraw�dzie aby ilo�� kraw�dzi zgadza�a si� z ilo�ci� kraw�dzi dla podanej g�sto�ci
		int random1 = rand()%n;
		int random2 = rand()%n;
		
		while(random1 == random2 || check_edge_exist(random1, random2, density_edges, Unew, Vnew)) {	// je�li wylosowane wierzcho�ki kraw�dzi s� takie same lub je�li taka kraw�d� ju� istnieje - wylosuj nowe wierzcho�ki
			random1 = rand()%n;
			random2 = rand()%n;
		}
		
		Unew[i] = random1;						// przypisywanie nowych wierzcho�k�w (do zbioru kraw�dzi)
		Vnew[i] = random2;
	}
	
	delete [] U;								// usuwanie starych tablic
	delete [] V;
	
	U = Unew;									// przypisywanie starego wska�nika na nowe tablice
	V = Vnew;
	
	cout << endl;
	for(int i=0; i<density_edges; i++) {
		cout << "Kraw�d� " << i+1 << ":  " << U[i] << " - " << V[i] << endl;
	}
	
	int *weight_edges = new int[density_edges];				// tworzenie tabeli dynamicznej z losowymi wagami dla ka�dej z kraw�dzi (od 1 do 30)
	for(int i=0; i<density_edges; i++) {
		weight_edges[i] = rand()%30 + 1;
	}
	
	setU(U);							// przekazanie warto�ci do funkcji show_graph()
	setV(V);
	setVertex(vertex);
	setDensity_edges(density_edges);
	setN(n);
	setWeightEdges(weight_edges);
	
	//delete [] U;
	//delete [] V;
	//delete [] vertex;
	//delete [] weight_edges;
	
}

bool check_edge_exist(int a, int b, int n, int* Unew, int* Vnew) {				// funkcja sprawdzaj�ca czy kraw�d� o wierzcho�kach a i b ju� istnieje
	
	for(int i=0; i<n; i++) {
		if((a == Unew[i] && b == Vnew[i]) || (b == Unew[i] && a == Vnew[i])) {
			return true;
		}
	}
	return false;
}

#include <iostream>
#include <ctime>

//#include "generate.h"
//#include "show.h"

using namespace std;

void generate_graph(int n, int g) {				// n - iloœæ wierzcho³ków, g - gêstoœæ
	srand(time(NULL));
	int *U = new int[n-1];						// drzewo rozpinaj¹ce ma n-1 krawêdzi. U to jeden wierzcho³ek danej krawêdzi 
	int *V = new int[n-1];						// drzewo rozpinaj¹ce ma n-1 krawêdzi. V to drugi wierzcho³ek danej krawêdzi 
	
	int *vertex = new int[n];					// tablica przechowuj¹ca wierzcho³ki grafu
	
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
	
	for(int i=0; i<n-1; i++) {
		cout << "KrawêdŸ " << i+1 << ":  " << U[i] << " - " << V[i] << endl;
	}
	
	int max_edges = (n*(n-1))/2;				// liczba krawêdzi w grafie pe³nym dla n wierzcho³ków
	int density_edges = max_edges*(g*0.01);		// liczba krawêdzi dla podanej przez u¿ytkownika gêstoœci
	
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
	
	cout << endl;
	for(int i=0; i<density_edges; i++) {
		cout << "KrawêdŸ " << i+1 << ":  " << U[i] << " - " << V[i] << endl;
	}
	
	int *weight_edges = new int[density_edges];				// tworzenie tabeli dynamicznej z losowymi wagami dla ka¿dej z krawêdzi (od 1 do 30)
	for(int i=0; i<density_edges; i++) {
		weight_edges[i] = rand()%30 + 1;
	}
	
	setU(U);							// przekazanie wartoœci do funkcji show_graph()
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

bool check_edge_exist(int a, int b, int n, int* Unew, int* Vnew) {				// funkcja sprawdzaj¹ca czy krawêdŸ o wierzcho³kach a i b ju¿ istnieje
	
	for(int i=0; i<n; i++) {
		if((a == Unew[i] && b == Vnew[i]) || (b == Unew[i] && a == Vnew[i])) {
			return true;
		}
	}
	return false;
}

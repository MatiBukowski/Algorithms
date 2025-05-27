#include <iostream>
#include <limits>

#include "bellmanFord_algorithm.h"

const int INF = numeric_limits<int>::max();  
 
using namespace std;

BellmanFord_Algorithm::BellmanFord_Algorithm(int N, int Edges, int** matrix, int* weight, int** suc_list, int A, int B) {
	n = N;
	edges_number = Edges;
	incidence_matrix = matrix;
	successor_list = suc_list;
	weight_edges = weight;
	a = A;
	b = B;
}

BellmanFord_Algorithm::~BellmanFord_Algorithm() {}

void BellmanFord_Algorithm::bellmanFord_matrix() {
	int d[n];							// tablica przechwouj�ca warto�� d (drogi) dla ka�dego wierzcho�ka
	int p[n];							// tablica poprzednik�w;
	int edges[edges_number][2];			// dwuwymiarowo tablica przechowuj�ca wierzcho�ki u i v kraw�dzi
	
	for(int i=0; i<edges_number; i++) {	
		for(int j=0; j<n; j++) {
			if(incidence_matrix[j][i] == 1) {
				edges[i][0] = j;								// u
			} else if (incidence_matrix[j][i] == -1) {
				edges[i][1] = j;								// v
			}
		}
	}
	
	for(int i=0; i<n; i++) {
		d[i] = INF-100;						// ustawienie drogi ka�dego wierzcho�ka na niesko�czono�� (tak naprawde to max int)
	}										// odejmuj� 100, aby przy dodaniu wagi kraw�dzi max int nie zmieni� si� na ujemny (tak si� dzieje po przekroczeniu maksymalnej warto�ci int)
	
	d[a] = 0;
	p[a] = -1;
	
	int counter;
	
	for(int i=0; i<n-1; i++) {
		counter = 0;					// zmienna kt�ra liczy ile zosta�o wykonanych relaksacji podczas jednej iteracji
		
		for(int j=0; j<edges_number; j++) {
			int u = edges[j][0];
			int v = edges[j][1];
			
			if(d[u] + weight_edges[j] < d[v]) {
				d[v] = d[u] + weight_edges[j];
				p[v] = u;
				counter++;
			}
		}
		
		if(counter == 0) 				// je�li nie wykonano podczas iteracji �adnej poprawy to algorytm mo�na zako�czy�
			break;
	}
	
	cout << "-- MACIERZOWO --" <<endl;
	show_shortest_path(p, d);
}

//---------------------------------------------------------------------------------------------------------------------------------------

void BellmanFord_Algorithm::bellmanFord_list() {
	int d[n];							// tablica przechwouj�ca warto�� d (drogi) dla ka�dego wierzcho�ka
	int p[n];							// tablica poprzednik�w;
	int edges[edges_number][3];			// dwuwymiarowo tablica przechowuj�ca wierzcho�ki u i v kraw�dzi oraz wag� danej kraw�dzi
	int index = 0;						// indeks kraw�dzi w tablic edges
		
	for(int i=0; i<n; i++) {	
		for(int j=1; j<successor_list[i][0]; j=j+2) {			// j = j+2, poniewa� co drugi element jest waga
			edges[index][0] = i;								// u
			edges[index][1] = successor_list[i][j];				// v
			edges[index][2] = successor_list[i][j+1];
			index++;
		}
	}
	
	for(int i=0; i<n; i++) {
		d[i] = INF-100;						// ustawienie drogi ka�dego wierzcho�ka na niesko�czono�� (tak naprawde to max int)
	}										// odejmuj� 100, aby przy dodaniu wagi kraw�dzi max int nie zmieni� si� na ujemny (tak si� dzieje po przekroczeniu maksymalnej warto�ci int)
	
	d[a] = 0;
	p[a] = -1;
	
	int counter;
	
	for(int i=0; i<n-1; i++) {
		counter = 0;					// zmienna kt�ra liczy ile zosta�o wykonanych relaksacji podczas jednej iteracji
		
		for(int j=0; j<edges_number; j++) {
			int u = edges[j][0];
			int v = edges[j][1];
			int weight = edges[j][2];
			
			if(d[u] + weight < d[v]) {
				d[v] = d[u] + weight;
				p[v] = u;
				counter++;
			}
		}
		
		if(counter == 0) 				// je�li nie wykonano podczas iteracji �adnej poprawy to algorytm mo�na zako�czy�
			break;
	}
	cout << endl;
	cout << "-- LISTOWO --" <<endl;
	show_shortest_path(p, d);
	
}

//---------------------------------------------------------------------------------------------------------------------------------------

void BellmanFord_Algorithm::show_shortest_path(int *p, int *d) {
	int pomB = b;																		// zmienna pomocnicza
	
	if(d[b] == INF || d[b] == INF-100) {												// db[b] == INF-100 - sprawdzenie dla algorytmu Bellmana-Forda
		cout << "�cie�ka nie istneieje" << endl;
	} else {
		while(p[pomB] != a) {												// maksymalna droga ma n-1 kraw�dzi
			cout << "Kraw�d�: " << p[pomB] << " - " << pomB << " : " << d[pomB] << endl;
			pomB = p[pomB];																	// idziemy po poprzednikach do wierzcho�ka startowego
		}
		cout << "Kraw�d�: " << p[pomB] << " - " << pomB << " : " << d[pomB];
		
		cout << endl << "Ca�kowity koszt �cie�ki mi�dzy wierzcho�kiem " << a << " i wierzcho�kiem " << b << " wynosi: " << d[b] << endl << endl;
	}
}

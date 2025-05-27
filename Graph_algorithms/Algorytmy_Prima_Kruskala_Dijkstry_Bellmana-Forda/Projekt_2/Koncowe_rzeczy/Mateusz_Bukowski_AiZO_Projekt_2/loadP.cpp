#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "loadP.h"
#include "generate_suc_list.h"

using namespace std;

LoadP::LoadP() {}

LoadP::~LoadP() {
	for(int i=0; i<n; i++) {
		delete [] incidence_matrix[i];
	}
	delete [] incidence_matrix;
	
	delete [] U;
	delete [] V;
	delete [] vertex;
	delete [] weight_edges;
}

void LoadP::load_graph() {
	ifstream file;	// wczytywany plik
	string name;	// zmienna przechowuj¹ca nazwê wczytywnaego pliku, któr¹ poda³ u¿ytkownik
		
	cout << "Podaj nazwê pliku, z którego chcesz wczytaæ tablicê: ";
	cin >> name;
	file.open((name + ".txt").c_str());			// otwieranie pliku o podanej nazwie
	
	if(file.good()==false) {					// jeœli plik siê nie otworzy³
		cout << "Plik nie istnieje" << endl;
	} else {
		
		string line;
		int line_number = 1;
		
		while(getline(file, line)) {
			if(line_number == 1) {
				stringstream ss;				// stringstream to typ danych, który pozwala na ³atwe konwertowanie danych np. z string na int
				ss << line.substr(0, line.find_first_of(" "));
				ss >> edges_number;
				
				ss.clear();						// czyszczenie ss
				
				ss << line.substr(line.find_first_of(" ")+1);
				ss >> n;
				
				U = new int[edges_number];
				V = new int[edges_number];
				vertex = new int[n];
				weight_edges = new int[edges_number];
				
				for(int i=0; i<n; i++) {
					vertex[i] = i;
				}
				
			} else {
				stringstream ss;
				ss << line.substr(0, line.find_first_of(" ")) << " ";
				ss >> U[line_number-2];
				ss.clear();	
				ss << line.substr(line.find_first_of(" ")+1,line.substr(line.find_first_of(" ")+1).find_first_of(" ")) << " ";
				ss >> V[line_number-2];
				ss.clear();
				ss << line.substr(line.find_first_of(" ")+1+line.substr(line.find_first_of(" ")+1).find_first_of(" ")+1);
				ss >> weight_edges[line_number-2];
				//cout << a << " " << b << " " << c << endl;
			}
			
			line_number++;
		}
		generate_incidence_matrix();
		
	}
	
	file.close();
	
//	for(int i=0; i<edges_number; i++) {											// wyœwietlanie wczytanego grafu
//		cout << U[i] << " --- " << V[i] << " : " << weight_edges[i] << endl;
//	}
}

void LoadP::generate_incidence_matrix() {
	incidence_matrix = new int*[n];							// n - wiersze
	for(int i=0; i<n; i++) {
		incidence_matrix[i] = new int[edges_number];		// edges_number - kolumny - iloœæ wierzcho³ków
	}
	for(int i=0; i<n; i++) {								// wype³nienie macierzy incydencji 0
		for(int j=0; j<edges_number; j++) {
			incidence_matrix[i][j] = 0;
		}
	}
	
	for(int i=0; i<n; i++) {
		for(int j=0; j<edges_number; j++) {
			if(U[j] == i)	{							// jeœli pierwszy wierzcho³ek krawêdzi j jest wierzcho³kiem i to wpisz 1
				incidence_matrix[i][j] = 1;
			} else if(V[j] == i) {						// jeœli drugi wierzcho³ek krawêdzi j jest wierzcho³kiem i to wpisz -1
				incidence_matrix[i][j] = -1;
			}
		}
	}
}

int* LoadP::getU() {
	return U;
}

int* LoadP::getV() {
	return V;
}

int* LoadP::getVertex() {
	return vertex;
} 

int* LoadP::getWeight() {
	return weight_edges;
}

int** LoadP::getIncidenceMatrix() {
	return incidence_matrix;
}

int LoadP::getN() {
	return n;
}

int LoadP::getEdgesNumber() {
	return edges_number;
}

int** LoadP::get_Suc_List() {
	Gen_Suc_List *gen_suc_list = new Gen_Suc_List(incidence_matrix, n, edges_number, weight_edges);
	gen_suc_list->generate_successor_list();
	return gen_suc_list->get_Suc_List();
}

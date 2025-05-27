#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "load.h"
#include "generate_adj_list.h"

using namespace std;

//Gen_Adj_List *gen_adj_list = NULL;

Load::Load() {}

Load::~Load() {
	for(int i=0; i<n; i++) {
		delete [] incidence_matrix[i];
	}
	delete [] incidence_matrix;
	
	delete [] U;
	delete [] V;
	delete [] vertex;
	delete [] weight_edges;
}

void Load::load_graph() {
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
//		gen_adj_list = new Gen_Adj_List(incidence_matrix, n, edges_number, weight_edges);
//		gen_adj_list->generate_adjacency_list();
	}
	
	file.close();
}

void Load::generate_incidence_matrix() {
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
			if(U[j] == i || V[j] == i)						// jeœli któryœ wierzcho³ek krawêdzi j jest wierzcho³kiem i to wpisz 1
				incidence_matrix[i][j] = 1;
		}
	}
}

int* Load::getU() {
	return U;
}

int* Load::getV() {
	return V;
}

int* Load::getVertex() {
	return vertex;
} 

int* Load::getWeight() {
	return weight_edges;
}

int** Load::getIncidenceMatrix() {
	return incidence_matrix;
}

int Load::getN() {
	return n;
}

int Load::getEdgesNumber() {
	return edges_number;
}

int** Load::get_Adj_List() {
	Gen_Adj_List *gen_adj_list = new Gen_Adj_List(incidence_matrix, n, edges_number, weight_edges);
	gen_adj_list->generate_adjacency_list();
	return gen_adj_list->get_Adj_List();
}

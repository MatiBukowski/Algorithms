#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "load.h"
#include "show.h"

using namespace std;

void load() {
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
		int n;						// iloœæ wierzcho³ków
		int edges_number;			// iloœæ krawêdzi
		int *U;
		int *V;
		int *vertex;
		int *weight_edges;
		
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
		
//		setU(U);							// przekazanie wartoœci do funkcji show_graph()
//		setV(V);
//		setVertex(vertex);
//		setDensity_edges(edges_number);
//		setN(n);
//		setWeightEdges(weight_edges);
		
//		delete [] U;
//		delete [] V;
//		delete [] vertex;
//		delete [] weight_edges;
	}
	
	file.close();
}

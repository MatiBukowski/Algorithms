//#ifndef GENERATE_ADJ_LIST_H
//#define GENERATE_ADJ_LIST_H

#include <iostream>

using namespace std;

class Gen_Adj_List {

	int** incidence_matrix;				// macierz incydencji - na jej podstawie tworzona jest lista s�siedztwa
	int** adjacency_list;				// lista s�siedztwa
	int n;								// liczba wierzcho�k�w
	int edges_number;					// liczba kraw�dzi
	int* weight_edges;
	
	public:
		Gen_Adj_List(int**, int, int, int*);
		~Gen_Adj_List();
		void generate_adjacency_list();
		int** get_Adj_List();
};


//#endif

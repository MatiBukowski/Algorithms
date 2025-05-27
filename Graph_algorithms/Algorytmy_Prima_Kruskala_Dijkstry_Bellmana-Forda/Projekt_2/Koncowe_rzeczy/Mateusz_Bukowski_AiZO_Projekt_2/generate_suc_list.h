#include <iostream>

using namespace std;

class Gen_Suc_List {

	int** incidence_matrix;				// macierz incydencji - na jej podstawie tworzona jest lista s�siedztwa
	int** successor_list;				// lista nast�pnik�w
	int n;								// liczba wierzcho�k�w
	int edges_number;					// liczba kraw�dzi
	int* weight_edges;
	
	public:
		Gen_Suc_List(int**, int, int, int*);
		~Gen_Suc_List();
		void generate_successor_list();
		int** get_Suc_List();
};

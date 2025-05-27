#include <iostream>
#include <cmath>

#include "kruskal_algorithm.h"
 
using namespace std;

Kruskal_Algorithm::Kruskal_Algorithm(int N, int Edges, int** matrix, int* weight, int** adj_list) {
	n = N;
	edges_number = Edges;
	incidence_matrix = matrix;
	adjacency_list = adj_list;
	weight_edges = weight;
}

Kruskal_Algorithm::~Kruskal_Algorithm() {}

void Kruskal_Algorithm::kruskal_matrix() {
	int **sorted_edges = new int*[edges_number];	// dwuwymiarowa tablica przechowuj�ca posortowane kraw�dzie wed�ug wag (1 element to indeks kraw�dzi, 2 element to waga kraw�dzi)
	int *result_U = new int[n-1];					// tablica przechowuj�ac pierwsze wierzcho�ki kraw�dzi o indeksie i nale��cej do MST (MST ma n-1 kraw�dzi)
	int *result_V = new int[n-1];					// tablica przechowuj�ac drugie wierzcho�ki kraw�dzi o indeksie i nale��cej do MST (MST ma n-1 kraw�dzi)
	int *result_weight = new int[n-1];				// tablica przechowuj�ca wagi kraw�dzi nale��cych do MST
	
	for(int i=0; i<edges_number; i++) {
		sorted_edges[i] = new int[2];
		sorted_edges[i][0] = i;
		sorted_edges[i][1] = weight_edges[i];
	}

//	sorted_edges = sort(sorted_edges);
	sorted_edges = sortowanie_przez_kopcowanie(sorted_edges, edges_number);
	
//	for(int i=0; i<edges_number; i++) {					// wy�wietlanie posortowanej tablicy kraw�dzi
//		cout << sorted_edges[i][0] << " : " << sorted_edges[i][1] << endl;
//	}
	
	int* parent = new int[n];
    int* rank = new int[n];
    for (int i=0; i<n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int u, v;											// wierzcho�ki kraw�dzi
    int amount;											// zmienna pomocnicza do zapisywania warto�ci u i v
    int e = 0;											// indeks elementu tablicy z wierzcho�kami kraw�dzi nale��cymi do MST
    for(int i=0; i<edges_number && e<n-1; i++) {		// e < n-1 - jak ju� bedzie n-1 kraw�dzi to mo�na szybciej sko�czy�, poniewa� MST ma n-1 kraw�dzi
    	int edge = sorted_edges[i][0];					// po kolei po posortowanych kraw�dziach
    	amount = 0;
    	for(int j=0; j<n; j++) {						// szukanie wierzcho�k�w dla danej kraw�dzi - w d� macierzy incydencji
    		if(incidence_matrix[j][edge] != 0 && amount == 0) {
    			u = j;
    			amount++;
			} else if(incidence_matrix[j][edge] != 0 && amount == 1) {
				v = j;
			}
		}

    	int x = find(u, parent);
    	int y = find(v, parent);
    	
    	if(x != y) {
    		result_U[e] = u;
    		result_V[e] = v;
    		result_weight[e] = sorted_edges[i][1];
    		e++;
    		parent = Union(x, y, parent);
		}
		
	}
	
  	cout << "-- MACIERZOWO --" <<endl;
	show_MST(result_U, result_V, result_weight);
	
	for(int i=0; i<edges_number; i++) {
		delete [] sorted_edges[i];
	}
	delete [] sorted_edges;
	
	delete [] parent;
	delete [] rank;
	delete [] result_U;
	delete [] result_V;
	delete [] result_weight;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

void Kruskal_Algorithm::kruskal_list() {
	int **sorted_edges = new int*[edges_number];	// dwuwymiarowa tablica przechowuj�ca posortowane kraw�dzie wed�ug wag (1 element to u, 2 element to waga kraw�dzi, e element to v)
	int *result_U = new int[n-1];					// tablica przechowuj�ac pierwsze wierzcho�ki kraw�dzi o indeksie i nale��cej do MST (MST ma n-1 kraw�dzi)
	int *result_V = new int[n-1];					// tablica przechowuj�ac drugie wierzcho�ki kraw�dzi o indeksie i nale��cej do MST (MST ma n-1 kraw�dzi)
	int *result_weight = new int[n-1];				// tablica przechowuj�ca wagi kraw�dzi nale��cych do MST
	
	for(int i=0; i<edges_number; i++) {
		sorted_edges[i] = new int[3];				// tablica, kt�ra przechwouje u-wag� kraw�dzi-v (taka kolejno��, aby m�c skorzysta� z funckji sort)
	}
	
	int index = 0;									// indeks wiersza tablicy sorted_edges
	
	for(int i=0; i<n; i++) {
		for(int j=1; j<adjacency_list[i][0]; j=j+2) {
			if(adjacency_list[i][j] > i) {								// je�li v > u, bo je�li v < u to znaczy, �e juz wczesniej dana karwedz by�a dodana do sorted_edges tylko w kolejno�ci v - u
				sorted_edges[index][0] = i;								// wierzcho�ek u danej kraw�dzi
				sorted_edges[index][1] = adjacency_list[i][j+1];		// waga danej kraw�dzi
				sorted_edges[index][2] = adjacency_list[i][j];			// wierzcho�ek v danej kraw�dzi
				index++;
			}
		}
	}
	
//	sorted_edges = sort(sorted_edges);
	
	sorted_edges = sortowanie_przez_kopcowanie(sorted_edges, edges_number);
	
//	for(int i=0; i<edges_number; i++) {									// wy�wietlanie posortowanej tablicy kraw�dzi
//		cout << sorted_edges[i][0] << " --- " << sorted_edges[i][2] << " : " << sorted_edges[i][1] << endl;
//	}
	
	int* parent = new int[n];
    int* rank = new int[n];
    for (int i=0; i<n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int e = 0;											// indeks elementu tablicy z wierzcho�kami kraw�dzi nale��cymi do MST
    for(int i=0; i<edges_number && e<n-1; i++) {		// e < n-1 - jak ju� bedzie n-1 kraw�dzi to mo�na szybciej sko�czy�, poniewa� MST ma n-1 kraw�dzi
    	int u = sorted_edges[i][0];
    	int v = sorted_edges[i][2];
    	
    	int x = find(u, parent);		// find(u, parent)
    	int y = find(v, parent);		// find(v, parent)
    	
    	if(x != y) {
    		result_U[e] = u;
    		result_V[e] = v;
    		result_weight[e] = sorted_edges[i][1];
    		e++;
    		parent = Union(x, y, parent);
		}
	}
	
	cout << endl;
	cout << "-- LISTOWO --" <<endl;
	show_MST(result_U, result_V, result_weight);
    
    for(int i=0; i<edges_number; i++) {
		delete [] sorted_edges[i];
	}
	delete [] sorted_edges;
	
	delete [] parent;
	delete [] rank;
	delete [] result_U;
	delete [] result_V;
	delete [] result_weight;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

int Kruskal_Algorithm::find(int vertex, int *parent) {						// funkcja, kt�ra zwraca max_rodzica (identyfiaktor) danego wierzcho�ka
	if(parent[vertex] == vertex)
		return vertex;
	return find(parent[vertex], parent);
}

int* Kruskal_Algorithm::Union(int x, int y, int *parent) {					// funkcja, ktora laczy dwa zbiory (przypisanie jakby tych samych identyfikator�w)
	parent[x] = y;
	return parent;
}

void Kruskal_Algorithm::show_MST(int *result_U, int *result_V, int *result_weight) {
	int sum_weight = 0;
	
	cout<<"MINIMALNE DRZEWO ROZPINAJ�CE:" << endl << endl;
	
	for(int i=0; i<n-1; i++) {			// n-1 kraw�dzi, zaczynamy od wierzcho�ka drugiego, poniewa� pierwszy nie ma poprzednika
		cout<<"Kraw�d� " << i+1 << ": " << result_U[i] << " - " << result_V[i] << " : " << result_weight[i] << endl;
		sum_weight = sum_weight + result_weight[i];
	}
	
	cout << endl << "Waga MST: " << sum_weight << endl;
}

//int** Kruskal_Algorithm::sort(int **sorted_edges) {							// funkcja, kt�ra za pomoc� algorytmu shella rostuje tablice dynamiczna dwuwymiarow� z karwedziami wedlug wag
//	int distance = edges_number;
//	int h;
//	
//	for(int i=1; i<edges_number; i++) {									// sekwencja odst�p�w Sedgewick'a
//		if(pow(4,i)+3*pow(2,i-1)+1 >= edges_number) {					// sprawdzane jest dla jakiego i jest maksymalny odst�p
//			h = i-1;													// do h zapisywana jest maksymalna warto�� i dla kt�rego odst�p jest mniejszy od n
//			i = edges_number;
//		}
//	}
//	
//	for(int w=h; w>=0; w--) {
//		
//		if(w != 0)														// por�wnywane s� warto�ci pocz�wszy od element�w odleg�ych o najwi�kszy mo�lwiy odst�p
//			distance = pow(4,w)+3*pow(2,w-1)+1;
//		
//		if(w == 0) 														// ostatni odst�p to 1 - por�wnywana ca�a tablica
//			distance = 1;
//		
//    	for(int i=distance; i<edges_number; i++) {
//        	int* pom = sorted_edges[i];
//            int j;
//            for (j=i; j>=distance && sorted_edges[j-distance][1]>pom[1]; j-=distance) {			//por�wnuje po kolei minimum 2 elementy i zamienia przez wstawianie 
//                sorted_edges[j] = sorted_edges[j-distance];				//przesuwa si� po kolei w prawo i mo�e por�wnywa� wcze�niej ju� por�wnywane liczby z kolejn� liczb� przesuni�t� o distance i si� sortuje
//            }
//            sorted_edges[j] = pom;
//        }
//    }
//    return sorted_edges;
//}

void Kruskal_Algorithm::kopiec(int **sorted_edges, int n, int parentIndex) {
	int left_child_index = 2*parentIndex + 1;					// indeks lewego dziecka
	int right_child_index = 2*parentIndex + 2;					// indeks prawego dziecka
	
	int largest_value_index = parentIndex;						// pocz�tkowe za�o�enie
																// por�wnanie rodzica z potomkakmi o ile istniej� i przypisanie do largest_value_index indeksu por�wnywanego elementu o najwi�kszej warto�ci
	if(left_child_index < n && sorted_edges[left_child_index][1] > sorted_edges[largest_value_index][1])
		largest_value_index = left_child_index;
		
	if(right_child_index < n && sorted_edges[right_child_index][1] > sorted_edges[largest_value_index][1])
		largest_value_index = right_child_index;
		
	if(largest_value_index != parentIndex) {										// je�li kt�ry� z potomk�w by� wi�kszy od rodzica to zamienia si� go z rodzicem i wywo�uje si� rekurencyjnie funkcje kopiec dla indeksu gdzie znajduje si� stary rodzic (wcze�niej - zamieniony element)
		swap(sorted_edges[largest_value_index], sorted_edges[parentIndex]);
		kopiec(sorted_edges, n, largest_value_index);								// sam indeks najwi�kszej warto�ci po zamianie zostaje na starym miejscu i dla niego wywo�ywana jest funkcja kopiec i idzie si� po kolei w d� drzewa
	}
}

void Kruskal_Algorithm::tworzenie_kopca(int **sorted_edges, int edges_number) {		// tworzenie kocpa dla ca�ej tablicy
	for(int i=(edges_number/2)-1; i>=0; i--) {										// sprawdzanie "tr�jk�t�w" (rodzic i potomkowie) dla ka�dego rodzica, id�c od ostatniego rodzica
		kopiec(sorted_edges, edges_number, i);
	}
}

int** Kruskal_Algorithm::sortowanie_przez_kopcowanie(int **sorted_edges, int edges_number) {
	
	tworzenie_kopca(sorted_edges, edges_number);												// tworzenie kocpa dla ca�ej tablicy
	
	for(int i=edges_number-1; i>=0; i--) {	
		swap(sorted_edges[0], sorted_edges[i]);													// ostatni element zamieniany jest z korzeniem (najwiekszym elementem)
		kopiec(sorted_edges, i, 0);																// przywracane s� w�a�ciwo�ci kopca dla tablic pomniejszonej o ostatni element
	}
	
	return sorted_edges;
}

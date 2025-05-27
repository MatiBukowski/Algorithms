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
	int **sorted_edges = new int*[edges_number];	// dwuwymiarowa tablica przechowuj¹ca posortowane krawêdzie wed³ug wag (1 element to indeks krawêdzi, 2 element to waga krawêdzi)
	int *result_U = new int[n-1];					// tablica przechowuj¹ac pierwsze wierzcho³ki krawêdzi o indeksie i nale¿¹cej do MST (MST ma n-1 krawêdzi)
	int *result_V = new int[n-1];					// tablica przechowuj¹ac drugie wierzcho³ki krawêdzi o indeksie i nale¿¹cej do MST (MST ma n-1 krawêdzi)
	int *result_weight = new int[n-1];				// tablica przechowuj¹ca wagi krawêdzi nale¿¹cych do MST
	
	for(int i=0; i<edges_number; i++) {
		sorted_edges[i] = new int[2];
		sorted_edges[i][0] = i;
		sorted_edges[i][1] = weight_edges[i];
	}

//	sorted_edges = sort(sorted_edges);
	sorted_edges = sortowanie_przez_kopcowanie(sorted_edges, edges_number);
	
//	for(int i=0; i<edges_number; i++) {					// wyœwietlanie posortowanej tablicy krawêdzi
//		cout << sorted_edges[i][0] << " : " << sorted_edges[i][1] << endl;
//	}
	
	int* parent = new int[n];
    int* rank = new int[n];
    for (int i=0; i<n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int u, v;											// wierzcho³ki krawêdzi
    int amount;											// zmienna pomocnicza do zapisywania wartoœci u i v
    int e = 0;											// indeks elementu tablicy z wierzcho³kami krawêdzi nale¿¹cymi do MST
    for(int i=0; i<edges_number && e<n-1; i++) {		// e < n-1 - jak ju¿ bedzie n-1 krawêdzi to mo¿na szybciej skoñczyæ, poniewa¿ MST ma n-1 krawêdzi
    	int edge = sorted_edges[i][0];					// po kolei po posortowanych krawêdziach
    	amount = 0;
    	for(int j=0; j<n; j++) {						// szukanie wierzcho³ków dla danej krawêdzi - w dó³ macierzy incydencji
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
	int **sorted_edges = new int*[edges_number];	// dwuwymiarowa tablica przechowuj¹ca posortowane krawêdzie wed³ug wag (1 element to u, 2 element to waga krawêdzi, e element to v)
	int *result_U = new int[n-1];					// tablica przechowuj¹ac pierwsze wierzcho³ki krawêdzi o indeksie i nale¿¹cej do MST (MST ma n-1 krawêdzi)
	int *result_V = new int[n-1];					// tablica przechowuj¹ac drugie wierzcho³ki krawêdzi o indeksie i nale¿¹cej do MST (MST ma n-1 krawêdzi)
	int *result_weight = new int[n-1];				// tablica przechowuj¹ca wagi krawêdzi nale¿¹cych do MST
	
	for(int i=0; i<edges_number; i++) {
		sorted_edges[i] = new int[3];				// tablica, która przechwouje u-wagê krawêdzi-v (taka kolejnoœæ, aby móc skorzystaæ z funckji sort)
	}
	
	int index = 0;									// indeks wiersza tablicy sorted_edges
	
	for(int i=0; i<n; i++) {
		for(int j=1; j<adjacency_list[i][0]; j=j+2) {
			if(adjacency_list[i][j] > i) {								// jeœli v > u, bo jeœli v < u to znaczy, ¿e juz wczesniej dana karwedz by³a dodana do sorted_edges tylko w kolejnoœci v - u
				sorted_edges[index][0] = i;								// wierzcho³ek u danej krawêdzi
				sorted_edges[index][1] = adjacency_list[i][j+1];		// waga danej krawêdzi
				sorted_edges[index][2] = adjacency_list[i][j];			// wierzcho³ek v danej krawêdzi
				index++;
			}
		}
	}
	
//	sorted_edges = sort(sorted_edges);
	
	sorted_edges = sortowanie_przez_kopcowanie(sorted_edges, edges_number);
	
//	for(int i=0; i<edges_number; i++) {									// wyœwietlanie posortowanej tablicy krawêdzi
//		cout << sorted_edges[i][0] << " --- " << sorted_edges[i][2] << " : " << sorted_edges[i][1] << endl;
//	}
	
	int* parent = new int[n];
    int* rank = new int[n];
    for (int i=0; i<n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int e = 0;											// indeks elementu tablicy z wierzcho³kami krawêdzi nale¿¹cymi do MST
    for(int i=0; i<edges_number && e<n-1; i++) {		// e < n-1 - jak ju¿ bedzie n-1 krawêdzi to mo¿na szybciej skoñczyæ, poniewa¿ MST ma n-1 krawêdzi
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

int Kruskal_Algorithm::find(int vertex, int *parent) {						// funkcja, która zwraca max_rodzica (identyfiaktor) danego wierzcho³ka
	if(parent[vertex] == vertex)
		return vertex;
	return find(parent[vertex], parent);
}

int* Kruskal_Algorithm::Union(int x, int y, int *parent) {					// funkcja, ktora laczy dwa zbiory (przypisanie jakby tych samych identyfikatorów)
	parent[x] = y;
	return parent;
}

void Kruskal_Algorithm::show_MST(int *result_U, int *result_V, int *result_weight) {
	int sum_weight = 0;
	
	cout<<"MINIMALNE DRZEWO ROZPINAJ¥CE:" << endl << endl;
	
	for(int i=0; i<n-1; i++) {			// n-1 krawêdzi, zaczynamy od wierzcho³ka drugiego, poniewa¿ pierwszy nie ma poprzednika
		cout<<"KrawêdŸ " << i+1 << ": " << result_U[i] << " - " << result_V[i] << " : " << result_weight[i] << endl;
		sum_weight = sum_weight + result_weight[i];
	}
	
	cout << endl << "Waga MST: " << sum_weight << endl;
}

//int** Kruskal_Algorithm::sort(int **sorted_edges) {							// funkcja, która za pomoc¹ algorytmu shella rostuje tablice dynamiczna dwuwymiarow¹ z karwedziami wedlug wag
//	int distance = edges_number;
//	int h;
//	
//	for(int i=1; i<edges_number; i++) {									// sekwencja odstêpów Sedgewick'a
//		if(pow(4,i)+3*pow(2,i-1)+1 >= edges_number) {					// sprawdzane jest dla jakiego i jest maksymalny odstêp
//			h = i-1;													// do h zapisywana jest maksymalna wartoœæ i dla którego odstêp jest mniejszy od n
//			i = edges_number;
//		}
//	}
//	
//	for(int w=h; w>=0; w--) {
//		
//		if(w != 0)														// porównywane s¹ wartoœci pocz¹wszy od elementów odleg³ych o najwiêkszy mo¿lwiy odstêp
//			distance = pow(4,w)+3*pow(2,w-1)+1;
//		
//		if(w == 0) 														// ostatni odstêp to 1 - porównywana ca³a tablica
//			distance = 1;
//		
//    	for(int i=distance; i<edges_number; i++) {
//        	int* pom = sorted_edges[i];
//            int j;
//            for (j=i; j>=distance && sorted_edges[j-distance][1]>pom[1]; j-=distance) {			//porównuje po kolei minimum 2 elementy i zamienia przez wstawianie 
//                sorted_edges[j] = sorted_edges[j-distance];				//przesuwa siê po kolei w prawo i mo¿e porównywaæ wczeœniej ju¿ porównywane liczby z kolejn¹ liczb¹ przesuniêt¹ o distance i siê sortuje
//            }
//            sorted_edges[j] = pom;
//        }
//    }
//    return sorted_edges;
//}

void Kruskal_Algorithm::kopiec(int **sorted_edges, int n, int parentIndex) {
	int left_child_index = 2*parentIndex + 1;					// indeks lewego dziecka
	int right_child_index = 2*parentIndex + 2;					// indeks prawego dziecka
	
	int largest_value_index = parentIndex;						// pocz¹tkowe za³o¿enie
																// porównanie rodzica z potomkakmi o ile istniej¹ i przypisanie do largest_value_index indeksu porównywanego elementu o najwiêkszej wartoœci
	if(left_child_index < n && sorted_edges[left_child_index][1] > sorted_edges[largest_value_index][1])
		largest_value_index = left_child_index;
		
	if(right_child_index < n && sorted_edges[right_child_index][1] > sorted_edges[largest_value_index][1])
		largest_value_index = right_child_index;
		
	if(largest_value_index != parentIndex) {										// jeœli któryœ z potomków by³ wiêkszy od rodzica to zamienia siê go z rodzicem i wywo³uje siê rekurencyjnie funkcje kopiec dla indeksu gdzie znajduje siê stary rodzic (wczeœniej - zamieniony element)
		swap(sorted_edges[largest_value_index], sorted_edges[parentIndex]);
		kopiec(sorted_edges, n, largest_value_index);								// sam indeks najwiêkszej wartoœci po zamianie zostaje na starym miejscu i dla niego wywo³ywana jest funkcja kopiec i idzie siê po kolei w dó³ drzewa
	}
}

void Kruskal_Algorithm::tworzenie_kopca(int **sorted_edges, int edges_number) {		// tworzenie kocpa dla ca³ej tablicy
	for(int i=(edges_number/2)-1; i>=0; i--) {										// sprawdzanie "trójk¹tów" (rodzic i potomkowie) dla ka¿dego rodzica, id¹c od ostatniego rodzica
		kopiec(sorted_edges, edges_number, i);
	}
}

int** Kruskal_Algorithm::sortowanie_przez_kopcowanie(int **sorted_edges, int edges_number) {
	
	tworzenie_kopca(sorted_edges, edges_number);												// tworzenie kocpa dla ca³ej tablicy
	
	for(int i=edges_number-1; i>=0; i--) {	
		swap(sorted_edges[0], sorted_edges[i]);													// ostatni element zamieniany jest z korzeniem (najwiekszym elementem)
		kopiec(sorted_edges, i, 0);																// przywracane s¹ w³aœciwoœci kopca dla tablic pomniejszonej o ostatni element
	}
	
	return sorted_edges;
}

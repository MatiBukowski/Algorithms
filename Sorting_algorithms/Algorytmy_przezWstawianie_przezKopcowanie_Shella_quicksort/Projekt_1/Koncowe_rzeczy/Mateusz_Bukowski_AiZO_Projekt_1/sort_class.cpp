#include <iostream>
#include <chrono>
#include <windows.h>
#include <math.h>
#include <ctime>
#include <cstdlib>

#include "sort_class.h"

using namespace std;

template <typename Fi>
Sort_class<Fi>::Sort_class() {		// konstruktor
}

template <typename Fi> 
Sort_class<Fi>::~Sort_class() {		// destruktor
} 

//------------------------------------------------------------------------------------------------------------------------------------------- sortowanie przez wstawianie

template <typename Fi>
void Sort_class<Fi>::sortowanie_przez_wstawianie(Fi *T, int n) {				//sortowanie przez wstawianie
	Fi pom;
	int j;
	
    for(int i=1; i<n; i++) {				// pocz¹wszy od drugiego elementu wartoœci s¹ po kolei przypiswane do pom i porównywane z wczeœniejszymi
            pom = T[i];
            j = i;
            
            while(j>0 && T[j-1]>pom) {		// jeœli wczeœniejszy element jest wiêkszy od pom to elementowi o indeksie na którym siê znajdujemy przypisywna jest wartoœæ wczeœniejszego elementu
            	T[j] = T[j-1]; 
                j--;
            }
             
            T[j] = pom; 					// elementowi o indeksie na którym siê znajdujemy przypisywna jest wartoœæ pom
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------- sortowanie Shella

template <typename Fi>
void Sort_class<Fi>::sortowanie_shella1(Fi *T, int n) {						//sortowanie shella z wiêksz¹ z³o¿onoœci¹ - O(n^2)
	int distance = n;
	
	for(int w=2; w<=n; w*=2) {								// sekwencja odstêpów Shell'a
		distance /= 2;										// odstêp siê zmniejsza a¿ dojdzie do 1
		
    	for(int i=distance; i<n; i++) {						// dla ka¿dego odstêpu sprawdzane s¹ elementy od odstêpu do n
        	Fi pom = T[i];
            int j;
            for(j=i; j>=distance && T[j-distance]>pom; j-=distance) {		// elementy odleg³e o dany odstêp s¹ porównywane i w razie z³ej kolejnoœci zamieniane przez wstawianie
                T[j] = T[j-distance];
            }
            T[j] = pom;
        }
    }
}

template <typename Fi>
void Sort_class<Fi>::sortowanie_shella2(Fi *T, int n) {						//sortowanie shella z mniejsz¹ z³o¿onoœci¹	- O(n^4/3)
	int distance = n;
	int h;
	
	for(int i=1; i<n; i++) {								// sekwencja odstêpów Sedgewick'a
		if(pow(4,i)+3*pow(2,i-1)+1 >= n) {					// sprawdzane jest dla jakiego i jest maksymalny odstêp
			h = i-1;										// do h zapisywana jest maksymalna wartoœæ i dla którego odstêp jest mniejszy od n
			i = n;
		}
	}
	
	for(int w=h; w>=0; w--) {
		
		if(w != 0)											// porównywane s¹ wartoœci pocz¹wszy od elementów odleg³ych o najwiêkszy mo¿lwiy odstêp
			distance = pow(4,w)+3*pow(2,w-1)+1;
		
		if(w == 0) 											// ostatni odstêp to 1 - porównywana ca³a tablica
			distance = 1;
		
    	for(int i=distance; i<n; i++) {
        	Fi pom = T[i];
            int j;
            for (j=i; j>=distance && T[j-distance]>pom; j-=distance) {		//porównuje po kolei minimum 2 elementy i zamienia przez wstawianie 
                T[j] = T[j-distance];										//przesuwa siê po kolei w prawo i mo¿e porównywaæ wczeœniej ju¿ porównywane liczby z kolejn¹ liczb¹ przesuniêt¹ o distance i siê sortuje
            }
            T[j] = pom;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------- sortowanie quicksort

template <typename Fi>
int Sort_class<Fi>::pivot(int left, int right, char pivotWay) {			// wybór rodzaju pivota
	if(pivotWay == 'l')
		return left;
	else if(pivotWay == 'r')
		return right;
	else if(pivotWay == 'm') 
		return (left+right)/2;
	else if(pivotWay == 'w')
		return left + rand()%(right - left + 1);
}

template <typename Fi>
int Sort_class<Fi>::pivotIndex(Fi *T, int left, int right, char pivotWay) {
	int pivIndex = pivot(left, right, pivotWay);
	Fi pivot = T[pivIndex];							// przypisanie wartoœci pivota
	int j = left;
	
	swap(T[pivIndex], T[right]);					// pivota ustawiany jest na praw¹ stronê, aby nie przeszkadza³ w porównaniach i zamianie
	
	for(int i=left; i<right; i++) {					// podzia³ tablicy na wartoœci mniejsze i wiêksze od pivota
		if(T[i] < pivot) {
			swap(T[i], T[j]);
			j++;
		}
	}
	
	swap(T[j], T[right]);							// zamiana pivota z najbardziej wysuniêt¹ na lewo liczb¹ od niego wiêksz¹ (b¹dŸ równ¹)
	return j;										// zwracanie indeksu pivota
}

template <typename Fi>
void Sort_class<Fi>::quicksort(Fi *T, int left, int right, char pivotWay) {
	
	if(left < right) {
		int pivIndex = pivotIndex(T, left, right, pivotWay);		// indeks pivota
		quicksort(T, left, pivIndex-1, pivotWay);					// wywo³ywanie funkcji quicksort dla lewej podtablicy
		quicksort(T, pivIndex+1, right, pivotWay);					// wywo³ywanie funkcji quicksort dla prawej podtablicy
	}
	
}

template <typename Fi>
void Sort_class<Fi>::sortowanie_quicksort(Fi *T, int n, char wybor) {
	srand(time(NULL));
	
	quicksort(T, 0, n-1, wybor);									// wywo³ywanie funkcji quicksort dla ca³ej tablicy
}

//------------------------------------------------------------------------------------------------------------------------------------------- sortowanie przez kopcowanie

template <typename Fi>
void Sort_class<Fi>::kopiec(Fi *T, int n, int parentIndex) {
	int left_child_index = 2*parentIndex + 1;					// indeks lewego dziecka
	int right_child_index = 2*parentIndex + 2;					// indeks prawego dziecka
	
	int largest_value_index = parentIndex;						// pocz¹tkowe za³o¿enie
																// porównanie rodzica z potomkakmi o ile istniej¹ i przypisanie do largest_value_index indeksu porównywanego elementu o najwiêkszej wartoœci
	if(left_child_index < n && T[left_child_index] > T[largest_value_index])
		largest_value_index = left_child_index;
		
	if(right_child_index < n && T[right_child_index] > T[largest_value_index])
		largest_value_index = right_child_index;
		
	if(largest_value_index != parentIndex) {					// jeœli któryœ z potomków by³ wiêkszy od rodzica to zamienia siê go z rodzicem i wywo³uje siê rekurencyjnie funkcje kopiec dla indeksu gdzie znajduje siê stary rodzic (wczeœniej - zamieniony element)
		swap(T[largest_value_index], T[parentIndex]);
		kopiec(T, n, largest_value_index);					// sam indeks najwiêkszej wartoœci po zamianie zostaje na starym miejscu i dla niego wywo³ywana jest funkcja kopiec i idzie siê po kolei w dó³ drzewa
	}
}

template <typename Fi>
void Sort_class<Fi>::tworzenie_kopca(Fi *T, int n) {			// tworzenie kocpa dla ca³ej tablicy
	for(int i=(n/2)-1; i>=0; i--) {								// sprawdzanie "trójk¹tów" (rodzic i potomkowie) dla ka¿dego rodzica, id¹c od ostatniego rodzica
		kopiec(T, n, i);
	}
}

template <typename Fi>
void Sort_class<Fi>::sortowanie_przez_kopcowanie(Fi *T, int n) {
	
	tworzenie_kopca(T, n);										// tworzenie kocpa dla ca³ej tablicy
	
	for(int i=n-1; i>=0; i--) {	
		swap(T[0], T[i]);										// ostatni element zamieniany jest z korzeniem (najwiekszym elementem)
		kopiec(T, i, 0);										// przywracane s¹ w³aœciwoœci kopca dla tablic pomniejszonej o ostatni element
	}
}


template class Sort_class<int>;									// wywo³ywanie instancji klasy szablonowej "Sort_class" dla typu danych int
template class Sort_class<float>;								// wywo³ywanie instancji klasy szablonowej "Sort_class" dla typu danych float



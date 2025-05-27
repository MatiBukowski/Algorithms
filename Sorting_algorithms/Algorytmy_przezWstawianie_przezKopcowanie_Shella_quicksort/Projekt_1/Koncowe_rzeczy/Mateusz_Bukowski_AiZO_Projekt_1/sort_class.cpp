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
	
    for(int i=1; i<n; i++) {				// pocz�wszy od drugiego elementu warto�ci s� po kolei przypiswane do pom i por�wnywane z wcze�niejszymi
            pom = T[i];
            j = i;
            
            while(j>0 && T[j-1]>pom) {		// je�li wcze�niejszy element jest wi�kszy od pom to elementowi o indeksie na kt�rym si� znajdujemy przypisywna jest warto�� wcze�niejszego elementu
            	T[j] = T[j-1]; 
                j--;
            }
             
            T[j] = pom; 					// elementowi o indeksie na kt�rym si� znajdujemy przypisywna jest warto�� pom
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------- sortowanie Shella

template <typename Fi>
void Sort_class<Fi>::sortowanie_shella1(Fi *T, int n) {						//sortowanie shella z wi�ksz� z�o�ono�ci� - O(n^2)
	int distance = n;
	
	for(int w=2; w<=n; w*=2) {								// sekwencja odst�p�w Shell'a
		distance /= 2;										// odst�p si� zmniejsza a� dojdzie do 1
		
    	for(int i=distance; i<n; i++) {						// dla ka�dego odst�pu sprawdzane s� elementy od odst�pu do n
        	Fi pom = T[i];
            int j;
            for(j=i; j>=distance && T[j-distance]>pom; j-=distance) {		// elementy odleg�e o dany odst�p s� por�wnywane i w razie z�ej kolejno�ci zamieniane przez wstawianie
                T[j] = T[j-distance];
            }
            T[j] = pom;
        }
    }
}

template <typename Fi>
void Sort_class<Fi>::sortowanie_shella2(Fi *T, int n) {						//sortowanie shella z mniejsz� z�o�ono�ci�	- O(n^4/3)
	int distance = n;
	int h;
	
	for(int i=1; i<n; i++) {								// sekwencja odst�p�w Sedgewick'a
		if(pow(4,i)+3*pow(2,i-1)+1 >= n) {					// sprawdzane jest dla jakiego i jest maksymalny odst�p
			h = i-1;										// do h zapisywana jest maksymalna warto�� i dla kt�rego odst�p jest mniejszy od n
			i = n;
		}
	}
	
	for(int w=h; w>=0; w--) {
		
		if(w != 0)											// por�wnywane s� warto�ci pocz�wszy od element�w odleg�ych o najwi�kszy mo�lwiy odst�p
			distance = pow(4,w)+3*pow(2,w-1)+1;
		
		if(w == 0) 											// ostatni odst�p to 1 - por�wnywana ca�a tablica
			distance = 1;
		
    	for(int i=distance; i<n; i++) {
        	Fi pom = T[i];
            int j;
            for (j=i; j>=distance && T[j-distance]>pom; j-=distance) {		//por�wnuje po kolei minimum 2 elementy i zamienia przez wstawianie 
                T[j] = T[j-distance];										//przesuwa si� po kolei w prawo i mo�e por�wnywa� wcze�niej ju� por�wnywane liczby z kolejn� liczb� przesuni�t� o distance i si� sortuje
            }
            T[j] = pom;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------- sortowanie quicksort

template <typename Fi>
int Sort_class<Fi>::pivot(int left, int right, char pivotWay) {			// wyb�r rodzaju pivota
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
	Fi pivot = T[pivIndex];							// przypisanie warto�ci pivota
	int j = left;
	
	swap(T[pivIndex], T[right]);					// pivota ustawiany jest na praw� stron�, aby nie przeszkadza� w por�wnaniach i zamianie
	
	for(int i=left; i<right; i++) {					// podzia� tablicy na warto�ci mniejsze i wi�ksze od pivota
		if(T[i] < pivot) {
			swap(T[i], T[j]);
			j++;
		}
	}
	
	swap(T[j], T[right]);							// zamiana pivota z najbardziej wysuni�t� na lewo liczb� od niego wi�ksz� (b�d� r�wn�)
	return j;										// zwracanie indeksu pivota
}

template <typename Fi>
void Sort_class<Fi>::quicksort(Fi *T, int left, int right, char pivotWay) {
	
	if(left < right) {
		int pivIndex = pivotIndex(T, left, right, pivotWay);		// indeks pivota
		quicksort(T, left, pivIndex-1, pivotWay);					// wywo�ywanie funkcji quicksort dla lewej podtablicy
		quicksort(T, pivIndex+1, right, pivotWay);					// wywo�ywanie funkcji quicksort dla prawej podtablicy
	}
	
}

template <typename Fi>
void Sort_class<Fi>::sortowanie_quicksort(Fi *T, int n, char wybor) {
	srand(time(NULL));
	
	quicksort(T, 0, n-1, wybor);									// wywo�ywanie funkcji quicksort dla ca�ej tablicy
}

//------------------------------------------------------------------------------------------------------------------------------------------- sortowanie przez kopcowanie

template <typename Fi>
void Sort_class<Fi>::kopiec(Fi *T, int n, int parentIndex) {
	int left_child_index = 2*parentIndex + 1;					// indeks lewego dziecka
	int right_child_index = 2*parentIndex + 2;					// indeks prawego dziecka
	
	int largest_value_index = parentIndex;						// pocz�tkowe za�o�enie
																// por�wnanie rodzica z potomkakmi o ile istniej� i przypisanie do largest_value_index indeksu por�wnywanego elementu o najwi�kszej warto�ci
	if(left_child_index < n && T[left_child_index] > T[largest_value_index])
		largest_value_index = left_child_index;
		
	if(right_child_index < n && T[right_child_index] > T[largest_value_index])
		largest_value_index = right_child_index;
		
	if(largest_value_index != parentIndex) {					// je�li kt�ry� z potomk�w by� wi�kszy od rodzica to zamienia si� go z rodzicem i wywo�uje si� rekurencyjnie funkcje kopiec dla indeksu gdzie znajduje si� stary rodzic (wcze�niej - zamieniony element)
		swap(T[largest_value_index], T[parentIndex]);
		kopiec(T, n, largest_value_index);					// sam indeks najwi�kszej warto�ci po zamianie zostaje na starym miejscu i dla niego wywo�ywana jest funkcja kopiec i idzie si� po kolei w d� drzewa
	}
}

template <typename Fi>
void Sort_class<Fi>::tworzenie_kopca(Fi *T, int n) {			// tworzenie kocpa dla ca�ej tablicy
	for(int i=(n/2)-1; i>=0; i--) {								// sprawdzanie "tr�jk�t�w" (rodzic i potomkowie) dla ka�dego rodzica, id�c od ostatniego rodzica
		kopiec(T, n, i);
	}
}

template <typename Fi>
void Sort_class<Fi>::sortowanie_przez_kopcowanie(Fi *T, int n) {
	
	tworzenie_kopca(T, n);										// tworzenie kocpa dla ca�ej tablicy
	
	for(int i=n-1; i>=0; i--) {	
		swap(T[0], T[i]);										// ostatni element zamieniany jest z korzeniem (najwiekszym elementem)
		kopiec(T, i, 0);										// przywracane s� w�a�ciwo�ci kopca dla tablic pomniejszonej o ostatni element
	}
}


template class Sort_class<int>;									// wywo�ywanie instancji klasy szablonowej "Sort_class" dla typu danych int
template class Sort_class<float>;								// wywo�ywanie instancji klasy szablonowej "Sort_class" dla typu danych float



#include <iostream>

using namespace std;
template<typename Fi>

class Sort_class {											// klasa zawieraj�ca funkcje wszystkich badanych algorytm�w sortowania 
	
	int n;													// zmienna przechowuj�ca wielko�� tablicy
	Fi *T;													// wska�nik, kt�ry wskazuje na tablic� dynamicn�
	
	public:
		
	Sort_class();											// konstruktor
	~Sort_class();											// destruktor
	
	// funkcja do sortowania przez wstawianie
	void sortowanie_przez_wstawianie(Fi *, int);			// funkcja zawieraj�ca algorytm sortowania przez wstawianie. Jako argumenty przyjmuje wska�nik na sortowan� tablic� dynamiczn� oraz wielko�� sortowanej tablicy 
															
	// funkcje do sortowania Shella
	void sortowanie_shella1(Fi *, int);						// funkcja zawieraj�ca algorytm sortowania Shella o z�o�ono�ci O(n^2). Jako argumenty przyjmuje wska�nik na sortowan� tablic� dynamiczn� oraz wielko�� sortowanej tablicy
	void sortowanie_shella2(Fi *, int);						// funkcja zawieraj�ca algorytm sortowania Shella o z�o�ono�ci O(n^4/3). Jako argumenty przyjmuje wska�nik na sortowan� tablic� dynamiczn� oraz wielko�� sortowanej tablicy
			
	// funckje do sortowania quicksort												
	int pivot(int, int, char);								// funkcja zwracaj�ca index pivota w zale�no�ci od wyboru u�ytkownika (char), oraz lewego i prawego elementu danej tablicy/podtablicy
	int pivotIndex(Fi *, int, int, char);					// funkcja, w kt�rej nast�puje podzia� tablicy na podtablice z elementami mniejszymi i wi�kszymi od pivota, a nast�pnie zwracany jest index pivota
	void quicksort(Fi *, int, int, char);					// funkcja, w kt�rej wywo�ywane s� rekurencyjnie funkcje quicksort dla podtablic z elemntami mniejszymi i wi�kszymi od pivota
	void sortowanie_quicksort(Fi *, int, char);				// pierwsza wywo�ywana funkcja, w kt�rej wywo�ywana jest funkcja quicksort dla ca�ej sortowanej tablicy
	
	// funkcje do sortowania przez kopcowanie
	void kopiec(Fi *, int, int);							// funkcja, w kt�rej dla ka�dego rodzica i jego potomk�w w razie kolejno�ci niezgodenj z w�a�ciwo�ciami kopca zamieniana jest kolejnos� element�w, a nast�pnie 
															// rekurencyjnie ta funkcja jest wywo�ywana w d� drzewa
	void tworzenie_kopca(Fi *, int);						// funckja, w kt�rej tworzony jest kopopiec z ca�ej pocz�tkowej tablicy
	void sortowanie_przez_kopcowanie(Fi *, int);			// pierwsza wywo�ywana funkcja, w kt�rej wywolywana jest na poczatku funkcja tworz�ca kopiec z element�w z sortowanej tablicy, a nast�pnie po kolei
															// dla ka�dego elemntu od ty�u zamiieniany jest korze� z nim i potem przywracane s� w���ciwo�ci kopca i tak, a� do pierwszego elementu 
};

#include <iostream>

using namespace std;
template<typename Fi>

class Sort_class {											// klasa zawieraj¹ca funkcje wszystkich badanych algorytmów sortowania 
	
	int n;													// zmienna przechowuj¹ca wielkoœæ tablicy
	Fi *T;													// wskaŸnik, który wskazuje na tablicê dynamicn¹
	
	public:
		
	Sort_class();											// konstruktor
	~Sort_class();											// destruktor
	
	// funkcja do sortowania przez wstawianie
	void sortowanie_przez_wstawianie(Fi *, int);			// funkcja zawieraj¹ca algorytm sortowania przez wstawianie. Jako argumenty przyjmuje wskaŸnik na sortowan¹ tablicê dynamiczn¹ oraz wielkoœæ sortowanej tablicy 
															
	// funkcje do sortowania Shella
	void sortowanie_shella1(Fi *, int);						// funkcja zawieraj¹ca algorytm sortowania Shella o z³o¿onoœci O(n^2). Jako argumenty przyjmuje wskaŸnik na sortowan¹ tablicê dynamiczn¹ oraz wielkoœæ sortowanej tablicy
	void sortowanie_shella2(Fi *, int);						// funkcja zawieraj¹ca algorytm sortowania Shella o z³o¿onoœci O(n^4/3). Jako argumenty przyjmuje wskaŸnik na sortowan¹ tablicê dynamiczn¹ oraz wielkoœæ sortowanej tablicy
			
	// funckje do sortowania quicksort												
	int pivot(int, int, char);								// funkcja zwracaj¹ca index pivota w zale¿noœci od wyboru u¿ytkownika (char), oraz lewego i prawego elementu danej tablicy/podtablicy
	int pivotIndex(Fi *, int, int, char);					// funkcja, w której nastêpuje podzia³ tablicy na podtablice z elementami mniejszymi i wiêkszymi od pivota, a nastêpnie zwracany jest index pivota
	void quicksort(Fi *, int, int, char);					// funkcja, w której wywo³ywane s¹ rekurencyjnie funkcje quicksort dla podtablic z elemntami mniejszymi i wiêkszymi od pivota
	void sortowanie_quicksort(Fi *, int, char);				// pierwsza wywo³ywana funkcja, w której wywo³ywana jest funkcja quicksort dla ca³ej sortowanej tablicy
	
	// funkcje do sortowania przez kopcowanie
	void kopiec(Fi *, int, int);							// funkcja, w której dla ka¿dego rodzica i jego potomków w razie kolejnoœci niezgodenj z w³aœciwoœciami kopca zamieniana jest kolejnosæ elementów, a nastêpnie 
															// rekurencyjnie ta funkcja jest wywo³ywana w dó³ drzewa
	void tworzenie_kopca(Fi *, int);						// funckja, w której tworzony jest kopopiec z ca³ej pocz¹tkowej tablicy
	void sortowanie_przez_kopcowanie(Fi *, int);			// pierwsza wywo³ywana funkcja, w której wywolywana jest na poczatku funkcja tworz¹ca kopiec z elementów z sortowanej tablicy, a nastêpnie po kolei
															// dla ka¿dego elemntu od ty³u zamiieniany jest korzeñ z nim i potem przywracane s¹ w³¹œciwoœci kopca i tak, a¿ do pierwszego elementu 
};

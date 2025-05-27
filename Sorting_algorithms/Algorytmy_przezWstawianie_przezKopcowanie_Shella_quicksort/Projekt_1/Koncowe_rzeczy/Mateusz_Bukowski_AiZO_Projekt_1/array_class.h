#ifndef ARRAY_CLASS_H		// sprawdza czy plik nag³owkowy nie zosta³ ju¿ wczœniej zdefiniowany, jeœli nie, to kod miêdzy ifndef a endif jest kompilowany
#define ARRAY_CLASS_H

#include <iostream>

using namespace std;
template<typename Fi>

class Array_class {			// klasa przechowuj¹ca tablicê dynamiczn¹, która bedzie sortowana oraz zawieraj¹ca podstawowe funkcje dla tej tablicy
	
	int n;					// zmienna przechowuj¹ca wielkoœæ tablicy
	Fi *T; 					// wskaŸnik, który wskazuje na tablicê dynamicn¹
	
	public:
	Array_class(int);			// konstruktor
	~Array_class();				// destruktor
	void create_array();		// funkcja, która tworzy tablicê dynamiczn¹ i przypisuje na ni¹ wskaŸnik *T
	void add_data(Fi, int);		// funkcja, która dodaje do tablic dynamicznej kolejne lementy. Jako dane przyjmuje wskaŸnik na tablicê dynamiczn¹ oraz indeks elementu e tablicy
	Fi get_data(int);			// funkcja zwracaj¹ca element z tablic o danym indeksie
	Fi* get_array();			// funkcja zwracaj¹ca tablicê dynammiczn¹
	void show_array();			// funkcja wyœwietlaj¹ca ca³¹ tablicê dynamiczn¹
};

#endif


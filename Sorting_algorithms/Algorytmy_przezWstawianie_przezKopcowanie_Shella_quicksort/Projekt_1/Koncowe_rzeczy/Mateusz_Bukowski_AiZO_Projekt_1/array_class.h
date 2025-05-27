#ifndef ARRAY_CLASS_H		// sprawdza czy plik nag�owkowy nie zosta� ju� wcz�niej zdefiniowany, je�li nie, to kod mi�dzy ifndef a endif jest kompilowany
#define ARRAY_CLASS_H

#include <iostream>

using namespace std;
template<typename Fi>

class Array_class {			// klasa przechowuj�ca tablic� dynamiczn�, kt�ra bedzie sortowana oraz zawieraj�ca podstawowe funkcje dla tej tablicy
	
	int n;					// zmienna przechowuj�ca wielko�� tablicy
	Fi *T; 					// wska�nik, kt�ry wskazuje na tablic� dynamicn�
	
	public:
	Array_class(int);			// konstruktor
	~Array_class();				// destruktor
	void create_array();		// funkcja, kt�ra tworzy tablic� dynamiczn� i przypisuje na ni� wska�nik *T
	void add_data(Fi, int);		// funkcja, kt�ra dodaje do tablic dynamicznej kolejne lementy. Jako dane przyjmuje wska�nik na tablic� dynamiczn� oraz indeks elementu e tablicy
	Fi get_data(int);			// funkcja zwracaj�ca element z tablic o danym indeksie
	Fi* get_array();			// funkcja zwracaj�ca tablic� dynammiczn�
	void show_array();			// funkcja wy�wietlaj�ca ca�� tablic� dynamiczn�
};

#endif


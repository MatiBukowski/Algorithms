#include <iostream>

#include "array_class.h"

using namespace std;

template<typename Fi>
Array_class<Fi>::Array_class(int N) {			// konstruktor
	n = N;
}

template<typename Fi>
Array_class<Fi>::~Array_class() {
	delete [] T;								// destruktor - usuwanie tablicy dynamicznej
}

template<typename Fi>
void Array_class<Fi>::create_array() {
	T = new Fi[n];								// tworzenie tablicy dynamicznej o n elementach
}

template<typename Fi>
void Array_class<Fi>::add_data(Fi x, int i) {	// przypisywanie kolejnych elementów do tablicy dynamicznej
	T[i] = x;
}

template<typename Fi>
Fi Array_class<Fi>::get_data(int i) {			// zwracanie elementu o indeksie i
	return T[i];
}

template<typename Fi>
Fi* Array_class<Fi>::get_array() {				// zwracanie tablicy dynamicznej 
	return T;
}

template<typename Fi>
void Array_class<Fi>::show_array() {			// wyœwietlanie wygenerowanej tablicy dynamicznej
	cout << "Tablica: ";
	for(int i=0; i<n; i++) {
		cout << T[i] << " ";
	}
}

template class Array_class<int>;				// wywo³ywanie instancji klasy szablonowej "Array_class" dla typu danych int
template class Array_class<float>;				// wywo³ywanie instancji klasy szablonowej "Array_class" dla typu danych float



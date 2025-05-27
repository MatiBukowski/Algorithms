#include <iostream>

#include "array_class.h"
using namespace std;

void menu_sort();											// funkcja wy�wietlaj�ac menu wybor�w r�nych algorytm�w sortowania an ekranie
void sort_choice_switch(int);								// funkcja odpowiedzialna za dalsze dzia�ania programu w zale�no�ci algorytmu sortowania jaki wybra� u�ytkownik
void check_correct(int);									// funkcja sprawdzaj�ca poprawno�� posortowania
void set_arrays_int(Array_class<int> *);					// z funkcji choice_switch z pliku menu.cpp do tej funkcji przekazywana jest kopia wygenerowanej tablicy do posortowania z elementami int, aby w pliku menu_sort.cpp mo�na by�o na niej operowa�
void set_arrays_float(Array_class<float> *);				// z funkcji choice_switch z pliku menu.cpp do tej funkcji przekazywana jest kopia wygenerowanej tablicy do posortowania z elementami float, aby w pliku menu_sort.cpp mo�na by�o na niej operowa�

#include <iostream>

#include "array_class.h"
using namespace std;

void menu_sort();											// funkcja wyœwietlaj¹ac menu wyborów ró¿nych algorytmów sortowania an ekranie
void sort_choice_switch(int);								// funkcja odpowiedzialna za dalsze dzia³ania programu w zale¿noœci algorytmu sortowania jaki wybra³ u¿ytkownik
void check_correct(int);									// funkcja sprawdzaj¹ca poprawnoœæ posortowania
void set_arrays_int(Array_class<int> *);					// z funkcji choice_switch z pliku menu.cpp do tej funkcji przekazywana jest kopia wygenerowanej tablicy do posortowania z elementami int, aby w pliku menu_sort.cpp mo¿na by³o na niej operowaæ
void set_arrays_float(Array_class<float> *);				// z funkcji choice_switch z pliku menu.cpp do tej funkcji przekazywana jest kopia wygenerowanej tablicy do posortowania z elementami float, aby w pliku menu_sort.cpp mo¿na by³o na niej operowaæ

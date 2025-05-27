#include <iostream>
#include <chrono>
#include <fstream>

#include "menu_sort.h"
#include "sort_class.h"
#include "array_class.h"

using namespace std;

Array_class<int> *tab_int_copy_2 = NULL;		// deklarowanie wska�nika na obiekt klasy Array_class o typie danych int i przypisywanie mu warto�ci NULL - kopia wygenerowanej tablic przekazana z pliku menu.cpp
Array_class<float> *tab_float_copy_2 = NULL;	// deklarowanie wska�nika na obiekt klasy Array_class o typie danych float i przypisywanie mu warto�ci NULL - kopia wygenerowanej tablic przekazana z pliku menu.cpp

Sort_class<int> sort_int;						// tworzenie obiektu klasy Sort_class dla danych typu int - aby wywo�ywa� z tej klasy funkcje wywo�uj�ce algorytmy sortowa�
Sort_class<float> sort_float;					// tworzenie obiektu klasy Sort_class dla danych typu float - aby wywo�ywa� z tej klasy funkcje wywo�uj�ce algorytmy sortowa�

// ofstream file;								// deklaracja pliku do zapisywania wynik�w pomiar�w do sprawozdania

void menu_sort() {		// menu wyboru algorytm�w sortowania
	cout << "----------------------------------ALGORITHMS_MENU----------------------------------" << endl;
	cout << "1 - sortowanie przez wstawianie" << endl;
	cout << "2 - sortowanie przez kopcowanie" << endl;
	cout << "3 - sortowanie Shella" << endl;
	cout << "4 - sortowanie szybkie (quicksort)" << endl;
	cout << "-----------------------------------------------------------------------------------" << endl;
}

void sort_choice_switch(int N) {		// wyb�r algorytmu sortowania prez u�ytkownika na podstawie menu_sort
	int choice;		// zmienna przechowuj�ca wyb�r uzytkowika
	
//	file.open("czasy.txt", ios::app);	// do sprawozdania
	
	cout << "Podaj wyb�r: ";
	cin >> choice;
	system("cls");
	
	switch(choice) {
		case 1: {		// wywo�anie algorytmu sortowania przez wstawianie
		
//			Array_class<int> *tab_int_copy_help = NULL;			// tworzenie pomocniczych tablic do zbierania pomiar�w do sprawozdania
//			Array_class<float> *tab_float_copy_help = NULL;
//			if(tab_int_copy_2) {
//				tab_int_copy_help=new Array_class<int>(N);
//				tab_int_copy_help->create_array();
//			}
//			if(tab_float_copy_2) {
//				tab_float_copy_help=new Array_class<float>(N);
//				tab_float_copy_help->create_array();
//			}
			
//			for(int j=0; j<50; j++) {
			
//			for(int i=0; i<N; i++) {
//				if(tab_int_copy_2) {
//					tab_int_copy_help->add_data(tab_int_copy_2->get_data(i),i);
//				}
//				if(tab_float_copy_2) {
//					tab_float_copy_help->add_data(tab_float_copy_2->get_data(i),i);
//				}
//				}
				
			auto start_time = chrono::high_resolution_clock::now();			// rozpocz�cie mierzenia czasu
				if(tab_int_copy_2) {	// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania przez wstawianie dla danych typu int i przekazywanie jej kopii tablicy i wielko�ci tablicy
					sort_int.sortowanie_przez_wstawianie(tab_int_copy_2->get_array(), N);
				} else if(tab_float_copy_2) {	// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania przez wstawianie dla danych typu float i przekazywanie jej kopii tablicy i wielko�ci tablicy
					sort_float.sortowanie_przez_wstawianie(tab_float_copy_2->get_array(), N);
				}
			
			auto end_time = chrono::high_resolution_clock::now();			// zako�czenie mierzenia czasu
    		auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();		// policzenie czasu sortowania
    		cout << "Sorting time: " << time << " ms"<< endl << endl;
//    		file<<time<<endl;
//    	}
			break;
		}
		case 2: {		// wywo�anie algorytmu sortowania przez kopcowanie
			
//			Array_class<int> *tab_int_copy_help = NULL;			// tworzenie pomocniczych tablic do zbierania pomiar�w do sprawozdania
//			Array_class<float> *tab_float_copy_help = NULL;
//			if(tab_int_copy_2) {
//				tab_int_copy_help=new Array_class<int>(N);
//				tab_int_copy_help->create_array();
//			}
//			if(tab_float_copy_2) {
//				tab_float_copy_help=new Array_class<float>(N);
//				tab_float_copy_help->create_array();
//			}
			
//			for(int j=0; j<50; j++) {
			
//			for(int i=0; i<N; i++) {
//				if(tab_int_copy_2) {
//					tab_int_copy_help->add_data(tab_int_copy_2->get_data(i),i);
//				}
//				if(tab_float_copy_2) {
//					tab_float_copy_help->add_data(tab_float_copy_2->get_data(i),i);
//				}
//				}
				
			auto start_time = chrono::high_resolution_clock::now();			// rozpocz�cie mierzenia czasu
				if(tab_int_copy_2) {	// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania przez kopcowanie dla danych typu int i przekazywanie jej kopii tablicy i wielko�ci tablicy
					sort_int.sortowanie_przez_kopcowanie(tab_int_copy_2->get_array(), N);
				} else if(tab_float_copy_2) {	// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania przez kopcowanie dla danych typu float i przekazywanie jej kopii tablicy i wielko�ci tablicy
					sort_float.sortowanie_przez_kopcowanie(tab_float_copy_2->get_array(), N);
				}
				
			auto end_time = chrono::high_resolution_clock::now();			// zako�czenie mierzenia czasu
    		auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();		// policzenie czasu sortowania
    		cout << "Sorting time: " << time << " ms"<< endl << endl;
//    		file<<time<<endl;
//    	}
			break;
		}
		case 3: {		// wywo�anie algorytmu sortowania Shella
			int choice2 = 3;	// zmienna przechowuj�ca wyb�r u�ywtkownika z�o�ono�ci algorytmu Shella
			
			cout << "1 - z�o�ono�� n^2" << endl;
			cout << "2 - z�o�ono�� n^(4/3)" << endl << endl;
			
			while(choice2 != 1 && choice2 != 2) {
				cout << "Podaj wyb�r: ";
				cin >> choice2;
			}
			
//			Array_class<int> *tab_int_copy_help = NULL;			// tworzenie pomocniczych tablic do zbierania pomiar�w do sprawozdania
//			Array_class<float> *tab_float_copy_help = NULL;
//			if(tab_int_copy_2) {
//				tab_int_copy_help=new Array_class<int>(N);
//				tab_int_copy_help->create_array();
//			}
//			if(tab_float_copy_2) {
//				tab_float_copy_help=new Array_class<float>(N);
//				tab_float_copy_help->create_array();
//			}
//			
//			for(int j=0; j<50; j++) {
//			
//			for(int i=0; i<N; i++) {
//				if(tab_int_copy_2) {
//					tab_int_copy_help->add_data(tab_int_copy_2->get_data(i),i);
//				}
//				if(tab_float_copy_2) {
//					tab_float_copy_help->add_data(tab_float_copy_2->get_data(i),i);
//				}
//				}
			
			auto start_time = chrono::high_resolution_clock::now();			// rozpocz�cie mierzenia czasu
			if(tab_int_copy_2) {	// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania Shella o wybranej z�o�ono�ci dla danych typu int i przekazywanie jej kopii tablicy i wielko�ci tablicy
					if(choice2 == 1)
						sort_int.sortowanie_shella1(tab_int_copy_2->get_array(), N);
					else if(choice2 == 2)
						sort_int.sortowanie_shella2(tab_int_copy_2->get_array(), N);
						
				} else if(tab_float_copy_2) {	// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania Shella o wybranej z�o�ono�ci dla danych typu float i przekazywanie jej kopii tablicy i wielko�ci tablicy
					if(choice2 == 1)
						sort_float.sortowanie_shella1(tab_float_copy_2->get_array(), N);
					else if(choice2 == 2)
						sort_float.sortowanie_shella2(tab_float_copy_2->get_array(), N);
				}
				
			auto end_time = chrono::high_resolution_clock::now();			// zako�czenie mierzenia czasu
    		auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();		// policzenie czasu sortowania
    		cout << "Sorting time: " << time << " ms"<< endl << endl;
//    		file<<time<<endl;
//    	}
			break;
		}
		case 4: {		// wywo�anie algorytmu sortowania quicksort
			char wybor = 'o';	// zmienna przechowuj�ca wyb�r u�ywtkownika przypadku algorytmu sortowaina quicksort
	
			cout << "l - pivot skrajnie lewy" << endl;
			cout << "r - pivot skrajnie prawy" << endl;
			cout << "m - pivot �rodkowy" << endl;
			cout << "w - pivot losowy" << endl << endl;
	
			while(wybor != 'l' && wybor != 'r' && wybor != 'm' && wybor != 'w') {
				cout << "Podaj wyb�r: ";
				cin >> wybor;
			}
			
//			Array_class<int> *tab_int_copy_help = NULL;
//			Array_class<float> *tab_float_copy_help = NULL;
//			if(tab_int_copy_2) {
//				tab_int_copy_help=new Array_class<int>(N);
//				tab_int_copy_help->create_array();
//			}
//			if(tab_float_copy_2) {
//				tab_float_copy_help=new Array_class<float>(N);
//				tab_float_copy_help->create_array();
//			}
//			
//			for(int j=0; j<50; j++) {
//			
//			for(int i=0; i<N; i++) {
//				if(tab_int_copy_2) {
//					tab_int_copy_help->add_data(tab_int_copy_2->get_data(i),i);
//				}
//				if(tab_float_copy_2) {
//					tab_float_copy_help->add_data(tab_float_copy_2->get_data(i),i);
//				}
//				}
			
			auto start_time = chrono::high_resolution_clock::now();		// rozpocz�cie mierzenia czasu
				if(tab_int_copy_2) {	// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania quicksort dla wybranego przypadku dla danych typu int i przekazywanie jej kopii tablicy, wielko�ci tablicy i wyboru przypadku
					sort_int.sortowanie_quicksort(tab_int_copy_2->get_array(), N, wybor);
				}
				else if(tab_float_copy_2) {		// wywo�ywanie funkcji wywo�uj�cej algorytm sortowania quicksort dla wybranego przypadku dla danych typu float i przekazywanie jej kopii tablicy, wielko�ci tablicy i wyboru przypadku
					sort_float.sortowanie_quicksort(tab_float_copy_2->get_array(), N, wybor);
				}
			
			auto end_time = chrono::high_resolution_clock::now();		// zako�czenie mierzenia czasu
    		auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();		// policzenie czasu sortowania
    		cout<< "Sorting time: " << time << " ms"<< endl << endl;
//    		file<<time<<endl;
//    	}
    		break;
		}
		default: 
			cout << "niepoprawny numer polecenia" << endl << endl;
	}
	
//	file.close();
}

void check_correct(int N) {		// sprawdzanie poprawno�ci posortowania
int error = 0;					// zmienna przechowuj�ca warto�� 0 lub 1 (1 - wyst�pi� b��d w posortowaniu, 0 - nie wyst�pi� b��d w posortowaniu)

	if(tab_int_copy_2) {
		for(int i=1; i<N; i++) {
			if(tab_int_copy_2->get_data(i-1) > tab_int_copy_2->get_data(i)) {
				error = 1;
				i = N;
				cout << "Poprawno�� posortowania: niepoprawne" << endl << endl;
			}
		}
		
		if(error == 0) cout << "Poprawno�� posortowania: poprawne" << endl << endl;
	} else if (tab_float_copy_2) {
		for(int i=1; i<N; i++) {
			if(tab_float_copy_2->get_data(i-1) > tab_float_copy_2->get_data(i)) {
				error = 1;
				i = N;
				cout << "Poprawno�� posortowania: niepoprawne" << endl << endl;
			}
		}
		
		if(error == 0) cout << "Poprawno�� posortowania: poprawne" << endl << endl;
	}
}

void set_arrays_int(Array_class<int> *x_int) {		// ustawienie zadeklarowanego wska�nika na obiekt Array_class na obiekt przechowuj�cy kopi� tablicy z danymi typu int
	tab_int_copy_2 = x_int;
	tab_float_copy_2 = NULL;
}

void set_arrays_float(Array_class<float> *x_float) {	// ustawienie zadeklarowanego wska�nika na obiekt Array_class na obiekt przechowuj�cy kopi� tablicy z danymi typu float
	tab_float_copy_2 = x_float;
	tab_int_copy_2 = NULL;
}

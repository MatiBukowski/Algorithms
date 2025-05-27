#include <iostream>
#include <chrono>
#include <fstream>

#include "menu_sort.h"
#include "sort_class.h"
#include "array_class.h"

using namespace std;

Array_class<int> *tab_int_copy_2 = NULL;		// deklarowanie wskaŸnika na obiekt klasy Array_class o typie danych int i przypisywanie mu wartoœci NULL - kopia wygenerowanej tablic przekazana z pliku menu.cpp
Array_class<float> *tab_float_copy_2 = NULL;	// deklarowanie wskaŸnika na obiekt klasy Array_class o typie danych float i przypisywanie mu wartoœci NULL - kopia wygenerowanej tablic przekazana z pliku menu.cpp

Sort_class<int> sort_int;						// tworzenie obiektu klasy Sort_class dla danych typu int - aby wywo³ywaæ z tej klasy funkcje wywo³uj¹ce algorytmy sortowañ
Sort_class<float> sort_float;					// tworzenie obiektu klasy Sort_class dla danych typu float - aby wywo³ywaæ z tej klasy funkcje wywo³uj¹ce algorytmy sortowañ

// ofstream file;								// deklaracja pliku do zapisywania wyników pomiarów do sprawozdania

void menu_sort() {		// menu wyboru algorytmów sortowania
	cout << "----------------------------------ALGORITHMS_MENU----------------------------------" << endl;
	cout << "1 - sortowanie przez wstawianie" << endl;
	cout << "2 - sortowanie przez kopcowanie" << endl;
	cout << "3 - sortowanie Shella" << endl;
	cout << "4 - sortowanie szybkie (quicksort)" << endl;
	cout << "-----------------------------------------------------------------------------------" << endl;
}

void sort_choice_switch(int N) {		// wybór algorytmu sortowania prez u¿ytkownika na podstawie menu_sort
	int choice;		// zmienna przechowuj¹ca wybór uzytkowika
	
//	file.open("czasy.txt", ios::app);	// do sprawozdania
	
	cout << "Podaj wybór: ";
	cin >> choice;
	system("cls");
	
	switch(choice) {
		case 1: {		// wywo³anie algorytmu sortowania przez wstawianie
		
//			Array_class<int> *tab_int_copy_help = NULL;			// tworzenie pomocniczych tablic do zbierania pomiarów do sprawozdania
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
				
			auto start_time = chrono::high_resolution_clock::now();			// rozpoczêcie mierzenia czasu
				if(tab_int_copy_2) {	// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania przez wstawianie dla danych typu int i przekazywanie jej kopii tablicy i wielkoœci tablicy
					sort_int.sortowanie_przez_wstawianie(tab_int_copy_2->get_array(), N);
				} else if(tab_float_copy_2) {	// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania przez wstawianie dla danych typu float i przekazywanie jej kopii tablicy i wielkoœci tablicy
					sort_float.sortowanie_przez_wstawianie(tab_float_copy_2->get_array(), N);
				}
			
			auto end_time = chrono::high_resolution_clock::now();			// zakoñczenie mierzenia czasu
    		auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();		// policzenie czasu sortowania
    		cout << "Sorting time: " << time << " ms"<< endl << endl;
//    		file<<time<<endl;
//    	}
			break;
		}
		case 2: {		// wywo³anie algorytmu sortowania przez kopcowanie
			
//			Array_class<int> *tab_int_copy_help = NULL;			// tworzenie pomocniczych tablic do zbierania pomiarów do sprawozdania
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
				
			auto start_time = chrono::high_resolution_clock::now();			// rozpoczêcie mierzenia czasu
				if(tab_int_copy_2) {	// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania przez kopcowanie dla danych typu int i przekazywanie jej kopii tablicy i wielkoœci tablicy
					sort_int.sortowanie_przez_kopcowanie(tab_int_copy_2->get_array(), N);
				} else if(tab_float_copy_2) {	// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania przez kopcowanie dla danych typu float i przekazywanie jej kopii tablicy i wielkoœci tablicy
					sort_float.sortowanie_przez_kopcowanie(tab_float_copy_2->get_array(), N);
				}
				
			auto end_time = chrono::high_resolution_clock::now();			// zakoñczenie mierzenia czasu
    		auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();		// policzenie czasu sortowania
    		cout << "Sorting time: " << time << " ms"<< endl << endl;
//    		file<<time<<endl;
//    	}
			break;
		}
		case 3: {		// wywo³anie algorytmu sortowania Shella
			int choice2 = 3;	// zmienna przechowuj¹ca wybór u¿ywtkownika z³o¿onoœci algorytmu Shella
			
			cout << "1 - z³o¿onoœæ n^2" << endl;
			cout << "2 - z³o¿onoœæ n^(4/3)" << endl << endl;
			
			while(choice2 != 1 && choice2 != 2) {
				cout << "Podaj wybór: ";
				cin >> choice2;
			}
			
//			Array_class<int> *tab_int_copy_help = NULL;			// tworzenie pomocniczych tablic do zbierania pomiarów do sprawozdania
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
			
			auto start_time = chrono::high_resolution_clock::now();			// rozpoczêcie mierzenia czasu
			if(tab_int_copy_2) {	// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania Shella o wybranej z³o¿onoœci dla danych typu int i przekazywanie jej kopii tablicy i wielkoœci tablicy
					if(choice2 == 1)
						sort_int.sortowanie_shella1(tab_int_copy_2->get_array(), N);
					else if(choice2 == 2)
						sort_int.sortowanie_shella2(tab_int_copy_2->get_array(), N);
						
				} else if(tab_float_copy_2) {	// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania Shella o wybranej z³o¿onoœci dla danych typu float i przekazywanie jej kopii tablicy i wielkoœci tablicy
					if(choice2 == 1)
						sort_float.sortowanie_shella1(tab_float_copy_2->get_array(), N);
					else if(choice2 == 2)
						sort_float.sortowanie_shella2(tab_float_copy_2->get_array(), N);
				}
				
			auto end_time = chrono::high_resolution_clock::now();			// zakoñczenie mierzenia czasu
    		auto time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();		// policzenie czasu sortowania
    		cout << "Sorting time: " << time << " ms"<< endl << endl;
//    		file<<time<<endl;
//    	}
			break;
		}
		case 4: {		// wywo³anie algorytmu sortowania quicksort
			char wybor = 'o';	// zmienna przechowuj¹ca wybór u¿ywtkownika przypadku algorytmu sortowaina quicksort
	
			cout << "l - pivot skrajnie lewy" << endl;
			cout << "r - pivot skrajnie prawy" << endl;
			cout << "m - pivot œrodkowy" << endl;
			cout << "w - pivot losowy" << endl << endl;
	
			while(wybor != 'l' && wybor != 'r' && wybor != 'm' && wybor != 'w') {
				cout << "Podaj wybór: ";
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
			
			auto start_time = chrono::high_resolution_clock::now();		// rozpoczêcie mierzenia czasu
				if(tab_int_copy_2) {	// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania quicksort dla wybranego przypadku dla danych typu int i przekazywanie jej kopii tablicy, wielkoœci tablicy i wyboru przypadku
					sort_int.sortowanie_quicksort(tab_int_copy_2->get_array(), N, wybor);
				}
				else if(tab_float_copy_2) {		// wywo³ywanie funkcji wywo³uj¹cej algorytm sortowania quicksort dla wybranego przypadku dla danych typu float i przekazywanie jej kopii tablicy, wielkoœci tablicy i wyboru przypadku
					sort_float.sortowanie_quicksort(tab_float_copy_2->get_array(), N, wybor);
				}
			
			auto end_time = chrono::high_resolution_clock::now();		// zakoñczenie mierzenia czasu
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

void check_correct(int N) {		// sprawdzanie poprawnoœci posortowania
int error = 0;					// zmienna przechowuj¹ca wartoœæ 0 lub 1 (1 - wyst¹pi³ b³¹d w posortowaniu, 0 - nie wyst¹pi³ b³¹d w posortowaniu)

	if(tab_int_copy_2) {
		for(int i=1; i<N; i++) {
			if(tab_int_copy_2->get_data(i-1) > tab_int_copy_2->get_data(i)) {
				error = 1;
				i = N;
				cout << "Poprawnoœæ posortowania: niepoprawne" << endl << endl;
			}
		}
		
		if(error == 0) cout << "Poprawnoœæ posortowania: poprawne" << endl << endl;
	} else if (tab_float_copy_2) {
		for(int i=1; i<N; i++) {
			if(tab_float_copy_2->get_data(i-1) > tab_float_copy_2->get_data(i)) {
				error = 1;
				i = N;
				cout << "Poprawnoœæ posortowania: niepoprawne" << endl << endl;
			}
		}
		
		if(error == 0) cout << "Poprawnoœæ posortowania: poprawne" << endl << endl;
	}
}

void set_arrays_int(Array_class<int> *x_int) {		// ustawienie zadeklarowanego wskaŸnika na obiekt Array_class na obiekt przechowuj¹cy kopiê tablicy z danymi typu int
	tab_int_copy_2 = x_int;
	tab_float_copy_2 = NULL;
}

void set_arrays_float(Array_class<float> *x_float) {	// ustawienie zadeklarowanego wskaŸnika na obiekt Array_class na obiekt przechowuj¹cy kopiê tablicy z danymi typu float
	tab_float_copy_2 = x_float;
	tab_int_copy_2 = NULL;
}

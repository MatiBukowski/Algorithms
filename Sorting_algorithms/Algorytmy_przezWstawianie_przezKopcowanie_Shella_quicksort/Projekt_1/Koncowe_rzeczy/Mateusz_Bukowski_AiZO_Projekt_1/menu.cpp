#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "menu.h"
#include "array_class.h"
#include "menu_sort.h"

using namespace std;

int n;										// deklarowanie zmiennej przechowuj�cej wielko�c tablicy 
Array_class<int> *tab_int = NULL;			// deklarowanie wska�nika na obiekt klasy Array_class o typie danych int i przypisywanie mu warto�ci NULL - wygenerowana tablica z elemenatmi int
Array_class<float> *tab_float = NULL;		// deklarowanie wska�nika na obiekt klasy Array_class o typie danych float i przypisywanie mu warto�ci NULL - wygenerowana tablica z elemenatmi float

Array_class<int> *tab_int_copy = NULL;		// deklarowanie wska�nika na obiekt klasy Array_class o typie danych int i przypisywanie mu warto�ci NULL - kopia tablicy z elemenatmi int
Array_class<float> *tab_float_copy = NULL;	// deklarowanie wska�nika na obiekt klasy Array_class o typie danych float i przypisywanie mu warto�ci NULL	- kopia tablicy z elemenatmi float

void menu() {				// wy�wietlanie g�ownego menu
	cout << "---------------------------------------MENU---------------------------------------" << endl;
	cout << "1 - wczytanie tablicy z pliku o zadanej nazwie" << endl;
	cout << "2 - wygenerowanie tablicy o zadanym rozmiarze zawieraj�ce losowe warto�ci" << endl;
	cout << "3 - wy�wietlenie ostatnio utworzonej tablicy na ekranie" << endl;
	cout << "4 - uruchomienie wybranego algorytmu sortowania na ostatnio utworzonej tablicy" << endl;
	cout << "5 - wy�wietlenie posortowanej tablicy na ekranie" << endl;
	cout << "6 - zako�cz program" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_switch() {		// wyb�r u�ytkownika na podstawie menu i dalsze operacje
	int choice;
	
	cout << "Podaj wyb�r: ";
	cin >> choice;
	system("cls");
	
	switch(choice) {
		case 1: { 	// wczytywanie tablicy z pliku
			tab_int_copy=NULL;
			tab_float_copy=NULL;
			
			char o = 'g';	// zmienna przechowuj�ca wyb�r czy ma by� to tablica int�w czy float�w
			ifstream file;	// wczytywany plik
			string name;	// zmienna przechowuj�ca nazw� wczytywnaego pliku, kt�r� poda� u�ytkownik
			int x_i;		//zmienna przechowuj�ca jeden wiersz z pliku, gdzie wszystkie liczby s� intami
			float x_f;		// zmienna przechowuj�ca jeden wiersz z pliku, gdzie wszystkie liczby s� floatami
			
			
			while(o!='i' && o!='f') {
				cout << "Ma to by� tablica int-�w czy float-�w? (i/f): ";
				cin >> o;
			}
				
			cout << "Podaj nazw� pliku, z kt�rego chcesz wczyta� tablic�: ";
			cin >> name;
			
			file.open((name + ".txt").c_str());			// otwieranie pliku o podanej nazwie
			
			if(file.good()==false) {					// je�li plik si� nie otworzy�
				cout << "Plik nie istnieje" << endl;
			} else {									// je�li plik si� otworzy�
				
				string line;
				int line_number = 1;
				
				while(getline(file, line)){
					if(line_number == 1) {				// pierwszy element - wielko�� tablicy
						stringstream ss;				// stringstream to typ danych, kt�ry pozwala na �atwe konwertowanie danych np. z string na int
						ss << line;
						ss >> n;
						if(tab_float)
							tab_float=NULL;
						if(tab_int)
							tab_int=NULL;
							
					} else {
						stringstream ss;
						ss << line;
						
						if(o=='i') {									// tworzenie tablicy dla danych typu int
							if(tab_int==NULL) {
								ss >> x_i;
								tab_int = new Array_class<int>(n);		// tworzenie obiektu Arrary_class, kt�ry b�dzie przechowywa� tablic� 
								tab_int->create_array();				// tworzenie tablicy 
								tab_int->add_data(x_i, line_number-2);	// dodawanie element�w do tablicy
							}
							else {
								ss >> x_i;
								tab_int->add_data(x_i, line_number-2);
							}
						}
						else if(o=='f') {								// tworzenie tablicy dla danych typu float (analogicznie jak dla int)
							if(tab_float==NULL) {
								ss >> x_f;
								tab_float = new Array_class<float>(n);
								tab_float->create_array();
								tab_float->add_data(x_f, line_number-2);
							}
							else {
								ss >> x_f;
								tab_float->add_data(x_f, line_number-2);
							}
						}
					}
					line_number ++;
				}
			}
			
			file.close();		// zamykanie pliku
			
			cout << endl;
			menu();				// wy�wietlanie menu
			choice_switch();	// u�ytkownik musi wybra� nast�pny krok
			
			break;
		}
		case 2: {	// tworzenie tablicy o wielko�ci podanej przez u�ytkownika
			srand(time(NULL));
			char o = 'g';		// zmienna przechowuj�ca wyb�r czy ma by� to tablica int�w czy float�w
			char c = 'g';		// zmienna przechowuj�ca wyb�r jaki rodzaj tablicy ma to by�
			
			tab_int_copy=NULL;
			tab_float_copy=NULL;
			
			cout << "Podaj wielko�� ��danej tablicy: ";
			cin >> n;
			
			while(o!='i' && o!='f') {
				cout << "Ma to by� tablica int-�w czy float-�w? (i/f): ";
				cin >> o;
			}
				
				if(o=='i') {					// dla wybranych danych typu int wy�wietlanie mo�liwych opcji i generowanie tablicy
					if(tab_float || tab_int) {
						tab_float=NULL;
						tab_int=NULL;
					}

					tab_int = new Array_class<int>(n);
					tab_int->create_array();
					cout << endl << "Typy generowanych tablic: "<<endl;
					cout << "Tablica losowa - l"<<endl;
					cout << "Tablica posortowana rosn�co - r"<<endl;
					cout << "Tablica posortowana malej�co - m"<<endl;
					cout << "Tablica posortowana w 33% - 3"<<endl;
					cout << "Tablica posortowana w 66% - 6"<<endl;
					cout << "Podaj jaki ma by� typ wygenerowanej tablicy?: ";
					cin >> c;
					cout << endl;
					generation_int(n, c);	// funkcja generuj�ca wybrany rodzaj tablicy
					
//					for(int i=0; i<n; i++) {
//						tab_int->add_data(rand()%10001, i);
//					}	
				} else if(o=='f') {			// dla wybranych danych typu float wy�wietlanie mo�liwych opcji i generowanie tablicy
					if(tab_float || tab_int) {
						tab_float=NULL;
						tab_int=NULL;
					}
	
					tab_float = new Array_class<float>(n);
					tab_float->create_array();
					cout << endl << "Typy generowanych tablic: "<<endl;
					cout << "Tablica losowa - l"<<endl;
					cout << "Tablica posortowana rosn�co - r"<<endl;
					cout << "Tablica posortowana malej�co - m"<<endl;
					cout << "Tablica posortowana w 33% - 3"<<endl;
					cout << "Tablica posortowana w 66% - 6"<<endl;
					cout << "Podaj jaki ma by� typ wygenerowanej tablicy?: ";
					cin >> c;
					cout << endl;
					generation_float(n, c);		// funkcja generuj�ca wybrany rodzaj tablicy
//					for(int i=0; i<n; i++) {
//						tab_float->add_data(float(rand())/float((RAND_MAX)) * 10001, i);
//					}
				} else cout << "B��d" << endl;
			
			menu();
			choice_switch();
			break;
		}
		case 3: {		// wy�wietlanie wygenerowanej tablicy
			if(tab_int)
				tab_int->show_array();
			else if(tab_float)
				tab_float->show_array();
			
			cout << endl << endl;
			menu();
			choice_switch();
			break;
		}
		case 4: {		// opcja dla kt�rej b�dzie przeprowadzane sortowanie tablicy

			if(tab_int) {			// tworzony jest nowy obiket klasy Array_class, kt�ry b�dzie przechowywya� kopi� wygenerowanej tablicy z elementami typu int
				tab_int_copy=new Array_class<int>(n);
				tab_int_copy->create_array();
				for(int i=0; i<n; i++) {
					tab_int_copy->add_data(tab_int->get_data(i),i);
				}
			}
			else if(tab_float) {	// tworzony jest nowy obiket klasy Array_class, kt�ry b�dzie przechowywya� kopi� wygenerowanej tablicy z elementami typu float
				tab_float_copy=new Array_class<float>(n);
				tab_float_copy->create_array();
				for(int i=0; i<n; i++) {
					tab_float_copy->add_data(tab_float->get_data(i),i);
				}
			}
			
						
			if(tab_int_copy) {
				set_arrays_int(tab_int_copy);		// do pliku menu_sort.cpp przekazywana jest kopia tablicy z liczbami ca�kowitymi
			} else if(tab_float_copy) {
				set_arrays_float(tab_float_copy);	// do pliku menu_sort.cpp przekazywana jest kopia tablicy z liczbami rzeczywistymi
			}
			
			menu_sort();							// wywo�ywane jest menu rodzaj�w sortowa� z pliku menu_sort.cpp
			sort_choice_switch(n);					// u�ytkownik podaje wyb�r algorytmu sortowania (z plisku menu_sort.cpp)
			check_correct(n);						// sprawdzenie poprawno�ci posortowania
			
			menu();
			choice_switch();
			
			break;
		}
		case 5: {		// wy�wietlanie posortowanej tablicy - czyli kopii wygenerowanej tablicy
			if(tab_int_copy) {
				tab_int_copy->show_array();
				cout << endl << endl;
			} else if(tab_float_copy) {
				tab_float_copy->show_array();
				cout << endl << endl;
			}
			
			menu();
			choice_switch();
			
			break;
		}
		case 6: {		// wyj�cie z programu
			exit(0);
			break;
		}
		default:
			cout << "niepoprawny numer polecenia" << endl << endl;
			
			menu();
			choice_switch();
	}
}

void generation_int(int n, char choice) {		// funkcja generuj�ca r�ne rodzaje tablic w zalezno�ci od wyboru u�ytkownika - dla danych typu int
	
	if(choice == 'l') {							// generowanie tablicy losowej
		for(int i=0; i<n; i++) {
			tab_int->add_data(rand()%10001, i);
		}	
	}
	else if(choice == 'r') {					// generowanej tablicy posortowanej rosn�co
		for(int i=0; i<n; i++) {	// generowanie losowej tablicy
			tab_int->add_data(rand()%10001, i);
		}
		int *T = tab_int->get_array();
		
		int distance = n;
	
		for(int w=2; w<=n; w*=2) {	// sortowanie rosn�ce za pomoc� algorytmu Shella
		distance /= 2;
		
    	for(int i=distance; i<n; i++) {
        	int pom = T[i];
            int j;
            for(j=i; j>=distance && T[j-distance]>pom; j-=distance) {
                T[j] = T[j-distance];
            }
            T[j] = pom;
        }
    	}
	}
	else if(choice == 'm') {				// generowanej tablicy posortowanej malej�co
		for(int i=0; i<n; i++) {	// generowanie losowej tablicy
			tab_int->add_data(rand()%10001, i);
		}
		int *T = tab_int->get_array();
		
		int distance = n;
	
		for(int w=2; w<=n; w*=2) {	// sortowanie malej�ce za pomoc� algorytmu Shella
		distance /= 2;
		
    	for(int i=distance; i<n; i++) {
        	int pom = T[i];
            int j;
            for(j=i; j>=distance && T[j-distance]<pom; j-=distance) {
                T[j] = T[j-distance];
            }
            T[j] = pom;
        }
    	}
	}
	else if(choice == '3') {				// generowanej tablicy posortowanej w 33%
		for(int i=0; i<n/3; i++) {		// 33% tablic uzupe�niane jest po kolei od 0 do n/3
			tab_int->add_data(i, i);
		}
		
		for(int i=n/3; i<n; i++) {
			tab_int->add_data(n/3 + rand()%(((n/3)*2) + 1), i);	// p�niej generowane s� losowe elementy, kt�rych warto�� jest wi�ksza od n/3
		}
	}
	else if (choice == '6') {				// generowanej tablicy posortowanej w 66%
		for(int i=0; i<(n/3)*2; i++) {	// 66% tablic uzupe�niane jest po kolei od 0 do (n/3)*2
			tab_int->add_data(i, i);
		}
		
		for(int i=(n/3)*2; i<n; i++) {
			tab_int->add_data((n/3)*2 + rand()%((n/3) + 1), i);	// p�niej generowane s� losowe elementy, kt�rych warto�� jest wi�ksza od (n/3)*2
		}
	}
}

void generation_float(int n, char choice) {			// funkcja generuj�ca r�ne rodzaje tablic w zalezno�ci od wyboru u�ytkownika - dla danych typu float - wszystko dzia�a analogicznie jak dla danych typu int
	
	if(choice == 'l') {
		for(int i=0; i<n; i++) {
			tab_float->add_data(float(rand())/float((RAND_MAX)) *10001, i);
		}	
	}
	else if(choice == 'r') {
		for(int i=0; i<n; i++) {
			tab_float->add_data(float(rand())/float((RAND_MAX)) *10001, i);
		}
		float *T = tab_float->get_array();
		
		int distance = n;
	
		for(int w=2; w<=n; w*=2) {	
		distance /= 2;
		
    	for(int i=distance; i<n; i++) {
        	float pom = T[i];
            int j;
            for(j=i; j>=distance && T[j-distance]>pom; j-=distance) {
                T[j] = T[j-distance];
            }
            T[j] = pom;
        }
    	}
	}
	else if(choice == 'm') {
		for(int i=0; i<n; i++) {
			tab_float->add_data(float(rand())/float((RAND_MAX)) *10001, i);
		}
		float *T = tab_float->get_array();
		
		int distance = n;
	
		for(int w=2; w<=n; w*=2) {	
		distance /= 2;
		
    	for(int i=distance; i<n; i++) {
        	float pom = T[i];
            int j;
            for(j=i; j>=distance && T[j-distance]<pom; j-=distance) {
                T[j] = T[j-distance];
            }
            T[j] = pom;
        }
    	}
	}
	else if(choice == '3') {
		for(int i=0; i<n/3; i++) {
			tab_float->add_data(float(i), i);
		}
		
		for(int i=n/3; i<n; i++) {
			tab_float->add_data(n/3 + float(rand())/float((RAND_MAX)) * ((n/3)*2), i);
		}
	}
	else if (choice == '6') {
		for(int i=0; i<(n/3)*2; i++) {
			tab_float->add_data(float(i), i);
		}
		
		for(int i=(n/3)*2; i<n; i++) {
			tab_float->add_data((n/3)*2 + float(rand())/float((RAND_MAX)) * (n/3), i);
		}
	}
}




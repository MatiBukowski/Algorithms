#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "menu.h"
#include "array_class.h"
#include "menu_sort.h"

using namespace std;

int n;										// deklarowanie zmiennej przechowuj¹cej wielkoœc tablicy 
Array_class<int> *tab_int = NULL;			// deklarowanie wskaŸnika na obiekt klasy Array_class o typie danych int i przypisywanie mu wartoœci NULL - wygenerowana tablica z elemenatmi int
Array_class<float> *tab_float = NULL;		// deklarowanie wskaŸnika na obiekt klasy Array_class o typie danych float i przypisywanie mu wartoœci NULL - wygenerowana tablica z elemenatmi float

Array_class<int> *tab_int_copy = NULL;		// deklarowanie wskaŸnika na obiekt klasy Array_class o typie danych int i przypisywanie mu wartoœci NULL - kopia tablicy z elemenatmi int
Array_class<float> *tab_float_copy = NULL;	// deklarowanie wskaŸnika na obiekt klasy Array_class o typie danych float i przypisywanie mu wartoœci NULL	- kopia tablicy z elemenatmi float

void menu() {				// wyœwietlanie g³ownego menu
	cout << "---------------------------------------MENU---------------------------------------" << endl;
	cout << "1 - wczytanie tablicy z pliku o zadanej nazwie" << endl;
	cout << "2 - wygenerowanie tablicy o zadanym rozmiarze zawieraj¹ce losowe wartoœci" << endl;
	cout << "3 - wyœwietlenie ostatnio utworzonej tablicy na ekranie" << endl;
	cout << "4 - uruchomienie wybranego algorytmu sortowania na ostatnio utworzonej tablicy" << endl;
	cout << "5 - wyœwietlenie posortowanej tablicy na ekranie" << endl;
	cout << "6 - zakoñcz program" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_switch() {		// wybór u¿ytkownika na podstawie menu i dalsze operacje
	int choice;
	
	cout << "Podaj wybór: ";
	cin >> choice;
	system("cls");
	
	switch(choice) {
		case 1: { 	// wczytywanie tablicy z pliku
			tab_int_copy=NULL;
			tab_float_copy=NULL;
			
			char o = 'g';	// zmienna przechowuj¹ca wybór czy ma byæ to tablica intów czy floatów
			ifstream file;	// wczytywany plik
			string name;	// zmienna przechowuj¹ca nazwê wczytywnaego pliku, któr¹ poda³ u¿ytkownik
			int x_i;		//zmienna przechowuj¹ca jeden wiersz z pliku, gdzie wszystkie liczby s¹ intami
			float x_f;		// zmienna przechowuj¹ca jeden wiersz z pliku, gdzie wszystkie liczby s¹ floatami
			
			
			while(o!='i' && o!='f') {
				cout << "Ma to byæ tablica int-ów czy float-ów? (i/f): ";
				cin >> o;
			}
				
			cout << "Podaj nazwê pliku, z którego chcesz wczytaæ tablicê: ";
			cin >> name;
			
			file.open((name + ".txt").c_str());			// otwieranie pliku o podanej nazwie
			
			if(file.good()==false) {					// jeœli plik siê nie otworzy³
				cout << "Plik nie istnieje" << endl;
			} else {									// jeœli plik siê otworzy³
				
				string line;
				int line_number = 1;
				
				while(getline(file, line)){
					if(line_number == 1) {				// pierwszy element - wielkoœæ tablicy
						stringstream ss;				// stringstream to typ danych, który pozwala na ³atwe konwertowanie danych np. z string na int
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
								tab_int = new Array_class<int>(n);		// tworzenie obiektu Arrary_class, który bêdzie przechowywa³ tablicê 
								tab_int->create_array();				// tworzenie tablicy 
								tab_int->add_data(x_i, line_number-2);	// dodawanie elementów do tablicy
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
			menu();				// wyœwietlanie menu
			choice_switch();	// u¿ytkownik musi wybraæ nastêpny krok
			
			break;
		}
		case 2: {	// tworzenie tablicy o wielkoœci podanej przez u¿ytkownika
			srand(time(NULL));
			char o = 'g';		// zmienna przechowuj¹ca wybór czy ma byæ to tablica intów czy floatów
			char c = 'g';		// zmienna przechowuj¹ca wybór jaki rodzaj tablicy ma to byæ
			
			tab_int_copy=NULL;
			tab_float_copy=NULL;
			
			cout << "Podaj wielkoœæ ¿¹danej tablicy: ";
			cin >> n;
			
			while(o!='i' && o!='f') {
				cout << "Ma to byæ tablica int-ów czy float-ów? (i/f): ";
				cin >> o;
			}
				
				if(o=='i') {					// dla wybranych danych typu int wyœwietlanie mo¿liwych opcji i generowanie tablicy
					if(tab_float || tab_int) {
						tab_float=NULL;
						tab_int=NULL;
					}

					tab_int = new Array_class<int>(n);
					tab_int->create_array();
					cout << endl << "Typy generowanych tablic: "<<endl;
					cout << "Tablica losowa - l"<<endl;
					cout << "Tablica posortowana rosn¹co - r"<<endl;
					cout << "Tablica posortowana malej¹co - m"<<endl;
					cout << "Tablica posortowana w 33% - 3"<<endl;
					cout << "Tablica posortowana w 66% - 6"<<endl;
					cout << "Podaj jaki ma byæ typ wygenerowanej tablicy?: ";
					cin >> c;
					cout << endl;
					generation_int(n, c);	// funkcja generuj¹ca wybrany rodzaj tablicy
					
//					for(int i=0; i<n; i++) {
//						tab_int->add_data(rand()%10001, i);
//					}	
				} else if(o=='f') {			// dla wybranych danych typu float wyœwietlanie mo¿liwych opcji i generowanie tablicy
					if(tab_float || tab_int) {
						tab_float=NULL;
						tab_int=NULL;
					}
	
					tab_float = new Array_class<float>(n);
					tab_float->create_array();
					cout << endl << "Typy generowanych tablic: "<<endl;
					cout << "Tablica losowa - l"<<endl;
					cout << "Tablica posortowana rosn¹co - r"<<endl;
					cout << "Tablica posortowana malej¹co - m"<<endl;
					cout << "Tablica posortowana w 33% - 3"<<endl;
					cout << "Tablica posortowana w 66% - 6"<<endl;
					cout << "Podaj jaki ma byæ typ wygenerowanej tablicy?: ";
					cin >> c;
					cout << endl;
					generation_float(n, c);		// funkcja generuj¹ca wybrany rodzaj tablicy
//					for(int i=0; i<n; i++) {
//						tab_float->add_data(float(rand())/float((RAND_MAX)) * 10001, i);
//					}
				} else cout << "B³¹d" << endl;
			
			menu();
			choice_switch();
			break;
		}
		case 3: {		// wyœwietlanie wygenerowanej tablicy
			if(tab_int)
				tab_int->show_array();
			else if(tab_float)
				tab_float->show_array();
			
			cout << endl << endl;
			menu();
			choice_switch();
			break;
		}
		case 4: {		// opcja dla której bêdzie przeprowadzane sortowanie tablicy

			if(tab_int) {			// tworzony jest nowy obiket klasy Array_class, który bêdzie przechowywya³ kopiê wygenerowanej tablicy z elementami typu int
				tab_int_copy=new Array_class<int>(n);
				tab_int_copy->create_array();
				for(int i=0; i<n; i++) {
					tab_int_copy->add_data(tab_int->get_data(i),i);
				}
			}
			else if(tab_float) {	// tworzony jest nowy obiket klasy Array_class, który bêdzie przechowywya³ kopiê wygenerowanej tablicy z elementami typu float
				tab_float_copy=new Array_class<float>(n);
				tab_float_copy->create_array();
				for(int i=0; i<n; i++) {
					tab_float_copy->add_data(tab_float->get_data(i),i);
				}
			}
			
						
			if(tab_int_copy) {
				set_arrays_int(tab_int_copy);		// do pliku menu_sort.cpp przekazywana jest kopia tablicy z liczbami ca³kowitymi
			} else if(tab_float_copy) {
				set_arrays_float(tab_float_copy);	// do pliku menu_sort.cpp przekazywana jest kopia tablicy z liczbami rzeczywistymi
			}
			
			menu_sort();							// wywo³ywane jest menu rodzajów sortowañ z pliku menu_sort.cpp
			sort_choice_switch(n);					// u¿ytkownik podaje wybór algorytmu sortowania (z plisku menu_sort.cpp)
			check_correct(n);						// sprawdzenie poprawnoœci posortowania
			
			menu();
			choice_switch();
			
			break;
		}
		case 5: {		// wyœwietlanie posortowanej tablicy - czyli kopii wygenerowanej tablicy
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
		case 6: {		// wyjœcie z programu
			exit(0);
			break;
		}
		default:
			cout << "niepoprawny numer polecenia" << endl << endl;
			
			menu();
			choice_switch();
	}
}

void generation_int(int n, char choice) {		// funkcja generuj¹ca ró¿ne rodzaje tablic w zaleznoœci od wyboru u¿ytkownika - dla danych typu int
	
	if(choice == 'l') {							// generowanie tablicy losowej
		for(int i=0; i<n; i++) {
			tab_int->add_data(rand()%10001, i);
		}	
	}
	else if(choice == 'r') {					// generowanej tablicy posortowanej rosn¹co
		for(int i=0; i<n; i++) {	// generowanie losowej tablicy
			tab_int->add_data(rand()%10001, i);
		}
		int *T = tab_int->get_array();
		
		int distance = n;
	
		for(int w=2; w<=n; w*=2) {	// sortowanie rosn¹ce za pomoc¹ algorytmu Shella
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
	else if(choice == 'm') {				// generowanej tablicy posortowanej malej¹co
		for(int i=0; i<n; i++) {	// generowanie losowej tablicy
			tab_int->add_data(rand()%10001, i);
		}
		int *T = tab_int->get_array();
		
		int distance = n;
	
		for(int w=2; w<=n; w*=2) {	// sortowanie malej¹ce za pomoc¹ algorytmu Shella
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
		for(int i=0; i<n/3; i++) {		// 33% tablic uzupe³niane jest po kolei od 0 do n/3
			tab_int->add_data(i, i);
		}
		
		for(int i=n/3; i<n; i++) {
			tab_int->add_data(n/3 + rand()%(((n/3)*2) + 1), i);	// pó¿niej generowane s¹ losowe elementy, których wartoœæ jest wiêksza od n/3
		}
	}
	else if (choice == '6') {				// generowanej tablicy posortowanej w 66%
		for(int i=0; i<(n/3)*2; i++) {	// 66% tablic uzupe³niane jest po kolei od 0 do (n/3)*2
			tab_int->add_data(i, i);
		}
		
		for(int i=(n/3)*2; i<n; i++) {
			tab_int->add_data((n/3)*2 + rand()%((n/3) + 1), i);	// pó¿niej generowane s¹ losowe elementy, których wartoœæ jest wiêksza od (n/3)*2
		}
	}
}

void generation_float(int n, char choice) {			// funkcja generuj¹ca ró¿ne rodzaje tablic w zaleznoœci od wyboru u¿ytkownika - dla danych typu float - wszystko dzia³a analogicznie jak dla danych typu int
	
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




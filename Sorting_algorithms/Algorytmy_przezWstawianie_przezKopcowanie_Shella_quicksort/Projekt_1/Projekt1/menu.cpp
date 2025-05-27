#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "menu.h"
#include "sort_wstawianie.h"
#include "algorithms_menu.h"

using namespace std;

int n = 0;
int *T, *T2;

void menu() {
	cout << "---------------------------------------MENU---------------------------------------" << endl;
	cout << "1 - wczytanie tablicy z pliku o zadanej nazwie" << endl;
	cout << "2 - wygenerowanie tablicy o zadanym rozmiarze zawieraj¹ce losowe wartoœci" << endl;
	cout << "3 - wyœwietlenie ostatnio utworzonej tablicy na ekranie" << endl;
	cout << "4 - uruchomienie wybranego algorytmu na ostatnio utworzonej tablicy" << endl;
	cout << "5 - wyœwietlenie posortowanej tablicy na ekranie" << endl;
	cout << "6 - zakoñcz program" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
	
}

void choice_switch() {
	int choice;
	
	cout << "Podaj wybór: ";
	cin >> choice;
//	system("cls");
	
	switch(choice) {
		case 1: {
			ifstream file;
			string name;
			
			cout << "Podaj nazwê pliku, z którego chcesz wczytaæ tablicê: ";
			cin >> name;
			
			file.open((name + ".txt").c_str());
			
			if(file.good()==false) {
				cout << "Plik nie istnieje" << endl;
			} else {
				
				delete [] T;
				delete [] T2;
			
				string line;
				int line_number = 1;
				
				while(getline(file, line)){
					if(line_number == 1) {
						stringstream ss;
						ss << line;
						ss >> n;
						T = new int[n];
					} else {
						stringstream ss;
						ss << line;
						ss >> T[line_number-2];
					}
					line_number ++;
				}
				
				T2 = new int[n];			// tworzona jest nowa tablica dynamiczna, na której bêdzie przeprowadzane sortowanie
			
				for(int i=0; i<n; i++) {
					T2[i] = T[i];
				}
	
				set_x(false);
			}
			
			file.close();
			
			cout << endl;
			menu();
			choice_switch();
			
			break;
		}
		case 2: {
			cout << "Podaj wielkoœæ ¿¹danej tablicy: ";
			cin >> n;
			srand(time(NULL));
			
			delete [] T;
			delete [] T2;
		
			T = new int[n];
			
			for(int i=0; i<n; i++) {
				T[i] = rand()%500;
			}
			
			T2 = new int[n];			// tworzona jest nowa tablica dynamiczna, na której bêdzie przeprowadzane sortowanie
			
			for(int i=0; i<n; i++) {
				T2[i] = T[i];
			}
			
			set_x(false);
			cout << endl;
			menu();
			choice_switch();
	
			break;
		}
		case 3: {
			if(n!=0) {
				for(int i=0; i<n; i++) {
					cout << T[i] << " ";
				}
			} else cout << "Brak tablicy do wyœwietlenia";
			
			cout << endl << endl;
			menu();
			choice_switch();
			
			break;
		}
		case 4: {
			algorithms_menu();
			alg_choice_switch(n, T2);
			
			menu();
			choice_switch();
			
			break;
		}
		case 5: {
			if(is_sorted()) {
				for(int i=0; i<n; i++) {
					cout << T2[i] << " ";
				}
			} else cout << "B³¹d";
			
			cout << endl << endl;
			
			menu();
			choice_switch();
			
			break;
		}
		case 6: {
			delete [] T;
			delete [] T2;
			exit(0);
			break;
		}
		default:
			cout << "niepoprawny numer polecenia" << endl << endl;
			
			menu();
			choice_switch();
	}
	
	delete [] T;
	delete [] T2;
}




#include <iostream>

#include "menu.h"
#include "generate.h"

using namespace std;

void show_menu_MST() {				// wy�wietlanie g�ownego menu
	cout << "---------------------------------------MENU---------------------------------------" << endl;
	cout << "1 - wczytanie grafu z pliku o zadanej nazwie" << endl;
	cout << "2 - wygenerowanie losowego grafu" << endl;
	cout << "3 - wy�wietlenie grafu macierzowo i listowo" << endl;
	cout << "4 - zako�cz program" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_switch_MST() {		// wyb�r u�ytkownika na podstawie menu i dalsze operacje
	int choice;
	
	cout << "Podaj wyb�r: ";
	cin >> choice;
	system("cls");
	
	switch(choice) {
		case 1: {
			
			menu_MST();
			choice_switch_MST();
			break;
		}
		case 2: {
			int n;
			int g;
			
			cout << "Podaj ilo�� wierzcho�k�w grafu: ";
			cin >> n; 
			cout << "Podaj g�sto�� grafu (25, 50, 99 [%]): ";
			cin >> g;
			cout <<endl;
			 
			generate_graph(n, g);
	
			menu();
			choice_switch();
			break;
		}
		case 3: {
			
			menu();
			choice_switch();
			break;
		}
		case 4: {
			exit(0);
			break;
		}
		default:
			cout << "niepoprawny numer polecenia" << endl << endl;
			
			menu();
			choice_switch();		
	}
}

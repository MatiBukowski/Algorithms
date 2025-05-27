#include <iostream>

#include "menu.h"
#include "generate.h"

using namespace std;

void show_menu_MST() {				// wyœwietlanie g³ownego menu
	cout << "---------------------------------------MENU---------------------------------------" << endl;
	cout << "1 - wczytanie grafu z pliku o zadanej nazwie" << endl;
	cout << "2 - wygenerowanie losowego grafu" << endl;
	cout << "3 - wyœwietlenie grafu macierzowo i listowo" << endl;
	cout << "4 - zakoñcz program" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
}

void choice_switch_MST() {		// wybór u¿ytkownika na podstawie menu i dalsze operacje
	int choice;
	
	cout << "Podaj wybór: ";
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
			
			cout << "Podaj iloœæ wierzcho³ków grafu: ";
			cin >> n; 
			cout << "Podaj gêstoœæ grafu (25, 50, 99 [%]): ";
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

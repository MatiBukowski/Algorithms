#include <iostream>

#include "algorithms_menu.h"
#include "sort_wstawianie.h"
#include "menu.h"

using namespace std;
bool x = false;

void algorithms_menu() {
	cout << "----------------------------------ALGORITHMS_MENU----------------------------------" << endl;
	cout << "1 - sortowanie przez wstawianie" << endl;
	cout << "2 - sortowanie przez kopcowanie" << endl;
	cout << "3 - sortowanie Shella" << endl;
	cout << "4 - sortowanie szybkie (quicksort)" << endl;
	cout << "-----------------------------------------------------------------------------------" << endl;
	
}

void alg_choice_switch(int n, int *T) {
	int choice;
	
	cout << "Podaj wybór: ";
	cin >> choice;
//	system("cls");
	
	switch(choice) {
		case 1: {
			Sort_wstawianie algorithm1(n, T);
			algorithm1.sort();
			x = true;
			
//			menu();
//			choice_switch();
			
			break;
		}
		case 2: {
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			break;
		}
		default:
			cout << "niepoprawny numer polecenia";
	}
}

void set_x(bool g) {
	x = g;
}

bool is_sorted() {
	if(x)
		return true;
	else return false;
}

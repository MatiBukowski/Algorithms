#include <iostream>

#include "main_menu.h"
#include "menu_MST.h"
#include "menu_Path.h"

using namespace std;

void main_menu() {			// menu wyboru jaki problem u�ytkownik chce rozwi�za�
	int a = 0;
	
	while(a != 1 && a != 2 && a != 3) {
		cout << "------------------------------------MAIN-MENU-------------------------------------" << endl;
		cout << "1 - Szukanie najkr�tszej drogi w grafie" << endl;
		cout << "2 - Szukanie minimalnego drzewa rozpinaj�cego" << endl;
		cout << "3 - Zako�cz program" << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
		cout<<"Jaki problem chcesz rozwi�za�?: ";
		cin >> a;
		system("cls");
	}
	
	
	if(a == 1) {
		show_menu_Path();
		choice_switch_Path();
	} else if(a == 2) {
		show_menu_MST();
		choice_switch_MST();
	} else if(a == 3) {
		exit(0);
	}
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <locale.h>

#include "array_class.h"
#include "menu.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");
	
	menu();					// wywo�ywanie funkcji menu wy�wietlaj�cej g��wne menu (z pliku menu.cpp)
	choice_switch();		// wywo�ywanie funkcji dla kt�rej u�ywtkownik podaje wyb�r polecenia na podstawie menu (z pliku menu.cpp)
	
	return 0;
}

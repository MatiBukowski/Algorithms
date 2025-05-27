#include <iostream>
#include <ctime>
#include <cstdlib>
#include <locale.h>

#include "array_class.h"
#include "menu.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");
	
	menu();					// wywo³ywanie funkcji menu wyœwietlaj¹cej g³ówne menu (z pliku menu.cpp)
	choice_switch();		// wywo³ywanie funkcji dla której u¿ywtkownik podaje wybór polecenia na podstawie menu (z pliku menu.cpp)
	
	return 0;
}

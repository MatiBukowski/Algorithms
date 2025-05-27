#include <iostream>
#include <locale.h>

#include "sort_wstawianie.h"
#include "menu.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");
	
	menu();
	choice_switch();
	
//	srand(time(NULL));
//	
//	int n = 20;
//	int *T;
//	T = new int[n];
//
//	for(int i=0; i<n; i++) {
//		T[i] = rand()%500;
//	}
//	
//	Sort_wstawianie algorithm1(n, T);
//	algorithm1.show();
//	algorithm1.sort();
//	cout << endl;
//	algorithm1.show();
//	
//	delete [] T;
	
	return 0;
}

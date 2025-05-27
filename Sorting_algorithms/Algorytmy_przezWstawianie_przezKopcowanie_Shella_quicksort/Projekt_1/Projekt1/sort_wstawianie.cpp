#include <iostream>
#include <cstdlib>

#include "sort_wstawianie.h"

using namespace std;

Sort_wstawianie::Sort_wstawianie(int N, int *t) {
	n = N;
	T = t;
}

Sort_wstawianie::~Sort_wstawianie() {
	cout << "Destruktor!!!!!!!!!!!!!!!!!!!!!!!";
	delete [] T;
}

void Sort_wstawianie::show() {
	for(int i=0; i<n; i++) {
		cout << T[i] << " ";
	}
}

void Sort_wstawianie::sort() {
	int pom, j;
     for(int i=1; i<n; i++)
     {
             pom = T[i];
             j = i-1;
             
             while(j>=0 && T[j]>pom) {
                        T[j+1] = T[j]; 
                        j--;
             }
             
             T[j+1] = pom; 
     }     
}









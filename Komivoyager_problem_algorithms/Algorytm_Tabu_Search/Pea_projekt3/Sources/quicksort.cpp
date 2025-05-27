//
// Created by mateu on 13.12.2024.
//

#include "quicksort.h"
#include <iostream>
using namespace std;

int pivotIndex(int** T, int left, int right) {
    int pivIndex = (left+right)/2;
    int pivot = T[pivIndex][2];							// przypisanie wartości pivota
    int j = left;

    swap(T[pivIndex], T[right]);					// pivota ustawiany jest na prawą stronę, aby nie przeszkadzał w porównaniach i zamianie

    for(int i=left; i<right; i++) {					// podział tablicy na wartości mniejsze i większe od pivota
        if(T[i][2] < pivot) {
            swap(T[i], T[j]);
            j++;
        }
    }

    swap(T[j], T[right]);							// zamiana pivota z najbardziej wysuniętą na lewo liczbą od niego większą (bądź równą)
    return j;										// zwracanie indeksu pivota
}

void quicksort(int** T, int left, int right) {

    if(left < right) {
        int pivIndex = pivotIndex(T, left, right);		// indeks pivota
        quicksort(T, left, pivIndex-1);					// wywoływanie funkcji quicksort dla lewej podtablicy
        quicksort(T, pivIndex+1, right);					// wywoływanie funkcji quicksort dla prawej podtablicy
    }

}

void sortowanie_quicksort(int** T, int n) {
    quicksort(T, 0, n-1);									// wywoływanie funkcji quicksort dla całej tablicy
}
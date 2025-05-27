//
// Created by mateu on 29.12.2024.
//

#include "moves.h"
#include <iostream>

using namespace std;

void invert_move(int *permutation, int start, int end) {
    while(start < end) {
        swap(permutation[start], permutation[end]);
        start++;
        end--;
    }
}

void insert_move(int *permutation, int from_index, int to_index) {
    int city = permutation[from_index];

    if(from_index < to_index) {
        for(int i=from_index; i<to_index; i++) {
            permutation[i] = permutation[i+1];
        }
    } else {
        for(int i=from_index; i>to_index; i--) {
            permutation[i] = permutation[i-1];
        }
    }

    permutation[to_index] = city;
}
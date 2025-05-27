#include <iostream>
#include "main_menu.h"

using namespace std;

int main() {                                // główna funckja programu

    int** matrix = nullptr;
    int cities_number = 0;

    while(true) {
        show_main_menu();
        choice_switch(matrix, cities_number);
    }

}

#include <iostream>
#include <conio.h>
#include "main_switch.h"

int main()                      // głowna funkcja programu
{
    int** matrix = nullptr;
    int* sym_array = nullptr;

    load_conf_file(matrix, sym_array);

    getch();
    return 0;
}

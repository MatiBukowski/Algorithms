#include <iostream>
#include <conio.h>
#include "main_switch.h"


int main()                  // głowna funkcja programu
{
    int** matrix = nullptr;

    load_conf_file(matrix);

    getch();
    return 0;
}

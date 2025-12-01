#include <stdlib.h>
#include "utils.h"

/*
    jalankan command clear screen berdasarkan os user
 */
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void gotoxy(x,y) {
    #ifdef _WIN32
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        return;
    #else
        printf("\033[%d;%dH", y, x);
    #endif
}
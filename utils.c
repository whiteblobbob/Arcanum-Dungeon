#include <stdlib.h>
#include "utils.h"
#ifdef _WIN32
#include <windows.h>
#endif


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

//Fixed gotoxy function

void gotoxy(int x, int y) { 
#ifdef _WIN32
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", y, x);
#endif
}
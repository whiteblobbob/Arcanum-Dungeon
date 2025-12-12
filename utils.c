#include <stdlib.h>
#include "utils.h"
#ifdef _WIN32
#include <windows.h>
#endif
//For _getch() function
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include "sound.h"


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

void press_esc_key() {
    while (1) {
        int ch = _getch();
        if (ch == 27) //Ascii value for ESC
          { 
            stop_bgm();
            stop_all_sfx();
            abort();
            break;
        }
    }
} 

void press_enter_key()
{
    while (1) {
        int ch = _getch();
        if (ch == 13) //Ascii value for ENTER
          { 
            break;
        }
    }
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
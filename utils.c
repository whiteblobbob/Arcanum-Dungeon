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
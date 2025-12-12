/* Cross-platform beep implementation */
#include "sound.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#endif

void playsound(void) {
#ifdef _WIN32
    /* Windows beep using Beep API (frequency 1000 Hz, 300 ms) */
    Beep(1000, 300);
#else
    system("paplay src/slash.mp3");
#endif
}

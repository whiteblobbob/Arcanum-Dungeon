/* Cross-platform beep implementation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

void play_sound(const char *filename) {
#ifdef _WIN32

    // WINDOWS → Play WAV file
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);

#else
    system("paplay src/slash.mp3");
#endif
}

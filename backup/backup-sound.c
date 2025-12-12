/* Cross-platform beep implementation */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

void play_bgm(const char *filename) {
#ifdef _WIN32
    // WINDOWS → Play WAV file in loop
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); 
#endif
};

void stop_sound() {
// WINDOWS → Stop any currently playing sound
    PlaySound(NULL, NULL, 0); 
};

void play_sound(const char *filename) {
#ifdef _WIN32
    // WINDOWS → Play WAV file asynchronously
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC); 
#else
    /* Try several methods on Unix-like systems:
     * 1) Write BEL to the controlling TTY (/dev/tty) if available
     * 2) Print BEL to stdout
     * 3) If installed, call the `beep` utility
     * 4) If installed, try `paplay` to play a desktop sound
     */

    /* 1) Try /dev/tty */
    FILE *tty = fopen("/dev/tty", "w");
    if (tty) {
        fputc('\a', tty);
        fflush(tty);
        fclose(tty);
        return;
    }

    /* 2) Fallback to stdout BEL */
    fputc('\a', stdout);
    fflush(stdout);

    /* 3) Try `beep` utility if available */
    if (system("command -v beep >/dev/null 2>&1") == 0) {
        system("beep -f 1000 -l 300 >/dev/null 2>&1 || true");
        return;
    }

    /* 4) Try `paplay` (PulseAudio) to play a standard desktop sound if available */
    if (system("command -v paplay >/dev/null 2>&1") == 0) {
        /* Play a commonly-available sound if present; ignore errors */
        system("paplay /usr/share/sounds/freedesktop/stereo/complete.oga >/dev/null 2>&1 || true");
        return;
    }

    /* If none of the above worked, there's not much we can do portably.
     * Terminal bell may be disabled or the system may not allow console speaker access.
     * Recommend the user enable terminal bell or install `beep`/PulseAudio utilities.
     */
#endif
}

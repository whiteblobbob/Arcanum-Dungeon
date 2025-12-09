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

void beep(void) {
#ifdef _WIN32
    /* Windows beep using Beep API (frequency 1000 Hz, 300 ms) */
    Beep(1000, 300);
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

#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

/* Cross-platform beep function */
void beepy() {
#ifdef _WIN32
    /* Windows beep using Beep API */
    Beep(1000, 500);  /* frequency: 1000 Hz, duration: 500 ms */
#else
    /* Linux/Unix beep using printf bell character */
    printf("\a");
    fflush(stdout);
#endif
}

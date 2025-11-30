#include <stdio.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))   // Windows Sleep
#else
#include <unistd.h>                  // Linux/Mac
#endif
#include "combat.h"
#include "utils.h"
#include "sound.h"



int main() {

    // UI Select Variable
    int menu;


    // Color Variable
    const char *purple = "\033[0;35m";
    const char *white = "\033[0;37m";
    const char *aqua = "\033[0;36m";
    const char *blue = "\033[0;34m";
    const char *green = "\033[0;32m";
    const char *yellow = "\033[0;33m";
    const char *red = "\e[1;31m";
    const char *black = "\033[0;30m";

    // Reset to default color
    const char *reset = "\033[0m";
    
    // Code For Menu UI
    printf("%s====================================================================%s\n", purple, reset);
    printf("%s|                                                                  |%s\n", purple, reset);
    printf("%s|%s                        %sArcanum Dungeon!%s                          |%s\n",purple, reset, aqua, purple, reset);
    printf("%s|                                                                  |%s\n", purple, reset);
    printf("%s====================================================================%s\n", purple, reset);
    printf("%s|%s", purple, reset);
    printf("                          1. %sNew Game                             %s|%s\n", green, purple, reset);
    printf("%s====================================================================%s\n", purple, reset);
    printf("%s|%s", purple, reset);
    printf("                          2. %sLoad FIle                            %s|%s\n", yellow, purple, reset);
    printf("%s====================================================================%s\n", purple, reset);
    printf("%s|%s", purple, reset);
    printf("                          3. %sExit                                 %s|%s\n", red, purple, reset);
    printf("%s====================================================================%s\n", purple, reset);

    do
    {
    printf("Menu Selection : ");
    scanf("%d", &menu);

    
  if (menu == 1)
    {   
        printf("%sWelcome to the World My Hero! %s\n", aqua, reset);
        sleep(2);
        
    }else if (menu == 2)
    {
        printf("%sWelcome Back Hero! %s\n", blue, reset);
        sleep(2);
        printf("%sChecking Your Journey, A Moment!%s\n", yellow, reset);
        sleep(2);

    }else if (menu == 3)
    {   
        printf("%sWe'll Wait For Your Comeback, Hero!%s\n", yellow, reset);
        abort();
    }
    else{
        printf("%sHero, Your Choice Isn't Valid..%s\n", red, reset);
    };
    } while (menu < 1 || menu > 3);
    // menu UI sampai disini
    
    // Story mulai dari sini
    printf("%sHero, Watch Out!, You Encountered an Enemy%s\n",red, reset);
    sleep(2);
    /* nyoba suara */
    beep();
    start_combat();
    // End Of Battle UI Code

    // Checkpoint UI


    printf("This is checkpoint UI\n");

    return 0;
}
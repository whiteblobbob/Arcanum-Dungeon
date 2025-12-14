#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "combat.h"
#include "utils.h"
#include "storage.h"
#include "dungeon.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include "sound.h"

int main() {
    // rng seeding
    srand(time(NULL));
    // Initialize Sound and Music System
    init_audio();

    // UI Select Variable
    char menu = '0';

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

    play_bgm("sound/bgm/Fontainebleau - Just You.wav");
    set_bgm_volume(0.4f);

    while (menu == '0') {
        clear_screen();

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
        printf("%s====================================================================%s\n\n", purple, reset);

        printf("Menu: ");
        scanf(" %c", &menu);
        clear_input_buffer();

        if (menu == '1') {
            char name[17];
            struct player save;

            printf("%sWelcome to the world of Arcanum, Hero!%s\n", aqua, reset);

            sleep(2);

            printf("%sWould you please tell us your name?%s\n", aqua, reset);
            printf("Name (Max 16 letters): ");

            // scanf("%16s", name);
            fgets(name, sizeof(name), stdin);
            clear_input_buffer();

            create_data(&save, name);
            save_data(&save);

            printf("%s%s... A fitting name for the hero who will save the world..%s\n", aqua, save.name, reset);

            sleep(3);

            printf("%sWell then, let's begin!%s\n",aqua, reset);

            play_sfx("sound/sfx/new-game.wav");
            set_sfx_volume(0.4f);

            sleep(2);

            enter_dungeon(&save);
        } else if (menu == '2') {
            struct player save;
            int save_exists = load_data(&save);

            if (!save_exists) {
                printf("%sYou don't have a save file yet!%s\n", red, reset);
                menu = '0';
                continue;
            }

            printf("%sWelcome back, %s!%s\n", blue, save.name, reset);

            sleep(2);

            printf("%sChecking your adventure log, wait for a moment!%s\n", yellow, reset);

            sleep(2);

            printf("%sDone!%s\n", green, reset);

            play_sfx("sound/sfx/load.wav");
            set_sfx_volume(0.4f);

            sleep(2);

            enter_dungeon(&save);
        } else if (menu == '3') {   
            play_sfx("sound/sfx/exit.wav");

            printf("%sWe will be waiting for your return, Hero!%s\n", yellow, reset);

            sleep(4);
            // exit with error code 0
            return 0;
        } else {
            printf("%sHero, your choice isn't valid...%s\n", red, reset);
            sleep(2);
            menu = '0';
        }
    }

    // Checkpoint UI
    // printf("This is checkpoint UI");

    return 0;
}
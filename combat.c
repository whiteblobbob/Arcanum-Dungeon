#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"
#include "utils.h"


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

// CONSTANTS
int CRIT_CHANCE = 7;

int player_stats[] = {
    10, // max hp
    4, // atk
    2, // def
    10 // mana
};

int enemy_stats[] = {
    10, // max hp
    4, // atk
    2, // def
    10 // mana
};

char combat_log[2][100] = {"", ""};

int damage(int atk, int def, int attacker) {
    // crit chance
    int crit = (rand() % 100 + 1 <= CRIT_CHANCE);

    // damage calculation
    int dmg = (atk * 5) / (def + 5);

    // crit & guaranteed hit (bypass defense)
    dmg += (crit * dmg / 2) + (dmg <= 0);

    if (attacker == 0) {
        sprintf(combat_log[attacker], "You dealt %d damage!%s\n", dmg, (crit == 1 ? " (CRIT)" : ""));
    } else {
        sprintf(combat_log[attacker], "The enemy dealt %d damage!%s\n", dmg, (crit == 1 ? " (CRIT)" : ""));
    }

    return dmg;
}

int start_combat() {
    // rng seeding
    srand(time(NULL));

    // reset the combat log
    combat_log[0][0] = '\0';
    combat_log[1][0] = '\0';

    // temp stats
    int player_hp = player_stats[0];
    int player_mana = player_stats[3];

    int enemy_hp = enemy_stats[0];
    int enemy_mana = enemy_stats[3];

    while (player_hp > 0 && enemy_hp > 0) {

        //disabled due UI needs
        
        // clear_screen();

    int action;
    do{
    printf("%s====================================================================%s\n", purple, reset);
    printf("%s|                                                                  |%s\n", purple, reset);
    printf("%s|%s                               %sAction%s                             |%s\n",purple, reset, aqua, purple, reset);
    printf("%s|                                                                  |%s\n", purple, reset);
    printf("%s====================================================================%s\n", purple, reset);
    printf("%s|%s", purple, reset);
    printf("                 1. %sAttack                %s2. %sDefend%s               |%s\n", red, reset, yellow, purple, reset);
    printf("%s====================================================================%s\n", purple, reset);
    printf("%s|%s", purple, reset);
    printf("                 3. %sSkill                 %s4. %sOther%s                |%s\n", blue, reset, green, purple, reset);
    printf("%s====================================================================%s\n", purple, reset);


        printf("%s%s", combat_log[0], combat_log[1]);
        
        printf("Hero  %d HP    %d ATK    %d MANA    %d DEF\n", player_hp, player_stats[1], player_mana, player_stats[2]);
        printf("Enemy   %d HP    %d ATK    %d MANA    %d DEF\n\n", enemy_hp, enemy_stats[1], enemy_mana, enemy_stats[2]);

        printf("I Will : ");
        scanf("%d", &action);

        if (action == 1)
        {   
            printf("%sYou Attacked an enemy, you deal amount of damage %s\n", red, reset);

                int dmg = damage(player_stats[1], enemy_stats[2], 0);
                enemy_hp -= dmg;
                sleep(2);
            
        }else if (action == 2)
        {
            printf("%sYou are guarding their attack, defense up! %s\n", yellow, reset);
            player_stats[2] += 2;
            sleep(2);

        }else if (action == 3)
        {   
            printf("%sWhich Skill would you like to deploy?%s\n", blue, reset);

            printf("1. %sRegen %s(Cost 3 mana) %s- %sHeals 2 HP%s\n", green, aqua, reset, green, reset);
            
            int skill;
            do{
            printf("I Will use : ");
            scanf("%d", &skill);

            if (skill == 1)
            {
                if (player_mana < 3)
                {
                    printf("%sYou tried to cast the healing but, you do not have enough Mana!%s\n", red, reset);
                    sleep(2);
                    continue;
                }

                //healing function
                player_hp += 2;
                player_mana -= 3;

                // check overheal and heal log
            if (player_hp == player_stats[0] + 1) {
                printf("%sYou regain 1 hp%s\n", green, reset);
                sleep(2);
            }
            else if (player_hp > player_stats[0]) {
                player_hp = player_stats[0];
                printf("%sYour HP is already full!%s\n", yellow, reset);
                sleep(2);
            }
            else {
                printf("%sYour Regain 2 HP%s\n", green, reset);
                sleep(2);
            }

        }else{
                printf("%sHero, Your Choice Isn't Valid..%s\n", red, reset);
        }

            }while (skill < 1 || skill > 1);
            
        }else if (action == 4){
            printf("%sIs there any strategy would you like?\n%s", yellow, reset);
            printf("1. %sFocus %s - %s Restore 2 Mana%s\n",aqua, reset, aqua, reset);

            int other;
            do{
            printf("Let's : ");
            scanf("%d", &other);

            if (other == 1)
            {
                player_mana += 3;
             if (player_mana == player_stats[0] + 1) {
                printf("%sYou regain 1 mana%s\n", aqua, reset);
                sleep(2);
            }
            else if (player_mana > player_stats[0]) {
                player_mana = player_stats[0];
                printf("%sYour Mana is already full!%s\n", yellow, reset);
                sleep(2);
            }
            else {
                printf("%sYour Regain 2 Mana%s\n", aqua, reset);
                sleep(2);
            }
        }else{
                printf("%sHero, Your Choice Isn't Valid..%s\n", red, reset);
        }

            }while (other < 1 || other > 1);

        }
        else{
            printf("%sHero, Your Choice Isn't Valid..%s\n", red, reset);
        };

        } while (action < 1 || action > 4);

        // apakah musuh masih hidup
        if (enemy_hp <= 0) {
            printf("%sThe enemy has been defeated!%s\n", yellow, reset);
            sleep(1);
            break;
        }

        // enemy action
        int dmg = damage(enemy_stats[1], player_stats[2], 1);
        player_hp -= dmg;
    }

    clear_screen();

    if (player_hp <= 0) {
        printf("%sYou have fallen...%s\n", red, reset);
        sleep(2);
    } else if (enemy_hp <= 0) {
        printf("%sHero!, Great work! (Exp +2)%s\n", green, reset);    
        sleep(2);
    }
}
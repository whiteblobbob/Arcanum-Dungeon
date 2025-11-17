#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"
#include "utils.h"

// CONSTANTS
int CRIT_CHANCE = 7;

int player_stats[] = {
    10, // max hp
    3, // atk
    2, // def
    10 // mana
};

int enemy_stats[] = {
    10, // max hp
    2, // atk
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
        clear_screen();

        // player action
        int action;

        printf("%s%s", combat_log[0], combat_log[1]);
        printf("PLAYER  %d HP    %d ATK    %d MANA    %d DEF\n", player_hp, player_stats[1], player_mana, player_stats[2]);
        printf("ENEMY   %d HP    %d ATK    %d MANA    %d DEF\n\n", enemy_hp, enemy_stats[1], enemy_mana, enemy_stats[2]);
        printf("1. Attack\n");
        printf("What would you like to do?\nAction: ");

        scanf("%d", &action);

        if (action == 1) {
            int dmg = damage(player_stats[1], enemy_stats[2], 0);
            enemy_hp -= dmg;
        } else {
            printf("Invalid action!\n\n");
            continue;
        }

        // apakah musuh masih hidup
        if (enemy_hp <= 0) {
            break;
        }

        // enemy action
        int dmg = damage(enemy_stats[1], player_stats[2], 1);
        player_hp -= dmg;
    }

    clear_screen();

    if (player_hp <= 0) {
        printf("YOU LOST!");
    } else if (enemy_hp <= 0) {
        printf("YOU WON! (+2 EXP)");    
    }
}
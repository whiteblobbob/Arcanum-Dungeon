#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "combat.h"
#include "utils.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include "sound.h"

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
int CRIT_CHANCE = 50;

// stats player dan enemy (sementara)
struct entity {
    int hp;
    int atk;
    int def;
    int mana;
};

char combat_log[2][100] = {"", ""};

int damage(int atk, int def, int attacker) {
    // crit chance (boolean)
    int crit = (rand() % 100 + 1 <= CRIT_CHANCE);

    // damage calculation, guarantees minimum divisor is 1
    int dmg = atk / ((def + 5) / 5);

    if (dmg <= 0) {
        dmg++;
    }

    // crit (bypass defense)
    if (crit) {
        dmg += dmg / 2;
    }

    if (attacker == 0) {
        sprintf(combat_log[attacker], "%sYou dealt %d damage!%s", aqua, dmg, reset, (crit == 1 ? " (CRIT)" : ""));
    } else {
        sprintf(combat_log[attacker], "%sThe enemy dealt %d damage!%s",red, dmg, reset, (crit == 1 ? " (CRIT)" : ""));
    }

    return dmg;
}

int start_combat(int level) {
    struct entity player;
    struct entity enemy;

    // sementara hardcoded
    player.hp = 10;
    player.atk = 2;
    player.def = 2;
    player.mana = 10;

    enemy.hp = 2;
    enemy.atk = 1;
    enemy.def = 2;
    enemy.mana = 2;

    // level scaling
    enemy.hp += (level * enemy.hp / 2) + (rand() % 2);
    enemy.atk += (level * enemy.atk / 2) + (rand() % 3);
    enemy.def += (level * enemy.def / 3) + (rand() % 3);
    enemy.mana += (level * enemy.mana / 5) + (rand() % 5);

    // reset the combat log
    combat_log[0][0] = '\0';
    combat_log[1][0] = '\0';

    // temp stats
    int player_hp = player.hp;
    int player_def = player.def;
    int player_mana = player.mana;

    int enemy_hp = enemy.hp;
    int enemy_def = enemy.def;
    int enemy_mana = enemy.mana;

    // Background Music with random selection
    const char* bgm_list[] = {
        "sound/bgm/Death By Glamour (UNDERTALE).wav",
        "sound/bgm/ASGORE (UNDERTALE).wav",
        "sound/bgm/Power Of NEO.wav"
    };

    int bgm_count = 3;

    // Pilih satu lagu secara acak
    int r = rand() % bgm_count;

    // Mulai BGM
    play_bgm(bgm_list[r]);

    // Atur volume
    set_bgm_volume(0.2f);


    while (player_hp > 0 && enemy_hp > 0) {
        // reset def
        player_def = player.def;
        enemy_def = enemy.def;

        //Display Combat Menu
        int action;

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
        printf("%s====================================================================%s\n\n", purple, reset);


        printf("%s\n%s\n\n", combat_log[0], combat_log[1]);
        
        printf("Hero   %d HP    %d ATK    %d MANA    %d DEF\n", player_hp, player.atk, player_mana, player.def);
        printf("Enemy  %d HP    %d ATK    %d MANA    %d DEF\n\n", enemy_hp, enemy.atk, enemy_mana, enemy.def);

        printf("I Will : ");
        scanf("%d", &action);

        if (action == 1) {
            play_sfx("sound/sfx/slash.wav");
            sleep(1);
            int crit = (rand() % 100 + 1 <= CRIT_CHANCE);
            int dmg = damage(player.atk, enemy_def, 0);
            enemy_hp -= dmg;
            if (crit == 1)
            {
            play_sfx("sound/sfx/crit.wav");
            printf("%sYou Attacked an enemy, you deal %d damage (CRITICAL HIT)%s\n", red, dmg, reset);
            sleep(2);
            }else{
            play_sfx("sound/sfx/hit.wav");
            printf("%sYou Attacked an enemy, you deal %d damage %s\n", red, dmg, reset);
            sleep(2);
            }
        
        } else if (action == 2) {
            printf("%sYou are guarding their attack, your defense temporarily increased by 2! %s\n", yellow, reset);
            player_def += 2;
            play_sfx("sound/sfx/defend.wav");
            sleep(2);

        } else if (action == 3) {   
            printf("%sWhich Skill would you like to deploy?%s\n", blue, reset);
            printf("1. %sRegen %s(Cost 3 mana) %s- %sHeals 2 HP%s\n", green, aqua, reset, green, reset);
            
            int skill;

            printf("I Will use : ");
            scanf("%d", &skill);

            if (skill == 1) {
                play_sfx("sound/sfx/regen.wav");
                if (player_mana < 3) {
                    printf("%sYou tried to cast the healing but, you do not have enough Mana!%s\n", red, reset);
                    sleep(2);
                    continue;
                }

                // check overheal and heal log
                if (player_hp >= player.hp) {
                    printf("%sYour HP is already full!%s\n", green, reset);
                    sleep(2);
                    continue;
                }

                int heal_amount = 2;

                player_mana -= 3;
                
                if (player_hp + heal_amount > player.hp) {
                    heal_amount = player.hp - player_hp;
                }
                player_hp += heal_amount;

                printf("%sYou regained %d HP%s\n", green, heal_amount, reset);
                sleep(2);
            } else {
                printf("%sHero, Your Choice Isn't Valid..%s\n", red, reset);
                sleep(2);
                clear_screen(); 
                continue;
            }
        } else if (action == 4) {
            printf("%sIs there any strategy would you like?\n%s", yellow, reset);
            printf("1. %sFocus %s - %s Restore 2 Mana%s\n",aqua, reset, aqua, reset);

            int other;

            printf("Let's : ");
            scanf("%d", &other);

            if (other == 1) {
                play_sfx("sound/sfx/focus.wav");

                int mana_amount = 3;

                if (player_mana + mana_amount > player.mana) {
                    mana_amount = player.mana - player_mana;
                }

                player_mana += mana_amount;

                printf("%sYou regained %d mana%s\n", aqua, mana_amount, reset);
                sleep(2);
            } else {
                printf("%sHero, Your Choice Isn't Valid..%s\n", red, reset);
                sleep(2);
                continue; 
            }
        } else {
            printf("%sHero, Your Choice Isn't Valid..%s\n", red, reset);
            sleep(2);
            continue;
        }

        // apakah musuh masih hidup
        if (enemy_hp <= 0) {
            printf("%sThe enemy has been defeated!%s\n", yellow, reset);
            play_sfx("sound/sfx/enemy-defeated.wav");    
            sleep(2);
            break;
        }

        // enemy action
        int dmg = damage(enemy.atk, player_def, 1);
        player_hp -= dmg;
        int crit = (rand() % 100 + 1 <= CRIT_CHANCE);
        if(crit == 1){
        printf("%sThe enemy Attacked you, it deals %d damage (CRITICAL HIT) %s\n", red, dmg, reset);
        play_sfx("sound/sfx/enemy-crit.wav");
        }else{
        printf("%sThe enemy Attacked you, it deals %d damage %s\n", red, dmg, reset);
        play_sfx("sound/sfx/jokowi-kaget.wav");
        }

        sleep(1);
        clear_screen();
    }
    

    clear_screen();

    if (player_hp <= 0) {
        play_bgm("sound/bgm/Fontainebleau - Doubt.wav");
        printf("%sYou have fallen...%s\n", red, reset);
        printf("%sPress ESC to exit.%s\n", red, reset);
        press_esc_key();
        stop_bgm();

        return 0;
    } else if (enemy_hp <= 0) {
        play_bgm("sound/bgm/Fontainebleau - A Joyful Moment.wav");
        printf("%sHero!, Great work! (Exp +2)%s\n", green, reset);   
        sleep(2);
        printf("%sPress ENTER to continue your adventure.%s\n", green, reset); 
        press_enter_key();
        printf("%sContinuing your adventure...%s\n", aqua, reset);
        sleep(2);

        return 1;
    }

    // safety
    return 0;
}
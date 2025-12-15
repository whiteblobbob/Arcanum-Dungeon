#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "combat.h"
#include "utils.h"
#include "shared.h"
#include "storage.h"
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

int damage(int atk, int def, int attacker) {
    // crit or not
    int crit = (rand() % 100 + 1 <= CRIT_CHANCE);

    int dmg = (atk * 5) / (def + 5);

    // guarantees minimum damage = 1
    if (dmg <= 0) {
        dmg++;
    }

    // crit (bypasses defense defense)
    if (crit) {
        dmg += dmg / 2;
    }

    return dmg;
}

int start_combat(struct player *save, int floor, int boss) {
    // hitung level musuh
    int level = floor * 3 / 2;

    // boss = level * 2
    if (boss) {
        level *= 2;
    }

    struct entity player;
    struct entity enemy;

    // sementara hardcoded
    player.hp = (*save).level * 2 + 10;
    player.atk = (*save).level + 5;
    player.def = (*save).level + 5;
    player.mana = (*save).level * 2 + 10;

    // level scaling
    enemy.hp = (level * 1.5) + (rand() % 8);
    enemy.atk = level + (rand() % 6);
    enemy.def = level + (rand() % 6);
    enemy.mana = (level * 2) + (rand() % 8);

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
        clear_screen();

        // reset def
        player_def = player.def;
        enemy_def = enemy.def;

        char action = '0';

        printf("FLOOR %d\n\n", floor);
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
        
        printf("%s | Lv. %d | %d HP  |  %d ATK  |  %d MANA  |  %d DEF\n",save->name, save->level, player_hp, player.atk, player_mana, player.def);
        printf("%s | Lv. %d | %d HP  |  %d ATK  |  %d MANA  |  %d DEF\n\n", (boss ? "BOSS" : "Enemy"), level, enemy_hp,  enemy.atk, enemy_mana, enemy.def);

        printf("Action: ");
        scanf(" %c", &action);
        clear_input_buffer();

        if (action == '1') {
            play_sfx("sound/sfx/slash.wav");

            sleep(1);

            int crit = (rand() % 100 + 1 <= CRIT_CHANCE);
            int dmg = damage(player.atk, enemy_def, 0);

            enemy_hp -= dmg;

            if (crit == 1) {
                play_sfx("sound/sfx/crit.wav");
                printf("%s%s attacked the enemy! Dealt %d damage! (CRITICAL HIT!)%s\n", red, save->name, dmg, reset);

                sleep(2);
            } else {
                play_sfx("sound/sfx/hit.wav");
                printf("%s%s attacked the enemy! Dealt %d damage!%s\n", red, save->name, dmg, reset);

                sleep(2);
            }
        
        } else if (action == '2') {
            int def_addition = 2 * save->level;
            player_def += def_addition;

            printf("%s%s guarded themselves! DEF temporarily increased by %d! %s\n", yellow, save->name, def_addition, reset);
            play_sfx("sound/sfx/defend.wav");

            sleep(2);

        } else if (action == '3') {   
            printf("%sWhich skill would you like to use?%s\n", blue, reset);
            printf("1. %sRegen %s(Cost %d) %s- %sRegenerates %d HP%s\n", green, aqua, save->level * 3, reset, green, 2 * save->level, reset);
        
            char skill;

            printf("Skill: ");
            scanf(" %c", &skill);
            clear_input_buffer();

            if (skill == '1') {
                play_sfx("sound/sfx/regen.wav");
              
                if (player_mana < 2 * save->level) {
                    printf("%sYou tried to cast Regen, but you do not have enough MANA!%s\n", red, reset);
                    sleep(2);
                    continue;
                }

                // check overheal and heal log
                if (player_hp >= player.hp) {
                    printf("%sYour HP is already full!%s\n", green, reset);
                    sleep(2);
                    continue;
                }

                int heal_amount = 3 * save->level;

                player_mana -= 2 * save->level;
                
                if (player_hp + heal_amount > player.hp) {
                    heal_amount = player.hp - player_hp;
                }
                player_hp += heal_amount;

                printf("%s%s cast Regen! Regained %d HP!%s\n", green, save->name, heal_amount, reset);
                sleep(2);
                // continue; (Pakai fitur ini kalau misalkan mau ngeheal, cuma gak ngurangin turn)
            } else {
                printf("%sHero, your choice isn't valid...%s\n", red, reset);
                sleep(2);

                continue;
            }
        } else if (action == '4') {
            printf("%sIs there any strategy that you would like to use?\n%s", yellow, reset);
            printf("1. %sFocus %s - %s Restores %d MANA%s\n",aqua, reset, aqua, 2 * save->level, reset);

            char other;

            printf("Other: ");
            scanf(" %c", &other);
            clear_input_buffer();

            if (other == '1') {
                play_sfx("sound/sfx/focus.wav");
              
                int mana_amount = 2 * save->level;

                if (player_mana + mana_amount > player.mana) {
                    mana_amount = player.mana - player_mana;
                }

                player_mana += mana_amount;

                printf("%s%s focused! Regained %d MANA%s\n", aqua, save->name, mana_amount, reset);
                sleep(2);
            } else {
                printf("%sHero, your choice isn't valid...%s\n", red, reset);
                sleep(2);
                continue; 
            }
        } else {
            printf("%sHero, your choice isn't valid...%s\n", red, reset);
            sleep(2);
            continue;
        }

        // apakah musuh masih hidup
        if (enemy_hp <= 0) {
            printf("%sYou defeated the enemy!%s\n", yellow, reset);
            play_sfx("sound/sfx/enemy-defeated.wav");    
            sleep(2);
            break;
        }

        // enemy action
        int dmg = damage(enemy.atk, player_def, 1);
        player_hp -= dmg;
        int crit = (rand() % 100 + 1 <= CRIT_CHANCE);

        if (crit == 1) {
            printf("%sThe enemy attacked %s! Dealt %d damage! (CRITICAL HIT!)%s\n", red, save->name, dmg, reset);
            play_sfx("sound/sfx/enemy-crit.wav");
        } else {
            printf("%sThe enemy attacked %s! Dealt %d damage!%s\n", red, save->name, dmg, reset);
            play_sfx("sound/sfx/jokowi-kaget.wav");
        }

        sleep(1);
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
      
        // exp reward
        int exp_reward = level * 3;
        (*save).exp += exp_reward;

        printf("%sGreat work, Hero! (+%d EXP)%s\n", green, exp_reward, reset);

        // save->exp == (*save).exp
        if (save->exp >= save->max_exp) {
            save->level++;
            save->exp -= save->max_exp;
            save->max_exp += save->max_exp / 2;

            printf("%sYou leveled up! (Lv. %d -> Lv. %d)%s\n", green, save->level - 1, save->level, reset);
        }

        printf("%s%d/%d EXP%s\n", green, save->exp, save->max_exp, reset);

        // save data
        save_data(save);

        sleep(2);
      
        printf("%sPress ENTER to continue your adventure%s\n", green, reset); 
        press_enter_key();
        printf("%sContinuing your adventure...%s\n", aqua, reset);
        sleep(2);

        return 1;
    }

    // safety
    return 0;
}

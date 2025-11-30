#include <stdio.h>
#include "combat.h"
#include "shared.h"

void enter_dungeon(struct player *save) {
    int victory = 1, floor = 1;

    while (victory) {
        int level = floor * 3 / 2;

        printf("Floor %d\n", floor);
        victory = start_combat(save, level);

        if (victory) {
            floor++;
        }
    }
}
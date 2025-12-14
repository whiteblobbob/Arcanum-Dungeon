#include <stdio.h>
#include "combat.h"
#include "shared.h"

void enter_dungeon(struct player *save) {
    int victory = 1, floor = 1;

    while (victory) {
        printf("FLOOR %d\n\n", floor);
        victory = start_combat(save, floor, (floor % 5 == 0));

        if (victory) {
            floor++;
        }
    }
}
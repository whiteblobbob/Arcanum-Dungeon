#include <stdio.h>
#include "shared.h"

void create_data(struct player *save, char name[17]) {
    (*save).exp = 0;
    (*save).level = 1;
    (*save).max_exp = 20;
    snprintf((*save).name, 17, "%s", name);
}

int load_data(struct player *save) {
    FILE *file = fopen("save.dat", "rb");

    if (!file) {
        return 0;
    }

    fread(save, sizeof(*save), 1, file);
    fclose(file);

    return 1;
}

void save_data(struct player *save) {
    FILE *file = fopen("save.dat", "wb");
    
    if (!file) {
        return;
    }

    fwrite(save, sizeof(*save), 1, file);
    fclose(file);
}
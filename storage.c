#include <stdio.h>
#include "shared.h"

struct player load_data() {
    FILE *file = fopen("save.dat", "rb");
    struct player save;

    if (!file) {
        save.level = 1;

        return save;
    }

    fread(&save, sizeof(save), 1, file);
    fclose(file);

    return save;
}

void save_data(struct player save) {
    FILE *file = fopen("save.dat", "wb");
    
    if (!file) {
        return;
    }

    fwrite(&save, sizeof(save), 1, file);
    fclose(file);
}
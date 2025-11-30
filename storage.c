#include <stdio.h>
#include "shared.h"

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
#ifndef STORAGE_H
#define STORAGE_H

#include "shared.h"

void create_data(struct player *save, char name[17]);
int load_data(struct player *save);
void save_data(struct player *save);

#endif
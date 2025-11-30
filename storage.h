#ifndef STORAGE_H
#define STORAGE_H

#include "shared.h"

int load_data(struct player *save);
void save_data(struct player *save);

#endif
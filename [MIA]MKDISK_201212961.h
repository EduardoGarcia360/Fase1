#ifndef MIAMKDISK_201212961_H
#define MIAMKDISK_201212961_H
#include "[MIA]ListaSE_201212961.h"

typedef struct s_disco s_disco;

struct s_disco{
    char nombre[50];
    char tamano[5];
    char puntero[9];
};


void proceso_mkdisk(Lista* lalista);

#endif // [MIA]MKDISK_201212961_H

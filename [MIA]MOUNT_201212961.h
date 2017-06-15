#ifndef MIAMOUNT_201212961_H_INCLUDED
#define MIAMOUNT_201212961_H_INCLUDED
#include "[MIA]ListaSE_201212961.h"

typedef struct NodoM NodoM;
typedef struct ListaM ListaM;

struct NodoM{
    char PATH[100];
    char NAME[30];
    char DISK[10];
    char LETRA;
    int numero;
    char ID;
    NodoM* siguiente;
};

struct ListaM{
    NodoM* inicio;
};

void proceso_mount(Lista* lalista);
//void montar(ListaM* lista, char ID, char PATH[100], char NAME[30]);

#endif // [MIA]MOUNT_201212961_H_INCLUDED

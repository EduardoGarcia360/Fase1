#ifndef MIALISTASE_201212961_H
#define MIALISTASE_201212961_H

typedef struct NodoL NodoL;
typedef struct Lista Lista;

struct NodoL{
    int categoria; //1: obligatorio 2: opcional
    char* comando; //size, path, etc.
    char* sentencia;
    NodoL* siguiente;
};

struct Lista{
    NodoL* inicio;
};

void addFinal(Lista* lista, int categoria, char* comando, char* sentencia);
void showLista(Lista* lista);

#endif // [MIA]LISTASE_201212961_H

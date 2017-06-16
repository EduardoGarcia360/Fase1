#ifndef MIALISTASE_201212961_H
#define MIALISTASE_201212961_H

/*para guardar los datos en la linea de entrada en Analizador*/
typedef struct NodoL NodoL;
typedef struct Lista Lista;
/*para guardar los datos de la particion en MOUNT*/
typedef struct NodoM NodoM;
typedef struct ListaM ListaM;
typedef struct TMP TMP;

/*usado en Analizador*/
struct NodoL{
    int categoria; //1: obligatorio 2: opcional
    char* comando; //size, path, etc.
    char* sentencia;
    NodoL* siguiente;
};

struct Lista{
    NodoL* inicio;
};

/*usado en MOUNT*/
struct NodoM{
    char* PATH;
    char* NAME_PART;
    char* DISK;
    char LETRA;
    int numero;
    char ID[5];
    NodoM* siguiente;
};

struct TMP{
    char LETRA;
    int NUMERO;
};

struct ListaM{
    NodoM* inicio;
    char letra_actual;
};

/*Analizador*/
void inicializar(Lista* lista);
void addFinal(Lista* lista, int categoria, char* comando, char* sentencia);
void limpiar_lista(Lista* lista);
void showLista(Lista* lista);
void inicializar(Lista* lista);

/*MOUNT*/
void inicializarM(ListaM* lista);
void addDisco(ListaM* lista, char* ruta, char* nombrepart, char* disco, char letra, int numero, char* id);
void showParticionesMontadas(ListaM* lalista);
void limpiar_lista_mount(ListaM* lalista);
TMP* ultima_letra(ListaM* lalista, char* nombredisco, char letra);

#endif // [MIA]LISTASE_201212961_H

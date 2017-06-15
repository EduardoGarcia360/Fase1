#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>

int cima=0;

EBR* crearParticion(char status, char fit, int start, int size, int next, char name[16]){
    EBR* par_ext = (EBR*)malloc(sizeof(EBR));
    par_ext->part_status=status;
    strcpy(par_ext->part_fit, fit);
    par_ext->part_start=start;
    par_ext->part_size=size;
    par_ext->part_next=next;
    strcpy(par_ext->part_name, name);
    par_ext->siguiente=NULL;
    return par_ext;
}

void agregarParticionEX(Lista_EBR* lista, char status, char fit, int start, int size, int next, char name[16]){
    EBR* nuevo = crearParticion(status, fit, start, size, next, name);
    if(cima==1){
        EBR* aux = lista->inicio;
        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }else{
        lista->inicio = nuevo;
        cima=1;
    }
}


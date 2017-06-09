#include "[MIA]FDISK_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
-el minimo de comandos para fdisk es de 3 ya que hay 6 que son opcionales
-debe haber almenos 3 procesos.
- 1 para obligatorios y 2 para opcionales.
*/


void proceso_fdisk(Lista* lalista){
    NodoL* actual=lalista->inicio;

    int categoria, resultado;
    int proceso=0;
    int comando[9]={-1,-1,-1,-1,-1,-1,-1,-1};

    //Datos por default
    FDISK* admin_part = (FDISK*)malloc(sizeof(FDISK));
    admin_part->UNIT[0]='K';
    admin_part->TYPE[0]='P';
    admin_part->FIT[0]='WF';
    admin_part->ADD=0;
    admin_part->MOV=0;

    while(actual!=NULL){
        categoria=actual->categoria;

        switch(categoria){
        case 1:
            if(strcmp("size",actual->comando)==0){
                comando[0]=0;
            }else if(strcmp("path",actual->comando)==0){
                comando[1]=1;
            }else if(strcmp("name",actual->comando)==0){
                comando[2]=2;
            }else{
                printf("\n\nError:\n");
                printf("Comando tipo $: %s, desconocido asegurese de ingresar un comando valido.\n\n", actual->comando);
                break;
            }
        break;
        case 2:
            if(strcmp("unit",actual->comando)==0){
            comando[3]=3;
            }else if(strcmp("type",actual->comando)==0){
            comando[4]=4;
            }else if(strcmp("fit",actual->comando)==0){
            }else if(strcmp("delete",actual->comando)==0){
            }else if(strcmp("add",actual->comando)==0){
            comando[7]=7;
            }else if(strcmp("mov",actual->comando)==0){
            }else{
                printf("\n\nError:\n");
                printf("Comando tipo @: %s, desconocido asegurese de ingresar un comando valido.\n\n", actual->comando);
                break;
            }
        break;
        default:
            printf("\n\nError:\n");
        break;
        }
        actual=actual->siguiente;
    }

}



#include "[MIA]MKDISK_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
-todos los comandos para mkdisk son de tipo obligatorio (1)
-cada metodo servira para realizar las validaciones correspondientes a cada comando
que se usa en mkdisk: size, path y name.
*/

int proceso_tam(char* sentencia);
int proceso_ruta(char* sentencia);
int proceso_nombre(char* sentencia);

void proceso_mkdisk(Lista* lalista){
    NodoL* actual=lalista->inicio;
    int categoria, resultado;
    char* comando="";
    char* sentencia="";
    while(actual!=NULL){
        categoria=actual->categoria;
        switch(categoria){
        case 1:
            if(strcmp("size",actual->comando)==0){

            }else if(strcmp("path",actual->comando)==0){

            }else if(strcmp("name",actual->comando)==0){
                resultado=proceso_nombre(actual->sentencia);
                if(resultado==0){
                    break;
                }else{
                    printf("nombre correcto\n");
                }
            }else{
                printf("\n\nError:\n");
                printf("Comando %s desconocido asegurese de ingresar un comando valido.\n", actual->comando);
            }
            break;
        default:
            printf("\n\nError:\n");
            printf("La categoria de los comandos para MKDISK debe ser\n");
            printf("obligatoria -> ($).\n");
            break;
        }
        actual=actual->siguiente;
    }
}

int proceso_nombre(char* sentencia){
    int correcto=0;
    char aSent[50];
    strcpy(aSent, sentencia);
    int pos=0, estado=0;
    int caracter;
    while(aSent[pos]!=NULL){
        caracter=aSent[pos];
        switch(estado){
        case 0:
            if(islower(caracter)||isupper(caracter)){
                estado=0;
            }else if(caracter=='.'){
                estado=2;
            }else if(caracter=='_'){
                estado=1;
            }else{
                estado=99;
            }
        break;
        case 1:
            if(isdigit(caracter)){
                estado=1;
            }else if(caracter=='.'){
                estado=2;
            }else{
                estado=99;
            }
        break;
        case 2:
            if(strcmp("d", &caracter)==0){
                estado=3;
            }else{
                estado=99;
            }
        break;
        case 3:
            if(strcmp("s", &caracter)==0){
                estado=4;
            }else{
                estado=99;
            }
        break;
        case 4:
            if(strcmp("k", &caracter)==0){
                correcto=1;
            }else{
                correcto=0;
                estado=99;
            }
        break;
        default:
        break;
        }//fin switch

        if(estado==99){
            printf("\n\nError:\n");
            printf("El dato %s no es un nombre valido.\n", sentencia);
            break;
        }
        pos++;
    }
    return correcto;
}

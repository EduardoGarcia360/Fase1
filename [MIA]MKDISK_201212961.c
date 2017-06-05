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
-como son 3 procesos al estar los 3 correctos se procede a crear el archivo
*/

int proceso_tam(char* sentencia);
int proceso_ruta(char* sentencia);
int validar_ruta(char* ruta);
int proceso_nombre(char* sentencia);

void proceso_mkdisk(Lista* lalista){
    NodoL* actual=lalista->inicio;
    int categoria, resultado;
    int proceso=0;
    char* comando="";
    char* sentencia="";
    while(actual!=NULL){
        categoria=actual->categoria;
        switch(categoria){
        case 1:
            if(strcmp("size",actual->comando)==0){
                resultado=proceso_tam(actual->sentencia);
                if(resultado==0){
                    break;
                }else{
                    proceso++;
                    printf("si es multiplo :v\n");
                }
            }else if(strcmp("path",actual->comando)==0){
                resultado=proceso_ruta(actual->sentencia);
                if(resultado==0){
                    break;
                }else{
                    proceso++;
                    printf("que wena ruta alv\n");
                }
            }else if(strcmp("name",actual->comando)==0){
                resultado=proceso_nombre(actual->sentencia);
                if(resultado==0){
                    break;
                }else{
                    proceso++;
                    printf("que wen nombre xdxd\n");
                }
            }else{
                printf("\n\nError:\n");
                printf("Comando: %s, desconocido asegurese de ingresar un comando valido.\n", actual->comando);
            }
            break;
        default:
            printf("\n\nError:\n");
            printf("La categoria de los comandos para MKDISK deben ser\n");
            printf("obligatoria -> ($).\n");
            break;
        }
        actual=actual->siguiente;
    }

    if(proceso==3){
        printf("aki aria mi archivo si pudiera hacerlo >:v\n");
    }else{
        printf("proceso fallido.\n");
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
            printf("El dato: %s, no es un nombre valido.\n", sentencia);
            break;
        }
        pos++;
    }
    return correcto;
}

int proceso_ruta(char* sentencia){
    int correcto=0;
    correcto=validar_ruta(sentencia);
    return correcto;
}

int validar_ruta(char* ruta){
    int correcto=0;
    char aRuta[50];
    strcpy(aRuta, ruta);
    int pos=0, estado=0;
    int caracter;
    while(aRuta[pos]!=NULL){
        caracter=aRuta[pos];
        switch(estado){
        case 0:
            if(caracter=='"'){
                estado=1;
            }else{
                estado=99;
            }
        break;
        case 1:
            if(caracter=='/'){
                estado=2;
            }else{
                estado=99;
            }
        break;
        case 2:
            if(islower(caracter)||isupper(caracter)){
                estado=2;
            }else if(caracter=='/'){
                estado=3;
            }else{
                estado=99;
            }
        break;
        case 3:
            if(islower(caracter)||isupper(caracter)){
                estado=2;
                correcto=0;
            }else if(caracter=='"'){
                correcto=1;
            }else{
                estado=99;
            }
        break;
        }//fin switch

        if(estado==99){
            printf("\n\nError:\n");
            printf("La ruta: %s\n", ruta);
            printf("no cumple con los requisitos para ser valida.\n");
            break;
        }
        pos++;
    }
    return correcto;
}

int proceso_tam(char* sentencia){
    int correcto=0;
    char aSent[4];
    strcpy(aSent, sentencia);
    int numero = atoi(aSent);
    int mod = numero%8;
    if(mod==0){
        correcto=1;
    }

    return correcto;
}






////naaaaaaaaaaaada

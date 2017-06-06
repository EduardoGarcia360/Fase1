#include "[MIA]RMDISK_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
-esta seccion solamente contiene el parametro path.
-es de tipo obligatorio (1)
*/

int rmproceso_ruta(char* sentencia);
int rmvalidar_ruta(char* ruta);


void proceso_rmdisk(Lista* lalista){
    NodoL* actual=lalista->inicio;
    int categoria, resultado;
    int proceso;
    char* comando="";
    char* sentencia="";
    while(actual!=NULL){
        categoria=actual->categoria;
        switch(categoria){
            case 1:
                if(strcmp("path",actual->comando)==0){
                    resultado=rmproceso_ruta(actual->sentencia);
                    if(resultado==0){
                        break;
                    }else{
                        proceso++;
                        printf("que wena ruta alv\n");
                    }
                }else{
                    printf("\n\nError:\n");
                    printf("Comando: %s, desconocido para RMDISK unicamente comando path.\n", actual->comando);
                }
            break;
            default:
                printf("\n\nError:\n");
                printf("La categoria del comando path en RMDISK\n");
                printf("debe ser obligatoria -> ($).\n");
            break;
        }
        actual=actual->siguiente;
    }

    if(proceso==1){
        printf("borrar archivo alv :v\n");
    }else{
        printf("Proceso para RMDISK fallido.\n");
    }
}

int rmproceso_ruta(char* sentencia){
    int restultado;
    restultado=rmvalidar_ruta(sentencia);
    return restultado;
}

int rmvalidar_ruta(char* ruta){
    int correcto=0;
    char aRuta[75];
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
                if(islower(caracter)||isupper(caracter)||isspace(caracter)){
                    estado=2;
                }else if(caracter=='/'){
                    estado=3;
                }else if(caracter=='_'){
                    estado=4;
                }else{
                    estado=99;
                }
            break;
            case 3:
                if(islower(caracter)||isupper(caracter)){
                    estado=2;
                }else{
                    estado=99;
                }
            break;
            case 4:
                if(isdigit(caracter)){
                    estado=5;
                }else{
                    estado=99;
                }
            break;
            case 5:
                if(isdigit(caracter)){
                    estado=5;
                }else if(caracter=='.'){
                    estado=6;
                }else{
                    estado=99;
                }
            break;
            case 6:
                if(strcmp("d", &caracter)==0){
                    estado=7;
                }else{
                    estado=99;
                }
            break;
            case 7:
                if(strcmp("s", &caracter)==0){
                    estado=8;
                }else{
                    estado=99;
                }
            break;
            case 8:
                if(strcmp("k", &caracter)==0){
                    estado=9;
                }else{
                    estado=99;
                }
            break;
            case 9:
                if(caracter=='"'){
                    correcto=1;
                }else{
                    correcto=0;
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



















///naaaaaada

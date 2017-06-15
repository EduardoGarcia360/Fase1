#include "[MIA]MOUNT_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generar_id(char* ruta);
char* getNombre_disco(char* ruta);

void proceso_mount(Lista* lalista){
    NodoL* actual=lalista->inicio;

    int categoria, resultado;
    int proceso=0, fallo=0;
    char* ruta="";
    char* nombre="";

    while(actual!=NULL){
        categoria=actual->categoria;

        switch(categoria){
        case 1:
            if(strcmp("path", actual->comando)==0){
                resultado=fvalidar_ruta(actual->sentencia);//uso la validacion de FDISK
                if(resultado==0){
                    proceso=0;
                    fallo=1;
                }else{
                    proceso++;
                    ruta=quitar_comillas(actual->sentencia);
                }
            }else if(strcmp("name", actual->comando)==0){
                resultado=fvalidar_nombre(actual->sentencia);
                if(resultado==0){
                    proceso=0;
                    fallo=1;
                }else{
                    proceso++;
                    nombre=concat(nombre, actual->sentencia);
                    //strcpy(nombre, actual->sentencia);
                }
            }else{
                printf("\n\nError:\n");
                printf("El comando %s no pertenece a MOUNT.\n\n", actual->comando);
                fallo=1;
            }
            break;
        default:
            printf("\n\nError!\n");
            break;
        }

        if(fallo==1){
            break;
        }
        actual=actual->siguiente;
    }

    if(proceso==2){
        //hacer mount
        generar_id(ruta);
    }else{
        printf("Proceso para MOUNT fallido.\n");
    }
}

void generar_id(char* ruta){
    char* algo = "";
    algo = getNombre_disco(ruta);
    printf("nombre limpio: %s\n", algo);
}

char* getNombre_disco(char* ruta){
    char aRuta[100];
    strcpy(aRuta, ruta);
    int pos=0, estado=0;
    int caracter;
    char* lexema="";

    while(aRuta[pos]!=NULL){
        caracter=aRuta[pos];
        if(islower(caracter) || isdigit(caracter) || caracter=='_'){
            lexema=concat(lexema, &caracter);
        }else if(caracter=='.'){
            break;
        }else{
            lexema=limpiar();
        }
        pos++;
    }
    return lexema;
}


////naaaaaaaaaaaaaaaaaaaaaaadaaaa

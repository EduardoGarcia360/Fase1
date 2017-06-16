#include "[MIA]MOUNT_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generar_id(ListaM* mi_lista, char* ruta, char* nombre_particion);
char* getNombre_disco(char* ruta);

void proceso_mount(Lista* lalista, ListaM* lalistam){
    NodoL* actual=lalista->inicio;


    int categoria, resultado;
    int proceso=0, fallo=0;
    char* ruta="";
    char* nombre_particion="";

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
                    nombre_particion=concat(nombre_particion, actual->sentencia);
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
        //en este punto ya tengo ruta, nombre de la particion y nombre del disco dentro de la ruta
        generar_id(lalistam, ruta, nombre_particion);
    }else{
        printf("Proceso para MOUNT fallido.\n");
    }
}

void generar_id(ListaM* lalistam, char* ruta, char* nombre_particion){
    //se obtiene el nombre del disco
    showParticionesMontadas(lalistam);
    char* nombre_disco = "";
    nombre_disco = getNombre_disco(ruta);

    TMP* datos = (TMP*)malloc(sizeof(TMP));
    datos = ultima_letra(lalistam, nombre_disco, 'a');

    char id[5];
    sprintf(id, "vd%c%i", datos->LETRA, datos->NUMERO);
    printf("id para meter %s\n", &id);
    addDisco(lalistam, ruta, nombre_particion, nombre_disco, datos->LETRA, datos->NUMERO, id);
    showParticionesMontadas(lalistam);
}

char* getNombre_disco(char* ruta){
    //recibe: /home/tugfa/elsad.dsk
    //retorna: elsad
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

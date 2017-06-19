#include "[MIA]MOUNT_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generar_id(ListaM* mi_lista, char* ruta, char* nombre_particion);
char* getNombre_disco(char* ruta);
int validar_disco(char* ruta, char* nombre_particion);

void proceso_mount(Lista* lalista, ListaM* lalistam){
    if(lalista->inicio == NULL){
        /*solo ingreso la palabra mount*/
        printf("Mostrando discos montados:\n");
        showParticionesMontadas(lalistam);
    }else{
        /*hay mas datos*/
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
}

void generar_id(ListaM* lalistam, char* ruta, char* nombre_particion){
    int r;
    r = validar_disco(ruta, nombre_particion);

    if(r==1){
        char* nombre_disco = "";
        nombre_disco = getNombre_disco(ruta);

        TMP* datos = (TMP*)malloc(sizeof(TMP));
        datos = letra_numero(lalistam, nombre_disco);

        char id[5];
        sprintf(id, "vd%c%i", datos->LETRA, datos->NUMERO);

        addDisco(lalistam, ruta, nombre_particion, nombre_disco, datos->LETRA, datos->NUMERO, id);
        printf("\nLa particion '%s' del disco '%s' fue montada exitosamente con el ID: '%s'\n\n", nombre_particion, nombre_disco, id);
    }

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

int validar_disco(char* ruta, char* nombre_particion){
    /*se valida que exista el disco y el nombre de la particion dentro*/
    int correcto=0;
    FILE* f = fopen(ruta, "r+b");
    if(f!=NULL){
        Mbr mbr_leido;
        fseek(f, 0, SEEK_SET);
        fread(&mbr_leido, sizeof(Mbr), 1, f);
        if(strcmp(&mbr_leido.mbr_partition_1.part_name, nombre_particion)==0 || strcmp(&mbr_leido.mbr_partition_2.part_name, nombre_particion)==0 || strcmp(&mbr_leido.mbr_partition_3.part_name, nombre_particion)==0 || strcmp(&mbr_leido.mbr_partition_4.part_name, nombre_particion)==0){
            /*el nombre de particion buscado si existe dentro del archivo*/
            correcto=1;
        }else{
            printf("\n\nError:\n");
            printf("El nombre '%s' no existe dentro del disco solicitado.\n\n", nombre_particion);
        }
        fclose(f);
    }else{
        printf("\n\nError:\n");
        printf("El archivo de disco al que intenta acceder no existe en la ruta indicada.\n");
        printf("Ruta ingresada: %s\n\n", ruta);
    }
    return correcto;
}

////naaaaaaaaaaaaaaaaaaaaaaadaaaa

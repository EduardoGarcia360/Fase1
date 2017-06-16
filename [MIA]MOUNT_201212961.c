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
    char* nombre_disco = "";
    nombre_disco = getNombre_disco(ruta);

    TMP* datos = (TMP*)malloc(sizeof(TMP));
    datos = ultima_letra(lalistam, nombre_disco, 'a');

    if(datos->LETRA == 'a' && datos->NUMERO == 1 && lalistam->inicio == NULL){
        //primer dato ingresado en la lista
        printf("primera asignacion\n");
        char* id="";
        id=concat(id, "vd");
        id=concat(id, &datos->LETRA);
        char tmp = datos->NUMERO+'0';
        id=concat(id, &tmp);

        addDisco(lalistam, ruta, nombre_particion, nombre_disco, datos->LETRA, datos->NUMERO, id);
    }else if(datos->LETRA == 'a' && datos->NUMERO > 1){
        //nueva particion
        printf("segunda asignacion\n");
        int n = datos->NUMERO;
        n++;
        char* id="";
        id=concat(id, "vd");
        id=concat(id, &datos->LETRA);
        char tmp = n +'0';
        id=concat(id, &tmp);

        addDisco(lalistam, ruta, nombre_particion, nombre_disco, datos->LETRA, n, id);
    }else if(datos->LETRA > 'a' && datos->NUMERO == 1){
        printf("tercera asignacion\n");
        //nuevo disco ingresado por ser mayor a 'a' le corresponde la siguiente letra
        //al hacer lo siguiente avanzamos de letra (ver ejemplo comentado)
        char le = datos->LETRA;
         le++;
        char* id="";
        id=concat(id, "vd");
        id=concat(id, &le);
        char tmp = datos->NUMERO+'0';
        id=concat(id, &tmp);

        addDisco(lalistam, ruta, nombre_particion, nombre_disco, le, datos->NUMERO, id);
    }else{
        printf("cuarta asignacion\n");
        //disco ya ingresado con distinta particion le corresponde siguiente numero
        int t = datos->NUMERO;
        datos->NUMERO = t + 1;
        char* id="";
        id=concat(id, "vd");
        id=concat(id, &datos->LETRA);
        char tmp = datos->NUMERO+'0';
        id=concat(id, &tmp);

        addDisco(lalistam, ruta, nombre_particion, nombre_disco, datos->LETRA, datos->NUMERO, id);
    }
    /*
    en caso de no entender el segundo if
    char letra = 'a';
    printf("%c\n", letra);
    letra++;
    printf("%c\n", letra);
    letra++;
    printf("%c\n", letra);
    letra++;
    printf("%c\n", letra);
    */
    //addDisco(lalistam, ruta, nombre_particion, algo, 'a', 1, "vda1");
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

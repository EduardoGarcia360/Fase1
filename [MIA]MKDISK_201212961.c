#include "[MIA]MKDISK_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

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
void crear_directorio(char* ruta);
void crear_disco(int tam, char* nombre, char* ruta);
void agregar_MBR(char* ruta, int tam);
void copia_seguridad(char* ruta, int tam);
char* quitar_comillas(char* ruta);
char* cambiar_nombre(char* nombre);

void proceso_mkdisk(Lista* lalista){
    NodoL* actual=lalista->inicio;
    int categoria, resultado;
    int proceso=0;
    char* comando="";
    char* sentencia="";

    int tam;
    char* nombre="";
    char* ruta="";
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
                    char aSent[4];
                    strcpy(aSent,actual->sentencia);
                    tam = atoi(aSent);
                }
            }else if(strcmp("path",actual->comando)==0){
                resultado=proceso_ruta(actual->sentencia);
                if(resultado==0){
                    break;
                }else{
                    proceso++;
                    ruta=concat(ruta,actual->sentencia);
                }
            }else if(strcmp("name",actual->comando)==0){
                resultado=proceso_nombre(actual->sentencia);
                if(resultado==0){
                    break;
                }else{
                    proceso++;
                    nombre=concat(nombre,actual->sentencia);
                }
            }else{
                printf("\n\nError:\n");
                printf("Comando: %s, desconocido asegurese de ingresar un comando valido.\n\n", actual->comando);
                break;
            }
            break;
        default:
            printf("\n\nError:\n");
            printf("La categoria de los comandos para MKDISK debe ser\n");
            printf("obligatoria -> ($).\n\n");
            break;
        }
        actual=actual->siguiente;
    }

    if(proceso==3){
        crear_directorio(ruta);
        crear_disco(tam,nombre,ruta);
    }else{
        printf("Proceso para MKDISK fallido.\nVerifique que haya ingresado los datos correctamente.\n\n");
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
            if(islower(caracter)){
                estado=2;
            }else if(caracter=='/'){
                estado=3;
            }else{
                estado=99;
            }
        break;
        case 3:
            if(islower(caracter)){
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

char* quitar_comillas(char* ruta){
    char aRuta[50];
    strcpy(aRuta, ruta);
    int pos=0;
    int caracter;
    char* limpia="";
    while(aRuta[pos]!=NULL){
        caracter=aRuta[pos];
        if(caracter!='"'){
            limpia=concat(limpia, &caracter);
        }
        pos++;
    }
    return limpia;
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

void crear_disco(int tam, char* nombre, char* ruta){
    ruta=quitar_comillas(ruta);
    ruta=concat(ruta,nombre);
    FILE* f = fopen(ruta,"wb");
    if(f!=NULL){
        char buffer[1024];
        for(int i=0; i<tam*1024; i++){
            fwrite(buffer,sizeof(buffer),1,f);
        }
        fclose(f);
        printf("disco creado!\n");
        copia_seguridad(ruta, tam);
        agregar_MBR(ruta, tam);
    }else{
        printf("Error en disco alv\n");
    }
}

void copia_seguridad(char* ruta, int tam){
    ruta=cambiar_nombre(ruta);
    FILE* f = fopen(ruta, "wb");
    if(f!=NULL){
        char buffer[1024];
        for(int i=0; i<tam*1024; i++){
            fwrite(buffer, sizeof(buffer), 1, f);
        }
        fclose(f);
        printf("Copia realizada con exito.\n");
        agregar_MBR(ruta, tam);
    }else{
        printf("Error al crear la copia.\n");
    }
}

char* cambiar_nombre(char* nombre){
    //recibe: /home/eduardo/pruebas/disco_32.dsk
    //retorna: /home/eduardo/pruebas/disco_32_copia.dsk
    char aNombre[100];
    strcpy(aNombre, nombre);
    int pos=0;
    int caracter;
    char* cambiado="";
    while(aNombre[pos]!=NULL){
        caracter=aNombre[pos];
        if(caracter=='.'){
            cambiado=concat(cambiado, "_copia.");
        }else{
            cambiado=concat(cambiado, &caracter);
        }
        pos++;
    }
    return cambiado;
}

void agregar_MBR(char* ruta, int tam){
    Mbr* nuevo = (Mbr*)malloc(sizeof(Mbr));

    nuevo->mbr_tamano=tam*1024*1024; //tamaño en bytes
    nuevo->mbr_fecha_creacion=time(0);
    nuevo->mbr_disk_signature=12;
    /*
    los valores de la estructura Particion llevan valores nulos
    ya que aun no se crean dichas particiones
    */
    nuevo->mbr_partition_1.part_status='n';
    nuevo->mbr_partition_1.part_type='n';
    strcpy(nuevo->mbr_partition_1.part_fit, "n");
    nuevo->mbr_partition_1.part_start=sizeof(Mbr)+1; //la particion inicia despues del tamaño del mbr
    nuevo->mbr_partition_1.part_size=0;
    strcpy(nuevo->mbr_partition_1.part_name,"");

    nuevo->mbr_partition_2.part_status='n';
    nuevo->mbr_partition_2.part_type='n';
    strcpy(nuevo->mbr_partition_2.part_fit, "n");
    nuevo->mbr_partition_2.part_start=0;
    nuevo->mbr_partition_2.part_size=0;
    strcpy(nuevo->mbr_partition_2.part_name,"");

    nuevo->mbr_partition_3.part_status='n';
    nuevo->mbr_partition_3.part_type='n';
    strcpy(nuevo->mbr_partition_3.part_fit, "n");
    nuevo->mbr_partition_3.part_start=0;
    nuevo->mbr_partition_3.part_size=0;
    strcpy(nuevo->mbr_partition_3.part_name,"");

    nuevo->mbr_partition_4.part_status='n';
    nuevo->mbr_partition_4.part_type='n';
    strcpy(nuevo->mbr_partition_4.part_fit, "n");
    nuevo->mbr_partition_4.part_start=0;
    nuevo->mbr_partition_4.part_size=0;
    strcpy(nuevo->mbr_partition_4.part_name,"");

    /*valores para la particion de tipo extendida*/
    nuevo->ebr_particion_1.part_size=0;
    nuevo->ebr_particion_2.part_size=0;
    nuevo->ebr_particion_3.part_size=0;
    nuevo->ebr_particion_4.part_size=0;

    FILE* f=fopen(ruta,"r+b");
    if(f!=NULL){
        fseek(f,0, SEEK_SET);
        fwrite(nuevo, sizeof(Mbr),1,f);
        fclose(f);
        printf("MBR agregado con exito.\n");
    }
}

void crear_directorio(char* ruta){
    char* comando = "mkdir -p ";
    comando=concat(comando, ruta);
    system(comando);
}




////naaaaaaaaaaaada

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

int fvalidar_nombre(char* nombre);
int fvalidar_ruta(char* ruta);
void crear_particion(FDISK* datos);
void par_uno(FILE* f, FDISK* datos, Mbr mbr_leido);
void par_dos(FILE* f, FDISK* datos, Mbr mbr_leido);
void par_tres(FILE* f, FDISK* datos, Mbr mbr_leido);
void par_cuatro(FILE* f, FDISK* datos, Mbr mbr_leido, int restante);
void asignar_primaria(FILE* f, FDISK* datos, Mbr mbr_leido);
void asignar_extendida(FILE* f, FDISK* datos, Mbr mbr_leido);
void asignar_logica(FILE* f, FDISK* datos, Mbr mbr_leido);
int tam_total(FDISK* datos);

void proceso_fdisk(Lista* lalista){
    NodoL* actual=lalista->inicio;

    int categoria, resultado;
    int proceso=0, fallo=0;

    //Datos por default: datos que tienen que aparecer en caso de que falten por ser opcionales.
    FDISK* admin_part = (FDISK*)malloc(sizeof(FDISK));
    admin_part->SIZE=-1;
    admin_part->UNIT='k';
    admin_part->TYPE='p';
    strcpy(admin_part->FIT, "wf");//para mas de dos caracteres
    admin_part->ADD=0;
    admin_part->MOV=0;

    while(actual!=NULL){
        categoria=actual->categoria;

        switch(categoria){
        case 1:
            if(strcmp("size",actual->comando)==0){
                char aSent[2];
                strcpy(aSent,actual->sentencia);
                int tam = atoi(aSent);
                if(tam>0){
                    admin_part->SIZE=tam;
                    proceso++;
                    printf("SIZE EN FDISK: %i\n", admin_part->SIZE);
                }else{
                    proceso=0;
                    printf("\n\nError:\n");
                    printf("El tamaño '%d' debe ser positivo y mayor a cero.\n", tam);
                    fallo=1;
                }
            }else if(strcmp("path",actual->comando)==0){
                resultado=fvalidar_ruta(actual->sentencia);
                if(resultado==0){
                    proceso=0;
                    fallo=1;
                }else{
                    proceso++;
                    actual->sentencia=quitar_comillas(actual->sentencia);
                    strcpy(admin_part->PATH, actual->sentencia);
                    printf("PATH EN FDISK: %s\n", admin_part->PATH);
                }
            }else if(strcmp("name",actual->comando)==0){
                resultado=fvalidar_nombre(actual->sentencia);
                if(resultado==0){
                    proceso=0;
                    fallo=1;
                }else{
                    proceso++;
                    strcpy(admin_part->NAME, actual->sentencia);
                    printf("NAME EN FDISK: %s\n", admin_part->NAME);
                }
            }else{
                printf("\n\nError:\n");
                printf("Comando tipo $: %s, desconocido asegurese de ingresar un comando valido.\n\n", actual->comando);
                fallo=1;
            }
        break;
        case 2:
            if(strcmp("unit",actual->comando)==0){
                if(strcmp("b",actual->sentencia)==0 || strcmp("k",actual->sentencia)==0 || strcmp("m",actual->sentencia)==0){
                    admin_part->UNIT=*actual->sentencia;
                    printf("UNIT EN FDISK: %c\n", admin_part->UNIT);
                }else{
                    printf("\n\nError:\n");
                    printf("La unidad para la particion debe ser en:\n-B: bytes\n-K: kilobytes\n-M: megabytes\n");
                    proceso=0;
                    fallo=1;
                }
            }else if(strcmp("type",actual->comando)==0){
                if(strcmp("p",actual->sentencia)==0 || strcmp("e",actual->sentencia)==0 || strcmp("l",actual->sentencia)==0){
                    admin_part->TYPE=*actual->sentencia;//en lista tipo de dato char*
                    printf("TYPE EN FDISK: %c\n", admin_part->TYPE);
                }else{
                    printf("\n\nError:\n");
                    printf("El tipo de particion debe ser:\n-P: particion primaria\n-E: particion extendida\n-L: particion logica\n");
                    proceso=0;
                    fallo=1;
                }
            }else if(strcmp("fit",actual->comando)==0){
                if(strcmp("bf",actual->sentencia)==0||strcmp("ff",actual->sentencia)==0||strcmp("wf",actual->sentencia)==0){
                    strcpy(admin_part->FIT, actual->sentencia);
                    printf("FIT EN FDISK: %s\n", admin_part->FIT);
                }else{
                    printf("\n\nError:\n");
                    printf("El ajuste para la particion debe ser:\n-BF: Best Fit (mejor ajuste)\n");
                    printf("-FF: First Fit (primer ajuste)\n");
                    printf("-WF: Worst Fit (peor ajuste)\n");
                    proceso=0;
                    fallo=1;
                }
            }else if(strcmp("delete",actual->comando)==0){
            }else if(strcmp("add",actual->comando)==0){
            }else if(strcmp("mov",actual->comando)==0){
            }else{
                printf("\n\nError:\n");
                printf("Comando tipo @: %s, desconocido asegurese de ingresar un comando valido.\n\n", actual->comando);
                proceso=0;
                fallo=1;
            }
        break;
        default:
            printf("\n\nError:\n");
        break;
        }

        if(fallo==1){
            break;
        }
        actual=actual->siguiente;
    }

    if(proceso>=3){
        crear_particion(admin_part);
    }else{
        printf("Proceso para FDISK fallido.\n");
    }
}

int fvalidar_nombre(char* nombre){
    int correcto=0;
    char aNombre[15];
    strcpy(aNombre,nombre);
    int pos=0, estado=0;
    int caracter;
    while(aNombre[pos]!=NULL){
        caracter=aNombre[pos];
        switch(estado){
            case 0:
                if(islower(caracter)||isupper(caracter)){
                    estado=1;
                }else{
                    estado=99;
                }
            break;
            case 1:
                if(islower(caracter)&&aNombre[pos+1]==NULL){
                    correcto=1;
                }else if(islower(caracter)){
                    estado=1;
                }else if(isdigit(caracter)&&aNombre[pos+1]==NULL){
                    correcto=1;
                }else if(isdigit(caracter)){
                    estado=2;
                }else{
                    estado=99;
                }
            break;
            case 2:
                if(isdigit(caracter)&&aNombre[pos+1]==NULL){
                    correcto=1;
                }else if(isdigit(caracter)){
                    estado=2;
                }else{
                    estado=99;
                }
            break;
        }

        if(estado==99){
            printf("\n\nError:\n");
            printf("El nombre: %s\n", nombre);
            printf("no cumple con los requisitos para ser valido.\n");
            break;
        }
        pos++;
    }
    return correcto;
}

int fvalidar_ruta(char* ruta){
    int correcto=0;
    char aRuta[75];
    strcpy(aRuta,ruta);
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
                    estado=3;
                }else{
                    estado=99;
                }
            break;
            case 3:
                if(islower(caracter) || isspace(caracter)){
                    estado=3;
                }else if(caracter=='/'){
                    estado=4;
                }else if(caracter=='.'){
                    estado=6;
                }else if(caracter=='_' || isdigit(caracter)){
                    estado=5;
                }else{
                    estado=99;
                }
            break;
            case 4:
                if(islower(caracter)){
                    estado=3;
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
        }

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

void crear_particion(FDISK* datos){
    Mbr mbr_leido;
    int extendida_activa=0;
    FILE* f = fopen(datos->PATH,"r+b");
    if(f!=NULL){
        fseek(f, 0, SEEK_SET);//nos posicionamos al inicio del archivo
        fread(&mbr_leido, sizeof(Mbr), 1, f);//leemos el MBR que agregamos en la parte de MKDISK

        int tam_ingresado=tam_total(datos);//retorna el tamaño en bytes
        if(tam_ingresado < mbr_leido.mbr_tamano){
            if(datos->TYPE=='p'){
                asignar_primaria(f, datos, mbr_leido);
            }else if(datos->TYPE=='e'){
                asignar_extendida(f, datos, mbr_leido);
            }else if(datos->TYPE=='l'){
                asignar_logica(f, datos, mbr_leido);
            }
        }else{
            int tmp1 = mbr_leido.mbr_tamano/1024;
            tmp1 = tmp1/1024;
            printf("\n\nError:\n");
            printf("El tamaño ingresado %i en %c sobrepasa el tamaño maximo del disco que es %i MB.\n", datos->SIZE, datos->UNIT, tmp1);
        }

        fclose(f);
    }else{
        printf("\n\nError:\n");
        printf("El archivo de disco al que intenta acceder no existe en la ruta indicada.\n");
        printf("Ruta ingresada: %s\n", datos->PATH);
    }
}

/* para particiones de tipo primaria */
void asignar_primaria(FILE* f, FDISK* datos, Mbr mbr_leido){
    if(mbr_leido.mbr_partition_1.part_size==0){
        par_uno(f, datos, mbr_leido);
    }else if(mbr_leido.mbr_partition_2.part_size==0){
        if(strcmp(mbr_leido.mbr_partition_1.part_name, datos->NAME)==0){
            printf("\n\nError:\n");
            printf("El nombre: %s que trata de asignar ya existe en otra particion.\n", datos->NAME);
        }else{
            par_dos(f, datos, mbr_leido);
        }
    }else if(mbr_leido.mbr_partition_3.part_size==0){
        if(strcmp(mbr_leido.mbr_partition_1.part_name, datos->NAME)==0 || strcmp(mbr_leido.mbr_partition_2.part_name, datos->NAME)==0){
            printf("\n\nError:\n");
            printf("El nombre: %s que trata de asignar ya existe en otra particion.\n", datos->NAME);
        }else{
            par_tres(f, datos, mbr_leido);
        }
    }else if(mbr_leido.mbr_partition_4.part_size==0){
        if(strcmp(mbr_leido.mbr_partition_1.part_name, datos->NAME)==0 || strcmp(mbr_leido.mbr_partition_2.part_name, datos->NAME)==0 || strcmp(mbr_leido.mbr_partition_3.part_name, datos->NAME)==0){
            printf("\n\nError:\n");
            printf("El nombre: %s que trata de asignar ya existe en otra particion.\n", datos->NAME);
        }else{
            /*se calcula el tamaño exacto que resta para la particion 4*/
            int tam_total_disco = mbr_leido.mbr_tamano;
            int restante = tam_total_disco-(sizeof(Mbr)+mbr_leido.mbr_partition_1.part_size+mbr_leido.mbr_partition_2.part_size+mbr_leido.mbr_partition_3.part_size);

            int ingresado = tam_total(datos);//cantidad ingresada por el usuario para esta particion
            int mega = 1024*1024;//un megabyte

            if((ingresado-restante)<mega){
                /*si lo ingresado difiere en menos de un 1MB*/
                par_cuatro(f, datos, mbr_leido, restante);
            }else{
                /*si al hacer la resta el resultado es mayor a 1MB*/
                printf("\n\nError:\n");
                printf("El tamaño ingresado para la particion 4 sobrepasa lo restante en el disco\n");
                printf("Espacio restante en disco: %i en bytes\n", restante);
            }
        }
    }else{
        printf("Las cuatro particiones ya estan llenas.\nCree otro disco o borre una particion.\n");
    }
}

void par_uno(FILE* f, FDISK* datos, Mbr mbr_leido){
    printf("*****Ingresando en la Particion 1*****\n");
    fseek(f, 0, SEEK_SET);

    /*asignamos los datos del MBR leido en la particion 1*/
    mbr_leido.mbr_partition_1.part_status='n';

    mbr_leido.mbr_partition_1.part_type = datos->TYPE;

    strcpy(mbr_leido.mbr_partition_1.part_fit, datos->FIT);
    //strncpy(mbr_leido.mbr_partition_1.part_fit, datos->FIT, 2);

    mbr_leido.mbr_partition_1.part_size = tam_total(datos);//en bytes

    //se indica donde empezara la particion 2
    mbr_leido.mbr_partition_2.part_start=sizeof(Mbr)+mbr_leido.mbr_partition_1.part_size+1;

    strcpy(mbr_leido.mbr_partition_1.part_name, datos->NAME);

    printf("*****Termiando de agregar datos\n.\n.\n");

    printf("*****RESUMEN DE DATOS INGRESADOS EN LA PARTICION 1:\n");
    printf("-Tipo de particion: %c\n", mbr_leido.mbr_partition_1.part_type);
    printf("-Ajuste de particion (FIT): %s\n", mbr_leido.mbr_partition_1.part_fit);
    printf("-Tamaño asignado: %i en %c\n", datos->SIZE, datos->UNIT);
    printf("-Inicio de particion: %i en bytes\n", mbr_leido.mbr_partition_1.part_start);
    printf("-Nombre asignado: %s\n", mbr_leido.mbr_partition_1.part_name);
    int tam_total_disco = mbr_leido.mbr_tamano;
    int restante = tam_total_disco-(sizeof(Mbr)+mbr_leido.mbr_partition_1.part_size);
    printf("-Espacio restante: %i\n\n", restante);

    //se guardan los cambios
    fwrite(&mbr_leido, sizeof(Mbr), 1, f);
}

void par_dos(FILE* f, FDISK* datos, Mbr mbr_leido){
    printf("*****Ingresando en la Particion 2*****\n");
    fseek(f, 0, SEEK_SET);

    /*asignamos los datos del MBR leido en la particion 2*/
    mbr_leido.mbr_partition_2.part_status='n';

    mbr_leido.mbr_partition_2.part_type = datos->TYPE;

    strcpy(mbr_leido.mbr_partition_2.part_fit, datos->FIT);
    //strncpy(mbr_leido.mbr_partition_2.part_fit, datos->FIT, 2);

    //se indica donde empezara la particion 3
    mbr_leido.mbr_partition_3.part_start = sizeof(Mbr)+mbr_leido.mbr_partition_1.part_size+mbr_leido.mbr_partition_2.part_size+1;

    mbr_leido.mbr_partition_2.part_size = tam_total(datos);

    strcpy(mbr_leido.mbr_partition_2.part_name, datos->NAME);

    printf("*****Termiando de agregar datos\n.\n.\n");

    printf("*****RESUMEN DE DATOS INGRESADOS EN LA PARTICION 2:\n");
    printf("-Tipo de particion: %c\n", mbr_leido.mbr_partition_2.part_type);
    printf("-Ajuste de particion (FIT): %s\n", mbr_leido.mbr_partition_2.part_fit);
    printf("-Tamaño asignado: %i en %c\n", datos->SIZE, datos->UNIT);
    printf("-Inicio de particion: %i en bytes\n", mbr_leido.mbr_partition_2.part_start);
    printf("-Nombre asignado: %s\n", mbr_leido.mbr_partition_2.part_name);
    int tam_total_disco = mbr_leido.mbr_tamano;
    int restante = tam_total_disco-(sizeof(Mbr)+mbr_leido.mbr_partition_1.part_size+mbr_leido.mbr_partition_2.part_size);
    printf("-Espacio restante: %i\n\n", restante);

    //se guardan los cambios
    fwrite(&mbr_leido, sizeof(Mbr), 1, f);
}

void par_tres(FILE* f, FDISK* datos, Mbr mbr_leido){
    printf("*****Ingresando en la Particion 3*****\n");
    fseek(f, 0, SEEK_SET);

    /*asignamos los datos del MBR leido en la particion 3*/
    mbr_leido.mbr_partition_3.part_status='n';

    mbr_leido.mbr_partition_3.part_type = datos->TYPE;

    strcpy(mbr_leido.mbr_partition_3.part_fit, datos->FIT);
    //strncpy(mbr_leido.mbr_partition_3.part_fit, datos->FIT, 2);

    //se indica donde empezara la particion 4
    mbr_leido.mbr_partition_4.part_start = sizeof(Mbr)+mbr_leido.mbr_partition_1.part_size+mbr_leido.mbr_partition_2.part_size+mbr_leido.mbr_partition_3.part_size+1;

    mbr_leido.mbr_partition_3.part_size = tam_total(datos);

    strcpy(mbr_leido.mbr_partition_3.part_name, datos->NAME);

    printf("*****Termiando de agregar datos\n.\n.\n");

    printf("*****RESUMEN DE DATOS INGRESADOS EN LA PARTICION 3:\n");
    printf("-Tipo de particion: %c\n", mbr_leido.mbr_partition_3.part_type);
    printf("-Ajuste de particion (FIT): %s\n", mbr_leido.mbr_partition_3.part_fit);
    printf("-Tamaño asignado: %i en %c\n", datos->SIZE, datos->UNIT);
    printf("-Inicio de particion: %i en bytes\n", mbr_leido.mbr_partition_3.part_start);
    printf("-Nombre asignado: %s\n", mbr_leido.mbr_partition_3.part_name);
    int tam_total_disco = mbr_leido.mbr_tamano;
    int restante = tam_total_disco-(sizeof(Mbr)+mbr_leido.mbr_partition_1.part_size+mbr_leido.mbr_partition_2.part_size+mbr_leido.mbr_partition_3.part_size);
    printf("-Espacio restante: %i\n\n", restante);

    //se guardan los cambios
    fwrite(&mbr_leido, sizeof(Mbr), 1, f);
}

void par_cuatro(FILE* f, FDISK* datos, Mbr mbr_leido, int restante){
    printf("*****Ingresando en la Particion 4*****\n");
    fseek(f, 0, SEEK_SET);

    /*asignamos los datos del MBR leido en la particion 4*/
    mbr_leido.mbr_partition_4.part_status='n';

    mbr_leido.mbr_partition_4.part_type = datos->TYPE;

    strncpy(mbr_leido.mbr_partition_4.part_fit, datos->FIT, 2);

    mbr_leido.mbr_partition_4.part_size = tam_total(datos);

    strcpy(mbr_leido.mbr_partition_4.part_name, datos->NAME);

    printf("*****Termiando de agregar datos\n.\n.\n");

    printf("*****RESUMEN DE DATOS INGRESADOS EN LA PARTICION 4:\n");
    printf("-Tipo de particion: %c\n", mbr_leido.mbr_partition_4.part_type);
    printf("-Ajuste de particion (FIT): %s\n", mbr_leido.mbr_partition_4.part_fit);
    printf("-Tamaño asignado: %i en bytes\n", restante);
    printf("-Inicio de particion: %i en bytes\n", mbr_leido.mbr_partition_4.part_start);
    printf("-Nombre asignado: %s\n", mbr_leido.mbr_partition_4.part_name);
    int restante_p4 = restante - mbr_leido.mbr_partition_4.part_size;
    printf("-Espacio restante para asignar a la particion 4: %i\n\n", restante_p4);

    //se guardan los cambios
    fwrite(&mbr_leido, sizeof(Mbr), 1, f);
}

/* para particiones de tipo extendida */
void asignar_extendida(FILE* f, FDISK* datos, Mbr mbr_leido){
    /*primero valido si alguna de las 4 particiones ya tiene el tipo extendida*/
    if(strcmp(mbr_leido.mbr_partition_1.part_type, datos->TYPE)==0 || strcmp(mbr_leido.mbr_partition_2.part_type, datos->TYPE)==0 || strcmp(mbr_leido.mbr_partition_3.part_type, datos->TYPE)==0 || strcmp(mbr_leido.mbr_partition_4.part_type, datos->TYPE)==0){
        printf("\n\nError:\n");
        printf("Ya existe una particion con el tipo Extendida,\nno puede haber mas de 1 particion de tipo extendida.\n");
    }else{
        if(mbr_leido.mbr_partition_1.part_size==0){
        }else if(mbr_leido.mbr_partition_2.part_size==0){
        }else if(mbr_leido.mbr_partition_3.part_size==0){
        }else if(mbr_leido.mbr_partition_4.part_size==0){
        }else{
            printf("\n\nError:\n");
            printf("Las cuatro particiones ya estan llenas.\nCree otro disco o borre una particion.\n");
        }
    }
}

/* para particiones de tipo logica */
void asignar_logica(FILE* f, FDISK* datos, Mbr mbr_leido){
    if(mbr_leido.mbr_partition_1.part_type=='e'){
        //algo xdxd
    }else if(mbr_leido.mbr_partition_1.part_type=='e'){
        //algo xdxd
    }else if(mbr_leido.mbr_partition_1.part_type=='e'){
        //algo xdxd
    }else if(mbr_leido.mbr_partition_1.part_type=='e'){
        //algo xdxd
    }else{
        printf("\n\nError:\n");
        printf("No existen particiones de tipo Extendida en la que se pueda crear una particion Logica.\n");
    }
}

int tam_total(FDISK* datos){
    int d=datos->SIZE;
    int retorno=0;
    if(datos->UNIT=='b'){
        retorno = d;
    }else if(datos->UNIT=='k'){
        retorno = d*1024;
    }else{
        retorno = d*1024*1024;
    }
    return retorno;
}



//naaaaaaaaaaaaaaaaaadaa

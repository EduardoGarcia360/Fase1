#include "[MIA]Reportes_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int re_validar_ruta(char* ruta);
temp* directorio_nombre(char* ruta);
void graficas(ListaM* lalistam, char* ruta, char* tipo_grafica, char* id, temp* aux);
void grafica_mbr(ListaM* lalistam, char* ruta, char* tipo_grafica, char* id, temp* aux);
void grafica_disk(ListaM* lalistam, char* ruta, char* tipo_grafica, char* id, temp* aux);
NodoM* getNodoMount(ListaM* lalistam, char* id);

void proceso_rep(Lista* lalista, ListaM* lalistam){
    showLista(lalista);
    NodoL* actual = lalista->inicio;

    int proceso=0, fallo=0;
    int categoria, resultado;
    char* ruta="";
    char* grafica="";
    char* id="";
    temp* aux = (temp*)malloc(sizeof(temp));

    while(actual!=NULL){
        categoria = actual->categoria;
        switch(categoria){
        case 1:
            if(strcmp("id", actual->comando)==0){
                resultado=buscar_id(lalistam, actual->sentencia);
                if(resultado==0){
                    proceso=0;
                    fallo=1;
                }else{
                    id=actual->sentencia;
                    printf("id: %s\n", id);
                    proceso++;
                }
            }else if(strcmp("path", actual->comando)==0){
                resultado=re_validar_ruta(actual->sentencia);
                if(resultado==0){
                    proceso=0;
                    fallo=1;
                }else{
                    proceso++;
                    ruta=quitar_comillas(actual->sentencia);
                    printf("ruta: %s\n", ruta);
                }
            }else if(strcmp("name", actual->comando)==0){
                if(strcmp("mbr", actual->sentencia)==0 || strcmp("disk", actual->sentencia)==0){
                    grafica=actual->sentencia;
                    printf("grafica: %s\n", grafica);
                    proceso++;
                }else{
                    printf("\n\nGrafica no disponible :(\n\n");
                }
            }else{
                printf("\n\nError:\n");
                printf("El comando %s no pertenece a REP.\n\n", actual->comando);
            }
            break;
        default:
            break;
        }

        if(fallo==1){
            break;
        }
        actual=actual->siguiente;
    }

    if(proceso==3){
        aux = directorio_nombre(ruta);
        graficas(lalistam, ruta, grafica, id, aux);
    }else{
        printf("\n\nProceso para REP fallido.\n\n");
    }
}

int re_validar_ruta(char* ruta){
    int correcto=0;
    char aRuta[100];
    strcpy(aRuta, ruta);
    int pos=0, estado=0, con_comillas=0;
    int caracter;
    while(aRuta[pos]!=NULL){
        caracter=aRuta[pos];
        switch(estado){
        case 0:
                if(caracter=='"'){
                    estado=1;
                    con_comillas=1;
                }else if(caracter=='/'){
                    estado=5;
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
                if(islower(caracter) || isspace(caracter) && islower(aRuta[pos+1])){
                    estado=3;
                }else if(caracter=='/'){
                    estado=4;
                }else if(isdigit(caracter) || isspace(caracter) && isdigit(aRuta[pos+1])){
                    estado= 6;
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
                if(islower(caracter)){
                    estado=3;
                }else{
                    estado=99;
                }
            break;
            case 6:
                if(isdigit(caracter)){
                    estado=6;
                }else if(caracter=='.'){
                    estado=7;
                }else{
                    estado=99;
                }
            break;
            case 7:
                if(strcmp("j", &caracter)==0){
                    estado=8;
                }else{
                    estado=99;
                }
            break;
            case 8:
                if(strcmp("p", &caracter)==0){
                    estado=9;
                }else{
                    estado=99;
                }
            break;
            case 9:
                if(strcmp("g", &caracter)==0 || con_comillas==1){
                    estado=10;
                }else if(strcmp("g", &caracter)==0 || con_comillas==0){
                    correcto=1;
                }else{
                    estado=99;
                }
            break;
            case 10:
                if(con_comillas==0){
                    estado=99;
                }else if(caracter=='"'){
                    correcto=1;
                }else{
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

temp* directorio_nombre(char* ruta){
    //recibe: /home/kewena/rutaalv/xdxdxd 2.jpg
    //retorna: temp* aux = [/home/kewena/rutaalv/][xdxdxd 2.jpg]
    char aRuta[100];
    strcpy(aRuta, ruta);
    int pos=0;
    int caracter;
    char* lexema="";
    char* directorio="";
    temp* aux = (temp*)malloc(sizeof(temp));

    while(aRuta[pos] != NULL){
        caracter=aRuta[pos];
        if(islower(caracter) || isspace(caracter) || isdigit(caracter)){
            lexema=concat(lexema, &caracter);
        }else if(caracter=='/'){
            directorio=concat(directorio, lexema);
            directorio=concat(directorio, &caracter);

            lexema=limpiar();
        }else if(caracter=='.'){
            aux->directorio = directorio;

            lexema=concat(lexema, ".jpg");
            aux->nombre_imagen = lexema;
            break;
        }

        pos++;
    }

    return aux;
}

void graficas(ListaM* lalistam, char* ruta, char* tipo_grafica, char* id, temp* aux){
    if(strcmp(tipo_grafica, "disk")==0){
        grafica_disk(lalistam, ruta, tipo_grafica, id, aux);
    }
}

void grafica_disk(ListaM* lalistam, char* ruta, char* tipo_grafica, char* id, temp* aux){
    NodoM* datos_disco = (NodoM*)malloc(sizeof(NodoM));
    datos_disco = getNodoMount(lalistam, id);
    if(datos_disco!=NULL){
        /*disco con el id encontrado*/
        FILE* f = fopen(datos_disco->PATH, "r+b");
        if(f!=NULL){
            /*disco aun en existencia*/
            Mbr mbr_leido;
            fseek(f, 0, SEEK_SET);
            fread(&mbr_leido, sizeof(Mbr), 1, f);
            /*datos del mbr en el disco*/
            char* directorio = aux->directorio;
            directorio=concat(directorio, "archivo.dot");
            FILE* g = fopen(directorio, "w");//como existe el archivo se pueden leer los datos
            if(g!=NULL){
                fprintf(g, "digraph g{\nsubgraph cluster0{\nnode [shape=record, syle=filled];\n");
                fprintf(g, "disk [shape=record, label=\"");
                /*datos particion 1*/
                fprintf(g, "particion 1:\\n");
                if(mbr_leido.mbr_partition_1.part_size==0){
                    fprintf(g, "LIBRE | ");
                }else{
                    fprintf(g, "Nombre: ");
                    fwrite(mbr_leido.mbr_partition_1.part_name, 1, strlen(mbr_leido.mbr_partition_1.part_name), g);
                    fprintf(g, "\\nTipo: ");
                    fprintf(g, &mbr_leido.mbr_partition_1.part_type);
                    fprintf(g, "\\nTamaño: ");
                    fprintf(g, "%d en bytes.", mbr_leido.mbr_partition_1.part_size);
                    fprintf(g, " | ");
                }
                /*datos particion 2*/
                fprintf(g, "particion 2:\\n");
                if(mbr_leido.mbr_partition_2.part_size==0){
                    fprintf(g, "LIBRE | ");
                }else{
                    fprintf(g, "Nombre: ");
                    fwrite(mbr_leido.mbr_partition_2.part_name, 1, strlen(mbr_leido.mbr_partition_2.part_name), g);
                    fprintf(g, "\\nTipo: ");
                    fprintf(g, &mbr_leido.mbr_partition_2.part_type);
                    fprintf(g, "\\nTamaño: ");
                    fprintf(g, "%d en bytes.", mbr_leido.mbr_partition_2.part_size);
                    fprintf(g, " | ");
                }
                /*datos particion 3*/
                fprintf(g, "particion 3:\\n");
                if(mbr_leido.mbr_partition_3.part_size==0){
                    fprintf(g, "LIBRE | ");
                }else{
                    fprintf(g, "Nombre: ");
                    fwrite(mbr_leido.mbr_partition_3.part_name, 1, strlen(mbr_leido.mbr_partition_3.part_name), g);
                    fprintf(g, "\\nTipo: ");
                    fprintf(g, &mbr_leido.mbr_partition_3.part_type);
                    fprintf(g, "\\nTamaño: ");
                    fprintf(g, "%d en bytes.", mbr_leido.mbr_partition_3.part_size);
                    fprintf(g, " | ");
                }
                /*datos particion 4*/
                fprintf(g, "particion 4:\\n");
                if(mbr_leido.mbr_partition_4.part_size==0){
                    fprintf(g, "LIBRE | ");
                }else{
                    fprintf(g, "Nombre: ");
                    fwrite(mbr_leido.mbr_partition_4.part_name, 1, strlen(mbr_leido.mbr_partition_4.part_name), g);
                    fprintf(g, "\\nTipo: ");
                    fprintf(g, &mbr_leido.mbr_partition_4.part_type);
                    fprintf(g, "\\nTamaño: ");
                    fprintf(g, "%d en bytes.", mbr_leido.mbr_partition_4.part_size);
                    fprintf(g, " | ");
                }

                fprintf(g, "\"];");
                fprintf(g, "\nlabel=\"");
                fprintf(g, datos_disco->DISK);
                fprintf(g, "\";\n}\n}");
                fclose(g);
            }else{
                printf("\n\nError:\nNo se pudo crear el archivo para graficar.\n\n");
            }
            fclose(f);
        }else{
            printf("\n\nError:\n");
            printf("Disco no encontrado, el disco ya no se encuentra en la ruta indicada.\n");
            printf("Ultima ruta de '%s' fue: %s\n\n", datos_disco->DISK, datos_disco->PATH);
        }
    }else{
        printf("\n\nError:\n");
        printf("Disco no encontrado, aun no ha montado ningun disco con el siguiente ID: %s\n\n", id);
    }
/*
    char* directorio = aux->directorio;
    directorio=concat(directorio, "archivo.dot");
    printf("dir %s\n", directorio);
    FILE* f = fopen(directorio, "w");//para archivo que tendra el codigo graphviz
    char* nodos="disk [shape=record, label=\"";
    if(f!=NULL){
        //fprintf(f, "digraph g{\nsubgraph cluster0{\nnode [shape=record, syle=filled];\n");

        fclose(f);
    }else{
        printf("\n\nerror al crear el archivo para mbr\n\n");
    }
*/
}

NodoM* getNodoMount(ListaM* lalistam, char* id){
    /*se busca en la lista de MOUNT el disco con el ID buscado*/
    NodoM* actual = (NodoM*)malloc(sizeof(NodoM));
    actual = lalistam->inicio;
    while(actual != NULL){
        if(strcmp(id, actual->ID)==0){
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}



















//////nadaaaaaaaaaa

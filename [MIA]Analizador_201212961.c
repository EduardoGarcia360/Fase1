#include "[MIA]Analizador_201212961.h"
#include "[MIA]ListaSE_201212961.h"
#include "[MIA]MKDISK_201212961.h"
#include "[MIA]RMDISK_201212961.h"
#include "[MIA]FDISK_201212961.h"
#include "[MIA]MKFILE_201212961.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* concat(char* destino, char* letra);// metodo para concatenar
char* limpiar();

/*
primera parte del analisis encargada de verficar si pertenece a mkdisk, rmdisk, etc
*/
void analizador_general(){
    Lista* mi_lista = (Lista*)malloc(sizeof(Lista));
    char linea[200];
    printf("Introduce linea de comando. (max. 200 caracteres):\n");
    scanf("%[^\n]s", &linea);
    //printf("la linea es: %s\n", linea);

    int pos=0, estado=0, correcto=0;
    char* tipo="";
    char* lexema="";
    char* comando="";
	char* sentencia="";
	int categoria;
	int caracter;

	while(linea[pos] != NULL){
	    caracter = linea[pos];
	    //printf("%c\n", caracter);
	    switch(estado){
        case 0:
            if(isspace(caracter)){
                //con espacio se agrega el tipo: mkdisk &size...
                tipo=concat(tipo,lexema);
                //printf("--tipo: %s\n\n", tipo);
                lexema=limpiar();
                estado=1;
            }else if(islower(caracter)||isupper(caracter)){
                caracter=tolower(caracter);
                lexema=concat(lexema, &caracter);
                estado=0;
            }else{
                //no puede venir numero en este punto: mk23disk &size..., o cualquier otro simbolo
                estado=99;
            }
            break;
        case 1:
            if(isspace(caracter)){
                estado=1;
            }else if(caracter=='$'){
                categoria=1;
                //printf("--categoria obligatorio\n");
                estado=2;
            }else if(caracter=='@'){
                categoria=2;
                //printf("--categoria opcional\n");
                estado=2;
            }else{
                estado=99;
            }
            break;
        case 2:
            if(islower(caracter)||isupper(caracter)){
                caracter=tolower(caracter);
                lexema=concat(lexema, &caracter);
                estado=2;
            }else if(caracter=='='){
                //para indicar que lo siguiente sera una sentencia: =>
                estado=3;
            }else{
                estado=99;
            }
            break;
        case 3:
            if(caracter=='>'){
                //comandos serian: size, path, etc
                comando=concat(comando, lexema);
                //printf("--comando: %s\n", comando);
                lexema=limpiar();
                estado=4;
            }else{
                estado=99;
            }
            break;
        case 4:
            if(isspace(caracter) && linea[pos+1]=='$' || isspace(caracter) && linea[pos+1]=='@'){
                //cuando encuentra un espacio indica que termino la sentencia o cuando termina la linea
                //ej. 1: mkdisk $size=>32 $path...
                //ej. 2: mkdisk $size=>32
                sentencia=concat(sentencia, lexema);
                printf("--sentencia: %s\n\n", sentencia);
                correcto=1;
                addFinal(mi_lista, categoria, comando, sentencia);
                lexema=limpiar();
                comando=limpiar();
                sentencia=limpiar();
                estado=1;
            }else if(linea[pos+1]==NULL){
                //entra en esta parte cuando es el final de linea se concatena ya que estamos en el ultimo caracter
                //ej. 1: mkdisk $size=>32 en este caso seria 2.
                caracter=tolower(caracter);
                lexema=concat(lexema, &caracter);
                sentencia=concat(sentencia, lexema);
                printf("--sentencia: %s\n\n", sentencia);
                correcto=1;
                addFinal(mi_lista, categoria, comando, sentencia);
                lexema=limpiar();
                comando=limpiar();
                sentencia=limpiar();
                estado=1;
            }else if(isdigit(caracter)){
                lexema=concat(lexema, &caracter);
                estado=4;
            }else if(isspace(caracter)){
                //ej. 1: rmdisk $path=>"/home/mis doc/eldisco_44.dsk"
                lexema=concat(lexema, &caracter);
                estado=4;
            }else if(islower(caracter)||isupper(caracter)){
                caracter=tolower(caracter);
                lexema=concat(lexema, &caracter);
                estado=4;
            }else if(caracter=='"'||caracter=='/'||caracter=='.'||caracter=='_'){
                lexema=concat(lexema, &caracter);
                estado=4;
            }else{
                estado=99;
            }
            break;
        default:
            printf("Error al analizar cadena, comando desconocido.\n");
            estado=99;
            break;
	    }//fin switch

	    //---------------- estado de error..
	    if(estado==99){
            printf("Error al analizar la cadena formato no valido.\n");
            correcto=0;
            break;
	    }
	    pos++;
	}//fin while

	switch(correcto){
    case 0:
        printf("\n\nError:\n");
        printf("Linea de comando no valida.\n");
        break;
    case 1:
        //showLista(mi_lista);
        if(strcmp("mkdisk", tipo)==0){
            proceso_mkdisk(mi_lista);
        }else if(strcmp("rmdisk", tipo)==0){
            proceso_rmdisk(mi_lista);
        }else if(strcmp("fdisk", tipo)==0){
            proceso_fdisk(mi_lista);
        }else if(strcmp("mkfile", tipo)==0){
            proceso_mkfile(mi_lista);
        }else{
            printf("Error:\n");
            printf("Tipo desconocido, verifique si pertenece a uno de estos comandos:\n");
            printf("mkdisk, rmdisk, etc.\n");
        }
        break;
    }
    return;
}

char* concat(char* destino, char* letra){
    char* resultado = malloc(strlen(destino)+strlen(letra)+1);
    strcpy(resultado, destino);
    strcat(resultado, letra);
    return resultado;
}

char* limpiar(){
    char* d="";
    return d;
}

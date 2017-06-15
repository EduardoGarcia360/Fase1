#include "[MIA]Analizador_201212961.h"
#include <stdio.h>
#include <stdlib.h>

void menu_general();

int main()
{
    menu_general();
    return 0;
}

void menu_general(){
    char* entrada = malloc(200);
    do{

        printf("*Introduce linea de comando. (max. 200 caracteres):\n");
        printf("*Para cerrar la aplicacion escriba: salir\n");
        fgets(entrada, 200, stdin);
        if(strcasecmp(entrada, "salir\n")==0)
            break;

        analizador_general(entrada);
        //entrada=limpiar();
        char* entrada = malloc(200);
    }while(strcasecmp("salir\n", entrada) != 0);
    free(entrada);
}

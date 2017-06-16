#include "[MIA]Analizador_201212961.h"
#include "[MIA]ListaSE_201212961.h"
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
    ListaM* mi_lista = (ListaM*)malloc(sizeof(ListaM));
    inicializarM(mi_lista);
    do{

        printf("*Introduce linea de comando. (max. 200 caracteres):\n");
        printf("*Para cerrar la aplicacion escriba: salir\n");
        fgets(entrada, 200, stdin);
        if(strcasecmp(entrada, "salir\n")==0)
            break;
        analizador_general(entrada, mi_lista);

    }while(strcasecmp("salir\n", entrada) != 0);
    free(entrada);
}

#include "[MIA]ListaSE_201212961.h"
#include "[MIA]Analizador_201212961.h"
#include "[MIA]Estructuras_201212961.h"
#include <stdio.h>
#include <stdlib.h>

void menu_general();
int opciones();

int main()
{
    analizador_general();
    //menu_general();
    return 0;
}

void menu_general(){
    printf("======= Archivos =======\n\n");
    int opcion;
    do{
        //system("/usr/bin/clear");
	puts("**************************************************");
	puts("***          Ingrese una opcion:               ***");
	puts("**************************************************");
	puts("1) Ingresar linea de comando                   ***");
	puts("2) Abrir un archivo                            ***");
	puts("3) Salir                                       ***");
	puts("**************************************************");
	puts("Ingrese una opcion:");
	getchar();
	fflush(stdin);
	scanf("%[\n]d",&opcion);
        switch(opcion){
        case 1:
            analizador_general();
            break;
        case 2:
            printf("\n\npronto\n\n");
            break;
        default:
            printf("Saliendo...\n");
            break;
        }
    }while(opcion!=3);
    return EXIT_SUCCESS;
}

int opciones(){
	int opcion;
	system("/usr/bin/clear");
	puts("**************************************************");
	puts("***          Ingrese una opcion:               ***");
	puts("**************************************************");
	puts("1) Ingresar linea de comando                   ***");
	puts("2) Abrir un archivo                            ***");
	puts("3) Salir                                       ***");
	puts("**************************************************");
	puts("Ingrese una opcion:");
	scanf("%d",&opcion);
	return opcion;
}

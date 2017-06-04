#include "[MIA]ListaSE_201212961.h"
#include <stdlib.h>
#include <stdio.h>

int cima=0;

NodoL* crearNodo(int cat, char* com, char* sen){
    NodoL* nodo = (NodoL*)malloc(sizeof(NodoL));
    nodo->categoria=cat;
    nodo->comando=com;
    nodo->sentencia=sen;
    nodo->siguiente=NULL;
    return nodo;
}

void addFinal(Lista* lista, int categoria, char* comando, char* sentencia){
    NodoL* nuevo = crearNodo(categoria, comando, sentencia);
	if(cima == 1){
		NodoL* aux = lista->inicio;
		while(aux->siguiente != NULL){
			aux = aux->siguiente;
		}
		aux->siguiente = nuevo;
	}else{
		lista->inicio = nuevo;
		cima = 1;
	}
}

void showLista(Lista* lista){
    NodoL* actual = lista->inicio;
	int contador=0;
	int cat;
	char* com="";
	char* sen="";
	while(actual != NULL){
		cat = actual->categoria;
		com = actual->comando;
		sen = actual->sentencia;
		printf("nodo %d:\n", contador);
		printf("cate: %d - ", cat);
		printf("coman: %s - ", com);
		printf("senten: %s\n", sen);
		contador++;
		actual = actual->siguiente;
	}
}

#include "[MIA]ListaSE_201212961.h"
#include <stdlib.h>
#include <stdio.h>

int cima=0;//Analizar
int cimamM=0;//Mount

/*para Analizador*/
void inicializar(Lista* lista){
    lista->inicio=NULL;
}

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
	if(lista->inicio != NULL){
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

void limpiar_lista(Lista* lalista){
    if(lalista->inicio!=NULL){
        int cont=0;
        while(cont != 1){
            NodoL* aux = lalista->inicio;
            if(aux->siguiente == NULL){
                cont = 1;
                free(aux);
                cima=0;
            }else{
                lalista->inicio = aux->siguiente;
                free(aux);
            }
        }
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
/*fin metodos para la lista usada en Analizador*/

/*para Mount*/
void inicializarM(ListaM* lista){
    lista->inicio=NULL;
}

NodoM* crearMount(char* ruta, char* nombre, char* disco, char letra, int num, char* id){
    NodoM* nodo = (NodoM*)malloc(sizeof(NodoM));
    nodo->PATH=ruta;
    nodo->NAME_PART=nombre;
    nodo->DISK=disco;
    nodo->LETRA=letra;
    nodo->numero=num;
    nodo->ID=id;
    nodo->siguiente=NULL;
    return nodo;
}

void addDisco(ListaM* lalista, char* ruta, char* nombrepart, char* disco, char letra, int numero, char* id){
    NodoM* nuevo = crearMount(ruta, nombrepart, disco, letra, numero, id);
    if (lalista->inicio != NULL){
        NodoM* aux = lalista->inicio;
        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente=nuevo;
    }else{
        lalista->inicio=nuevo;
        cimamM=1;
    }
}

void limpiar_lista_mount(ListaM* lalista){
    if(lalista->inicio != NULL){
        int cont=0;
        while(cont != 1){
            NodoM* aux = lalista->inicio;
            if(aux->siguiente==NULL){
                cont=1;
                free(aux);
                cimamM=0;
            }else{
                lalista->inicio=aux->siguiente;
                free(aux);
            }
        }
    }
}

void showParticionesMontadas(ListaM* lalista){
    NodoM* actual = lalista->inicio;
    int contador=0;
    while(actual != NULL){
        printf("Disco #%d\n", contador);
        printf("Ruta: %s\n", actual->PATH);
        printf("Nombre Particion: %s\n", actual->NAME_PART);
        printf("Nombre Disco: %s\n", actual->DISK);
        printf("Letra: %c\n", actual->LETRA);
        printf("Numero: %d\n", actual->numero);
        printf("ID: %s\n", actual->ID);
        printf("============\n");
        contador++;
        actual=actual->siguiente;
    }
}

TMP* ultima_letra(ListaM* lalista, char* nombredisco, char letra){
    TMP* aux = (TMP*)malloc(sizeof(TMP));
    if(lalista->inicio == NULL){
        aux->LETRA='a';
        aux->NUMERO=1;
    }else{
        NodoM* actual = lalista->inicio;
        int encontrado = 0;
        while(actual != NULL){
            if(strcmp(nombredisco, actual->DISK)==0){
                /*
                -si ya existe un disco con el nombre ingresado se asignan
                la LETRA y NUMERO que corresponden al mismo disco.
                */
                printf("*************comparo nombres\n");
                aux->LETRA = actual->LETRA;
                aux->NUMERO = actual->numero;
                encontrado=1;
            }else if(actual->LETRA > letra && encontrado==0){
                /*
                actual letra tiene 'a' mayor o igual que letra 'a'
                comparo para encontrar una letra mayor a la 'a' que envio
                b > a asigno b en aux.
                */
                printf("*************comparo letras\n");

                letra = actual->LETRA;
                aux->LETRA = actual->LETRA;
                aux->NUMERO = 1;
            }else{
                printf("*************ultimo\n");
                letra = actual->LETRA;
                aux->LETRA = actual->LETRA;
                aux->NUMERO = actual->numero;
            }
            actual = actual->siguiente;
        }
    }
    return aux;
}














/////nada

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TDA Lista Enlazada--------------------------------------------------------------------------------
typedef struct nodoGen{
    int n_inicio;
    int n_final;
    struct nodoGen* siguiente;
}nodo;

typedef struct listaGen{
    nodo* l_inicio;
}TDAlista;

//Operadores---------------------------------------------------------------------------------------

// Dom :
// Rec : TDA Lista Enlazada
// Desc: Crea una lista enlazada vacia, preparada para agregar elementos.
TDAlista* crearListaVacia(){
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->l_inicio=NULL;
  return lista;
}

// Dom : TDA Lista Enlazada
// Rec : Int
// Desc: Revisa si la lista enlazada esta vacia, retornando 1 si es asi, 0 si no.
int esListaVacia(TDAlista* lista){
    if (lista->l_inicio == NULL){ return 1; }
    else{ return 0; }
}

// Dom : TDA Lista Enlazada, int, int
// Rec : 
// Desc: Agrega un nodo nuevo hacia el final de una lista enlazada.
//       Este nodo contiene a los dos valores int que se estan agregando.
void insertarNodo(TDAlista* lista, int inicio,int final){
    nodo* nuevo=(nodo*)malloc(sizeof(nodo));
    nuevo->n_inicio = inicio;
    nuevo->n_final = final;
    nuevo->siguiente = NULL;
    if ( esListaVacia(lista) == 1 ){
        lista->l_inicio = nuevo;
    }else{
        nodo* aux = lista->l_inicio;
        while (aux->siguiente != NULL){
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

// Dom : TDA Lista Enlazada
// Rec : 
// Desc: Remueve el primer nodo de la lista enlazada.
void eliminarInicio(TDAlista* lista){
  nodo* aux;
  if(!esListaVacia(lista)){
    aux = lista->l_inicio;
    lista->l_inicio = lista->l_inicio->siguiente;
    free(aux);
  }
}

// Dom : TDA Lista Enlazada
// Rec : 
// Desc: Remueve todos los nodos de la lista enlazada, empezando por el primero.
void liberarLista(TDAlista* lista){
  while (esListaVacia(lista) == 0){
    eliminarInicio(lista);
  }
}

// Dom : nodo, int
// Rec :
// Desc: Muestra en la consola los contenidos de un nodo.
//       El int es para mostrar el valor contenido en el nodo de dos formas:
//       - (0) Muestra el dato directamente.
//       - (n) Muestra el dato como se debe interpretar.
void printNodo(nodo* nodoLista, int modo){
  if (nodoLista == NULL){
    printf("Nodo no existe.\n");
  }else{
    int ini = nodoLista->n_inicio;
    int fin = nodoLista->n_final;
    if (modo == 0){
      printf("Inicio: %d\n",ini);
      printf("Final : %d\n\n",fin);
    }else{
      printf("Inicio - Dia: %d | Hora: %d\n",ini/100,ini%100);
      printf("Final  - Dia: %d | Hora: %d\n\n",fin/100,fin%100);
    }
  }
}

// Dom : TDA Lista Enlazada, int
// Rec : 
// Desc: Exactamente lo mismo que printNodo, pero es para toda la lista enlazada.
void printLista(TDAlista* lista, int modo){
  if (!esListaVacia(lista)){
    nodo* aux=lista->l_inicio;
    int i=1,ini,fin;
    while (aux != NULL){
      printf("Nodo %d\n",i);
      printNodo(aux,modo);
      i++;
      aux = aux->siguiente;
    }
  }
  else
    printf("La lista esta vacia\n");
}

// Dom : TDA Lista Enlazada
// Rec : int
// Desc: Devuelve la cantidad de nodos que existen en la lista enlazada actualmente
int cantidadLista(TDAlista* lista){
  int i=0;
  nodo* aux = lista->l_inicio;
  while (aux != NULL){
    i++;
    aux=aux->siguiente;
  }
  return i;
}

// Dom : TDA Lista Enlazada, int
// Rec : NULL | nodo
// Desc: Devuelve un nodo de la lista dependiendo de la posicion de este.
//       NOTA: La cantidad de nodos empieza desde el 1 con esta funcion.
//       Asi que si el valor esta fuera de rango, retornara NULL.
nodo* obtenerNodo(TDAlista* lista, int pos){
  if ((pos > cantidadLista(lista)) || (pos < 1) ){
    return NULL;
  }else{
    int i;
    nodo* aux = lista->l_inicio;
    for (i = 0; i < pos-1; i++){
      aux = aux->siguiente;
    }
    return aux;
  }
}
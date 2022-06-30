#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TDA Lista Enlazada--------------------------------------------------------------------------------

typedef struct nodoGenerico{
   int tiempoI;
   int tiempoF;
   struct nodoGenerico* siguiente;
}nodo;

typedef struct listaGen{
    nodo* inicio;
}TDAlista;

//Operadores---------------------------------------------------------------------------------------

// Dom :
// Rec : TDA Lista Enlazada
// Desc: Crea una lista enlazada vacia, preparada para agregar elementos.
TDAlista* crearListaVacia(){
  TDAlista* lista=(TDAlista*)malloc(sizeof(TDAlista));
  lista->inicio=NULL;
  return lista;
}

// Dom : Int x Int
// Rec : TDA Nodo
// Desc: Crea un nodo vacio para agregar a una lista.
nodo* crearNodo(int tiempoI, int tiempoF){
  nodo* nodoNuevo = (nodo*)malloc(sizeof(nodo));
  nodoNuevo->tiempoI = tiempoI;
  nodoNuevo->tiempoF = tiempoF;
  nodoNuevo->siguiente = NULL;
  return nodoNuevo;
}

// Dom : TDA Lista Enlazada
// Rec : Int
// Desc: Revisa si la lista enlazada esta vacia, retornando 1 si es asi, 0 si no.
int esListaVacia(TDAlista* lista){
    if (lista->inicio == NULL){ return 1; }
    else{ return 0; }
}

// Dom: TDA Lista Enlazada, TDA Nodo
// Rec:
// Desc: Agrega un nodo nuevo hacia el final de una lista.
void insertarNodoFinal(TDAlista* lista, nodo* newNodo){
  if (esListaVacia(lista)){
    lista->inicio = newNodo;
  }else{
    nodo* aux = lista->inicio;
    while (aux->siguiente != NULL){
      aux = aux->siguiente;
    }
    aux->siguiente = newNodo;
  }
}

// Dom: TDA Lista Enlazada, TDA Nodo
// Rec:
// Desc: Agrega un nodo nuevo hacia el final de una lista.
void insertarNodoInicio(TDAlista* lista, nodo* newNodo){
  nodo* aux = lista->inicio;
  newNodo->siguiente = aux;
  lista->inicio = newNodo;
}

// Dom : TDA Lista Enlazada
// Rec : 
// Desc: Remueve el primer nodo de la lista enlazada.
void eliminarInicio(TDAlista* lista){
  nodo* aux;
  if(!esListaVacia(lista)){
    aux = lista->inicio;
    lista->inicio = lista->inicio->siguiente;
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

// Dom : nodo
// Rec :
// Desc: Muestra en la consola los contenidos de un nodo.
void printNodo(nodo* nodoLista){
  if (nodoLista == NULL){
    printf("Nodo no existe.\n");
  }else{
    printf("Datos: %d - %d",nodoLista->tiempoI,nodoLista->tiempoF);
    if (nodoLista->siguiente == NULL){
      printf(", Este es el ultimo valor.\n");
    }else{
      printf(".\n");
    }
  }
}

// Dom : TDA Lista Enlazada
// Rec : 
// Desc: Exactamente lo mismo que printNodo, pero es para toda la lista enlazada.
void printLista(TDAlista* lista){
  if (!esListaVacia(lista)){
    nodo* aux=lista->inicio;
    int i=1;
    while (aux != NULL){
      printf("Nodo %d: ",i);
      printNodo(aux);
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
  nodo* aux = lista->inicio;
  while (aux != NULL){
    i++;
    aux=aux->siguiente;
  }
  return i;
}

// Dom: TDA Lista Enlazada, value
// Rec:
// Desc: Remueve el nth nodo de la lista enlazada.
void eliminarNth(TDAlista* lista,int value){
  if (esListaVacia(lista) || value > cantidadLista(lista) || value <= 0){
    //No hacer nada si value esta fuera de rango.
  }else if (value == 1){
    nodo* aux = lista->inicio;
    lista->inicio = aux->siguiente;
    free(aux);
  }else{
    int i;
    nodo* aux = lista->inicio;
    nodo* auxDel = lista->inicio;

    for (i = 2; i < value; i++){
      aux = aux->siguiente;
    }
    auxDel = aux->siguiente;
    aux->siguiente = auxDel->siguiente;
    free(auxDel);
  }
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
    nodo* aux = lista->inicio;
    for (i = 0; i < pos-1; i++){
      aux = aux->siguiente;
    }
    return aux;
  }
}

// Dom : TDA Lista Enlazada
// Rec : nodo | NULL
// Desc: Devuelve el ultimo elemento de alguna lista, si es que hay elementos.
//       Si no hay elementos, retorna NULL
nodo* obtenerUltimoElemento(TDAlista* lista){
  if (!esListaVacia(lista)){
    nodo* aux = lista->inicio;
    while (aux->siguiente != NULL){
      aux = aux->siguiente;
    }
    return aux;
  }else{
    return NULL;
  }
}
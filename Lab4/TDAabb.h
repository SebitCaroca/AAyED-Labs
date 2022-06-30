#include <stdio.h>
#include <stdlib.h>

/*--------------- estructura de datos -----------------*/

typedef struct nodoABB{
  int tiempoI;
  int tiempoF;
  struct nodoABB* padre;
  struct nodoABB* hijoIzquierdo;
  struct nodoABB* hijoDerecho;
}nodoABB;

typedef struct {
  nodoABB* inicio;
}TDAabb;

/*--------------- operaciones de creación -----------------*/

TDAabb* crearABBVacio(){
  TDAabb* abb=(TDAabb*)malloc(sizeof(TDAabb));
  abb->inicio=NULL;
  return abb;
}

int esABBvacio(TDAabb* abb){
  if (abb->inicio == NULL)
    return 1;
  else
    return 0;
}

/*--------------- operaciones de posicion -----------------*/

//devuelve NULO si el árbol está vacío
nodoABB* raizABB(TDAabb* arbol){
  if (arbol!=NULL)
    return arbol->inicio;
  return NULL;
}

nodoABB* padreNodoABB(TDAabb* arbol, nodoABB* nodo){
  if (nodo!=NULL)
    return nodo->padre;
}

int esHojaABB(TDAabb* arbol, nodoABB* nodo){
  if (!esABBvacio(arbol)){
    if ((nodo->hijoIzquierdo==NULL)&&(nodo->hijoDerecho==NULL))
      return 1;
  }
  return 0;
}

/*--------------- operaciones de recorrido -----------------*/

void recorridoInordenArbolBinarioBusqueda(nodoABB* nodo){
  if (nodo!=NULL){
    //hijo izquierdo
    recorridoInordenArbolBinarioBusqueda(nodo->hijoIzquierdo);
    // raiz
    printf("%d %d\n",nodo->tiempoI,nodo->tiempoF);
    // hijo derecho
    recorridoInordenArbolBinarioBusqueda(nodo->hijoDerecho);
  }
}

void recorridoInordenABB(TDAabb* arbol){
  if (!esABBvacio(arbol)){
    printf("INORDEN ABB: \n");
    recorridoInordenArbolBinarioBusqueda(arbol->inicio);
    printf("\n");
  }else{
    printf("El árbol binario está vacío\n");
  }
}

/*--------------- operaciones auxiliares -----------------*/

nodoABB* buscarMenorABB(TDAabb* arbol, nodoABB* nodo){
  nodoABB* aux;
  if (!esABBvacio(arbol)){
    aux=nodo;
    while (aux!=NULL){
      if (aux->hijoIzquierdo != NULL){
        aux=aux->hijoIzquierdo;
      }else{ //es el aux es nodo que contiene dato
        return aux;
      }
    }
  }
  return NULL;
}

/*--------------- operaciones de actualización -----------------*/

void insertarRaizABB(TDAabb* arbol, int tiempoI, int tiempoF)
{
  nodoABB* raiz=(nodoABB*)malloc(sizeof(nodoABB));
  raiz->tiempoI = tiempoI;
  raiz->tiempoF = tiempoF;
  raiz->hijoIzquierdo=NULL;
  raiz->hijoDerecho=NULL;
  raiz->padre=NULL;
  arbol->inicio=raiz;
}

void insertarNodoRecursivoABB(nodoABB* nodo, int tiempoI, int tiempoF){
  nodoABB* nuevo;
  nuevo=(nodoABB*)malloc(sizeof(nodoABB));
  nuevo->tiempoI = tiempoI;
  nuevo->tiempoF = tiempoF;
  nuevo->hijoIzquierdo=NULL;
  nuevo->hijoDerecho=NULL;

  //Se toma preferencia al tiempo inicial para simular un ordenamiento de datos
  //No se modifican los datos iniciales en la lista enlazada, se modifican en el arbol al ingresar
  if (tiempoI <= nodo->tiempoI){
    //Bifurcacion - Lado Izquierdo
    if (nodo->hijoIzquierdo==NULL){
      // No hay un hijo a la izquierda
      nodo->hijoIzquierdo=nuevo;
      nuevo->padre=nodo;
    }else{
      // Si ya hay un hijo a la izquierda
      insertarNodoRecursivoABB(nodo->hijoIzquierdo,tiempoI,tiempoF);
    }
  }else{ 
    //Bifurcacion - Lado Derecho
    if (nodo->hijoDerecho==NULL){
      // No hay un hijo a la izquierda
      nodo->hijoDerecho=nuevo;
      nuevo->padre=nodo;
    }else{
      // Si ya hay un hijo a la izquierda
      insertarNodoRecursivoABB(nodo->hijoDerecho,tiempoI,tiempoF);
    }
  }
}

void insertarNodoABB(TDAabb* arbol, int tiempoI, int tiempoF)
{
  if (!esABBvacio(arbol))
  {
    insertarNodoRecursivoABB(arbol->inicio,tiempoI,tiempoF);
  }
  else
    insertarRaizABB(arbol,tiempoI,tiempoF);
}
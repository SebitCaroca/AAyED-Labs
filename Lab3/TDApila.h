#include <stdio.h>
#include <stdlib.h>

/*------------- estructura de datos -------------*/



typedef struct{
  int capacidad;
  int size;
  nodo* tope;
}TDApila;

/*------------- operaciones -------------*/

TDApila* crearPilaVacia(int capacidad){
  TDApila* pila=(TDApila*)malloc(sizeof(TDApila));
  pila->capacidad=capacidad;
  pila->size=0;
  pila->tope=NULL;
  return pila;
}

int esPilaVacia(TDApila* pila){
  if (pila->size == 0)
    return 1;
  else
    return 0;
}

void apilar(TDApila* pila, int datoNuevo){
  if (pila->capacidad > pila->size){
    pila->size = pila->size + 1;
    nodo* nodoNuevo = (nodo*)malloc(sizeof(nodo));
    nodoNuevo->dato = datoNuevo;
    nodoNuevo->siguiente = pila->tope;
    pila->tope = nodoNuevo;
  }
}

void desapilar(TDApila* pila){
  if (esPilaVacia(pila) == 0){ //Hay elementos, se puede desapilar.
    nodo* ptrAux = pila->tope;
    pila->tope = ptrAux->siguiente;
    free(ptrAux);
    pila->size = pila->size - 1;
  }
  else{ //No hay elementos, no se puede desapilar nada, y no hace nada.
    /* code */
  }
}

nodo* tope(TDApila* pila){
  if (esPilaVacia(pila) == 0){
    nodo* newNodo = crearNodoVacio();
    newNodo->dato = pila->tope->dato;
    newNodo->siguiente = pila->tope->siguiente;
    return(newNodo);
  }else{
    return NULL;
  }
}

/*------------- Actividad 4 -------------*/
//No usar el metodo de la lista enlazada.
//Obligatoriamente pasar de una lista a otra.
int buscarDatoPila(TDApila* pila, int datoBuscar){
  if (esPilaVacia(pila) == 0){
    TDApila* pilaAux = crearPilaVacia(pila->size);
    nodo* nodoAux = tope(pila);
    int isFound=0;

    while ( (esPilaVacia(pila) == 0) && (nodoAux->dato != datoBuscar) ){
      apilar(pilaAux,nodoAux->dato);
      desapilar(pila);
      nodoAux = tope(pila);
    }

    if (esPilaVacia(pila) == 0){
      isFound = 1;
    }
    
    nodoAux = tope(pilaAux);

    while (esPilaVacia(pilaAux) == 0){
      apilar(pila,nodoAux->dato);
      desapilar(pilaAux);
      nodoAux = tope(pilaAux);
    }

    free(pilaAux);

    return isFound;
    
  }else{
    return (-1); // La lista esta vacia, no se puede encontrar nada.
  }
}

/*Opcional, quiero ver que tengo en la pila.*/
void printPila(TDApila* pila){
  nodo* aux = tope(pila);
  printf("Espacio usado de pila: %d de %d\n",pila->size,pila->capacidad);
  if (esPilaVacia(pila) == 0){
    while (aux != NULL){
      printf("%d ",aux->dato);
      aux=aux->siguiente;
    }
  }
  printf("\n\n");
}

void vaciarPila(TDApila* pila){
  while (pila->size > 0){
    desapilar(pila);
  }
}



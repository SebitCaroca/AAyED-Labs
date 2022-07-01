#include <stdio.h>
#include <stdlib.h>
#include "TDAlista.h"
#include "TDAabb.h"
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define isOverlap(x1,x2,y1,y2) (((x1 <= y2) && (y1 <= x2)) ? 1 : 0 )


/*Esta funcion consiste en la lectura del archivo de entrada
  Lo adapta a una lista enlazada como entrada.*/
TDAlista* cargarListaDeArchivo(FILE* archivo){
  TDAlista* lista = crearListaVacia();
  int tiempoI,tiempoF;
  while (fscanf(archivo,"%d %d",&tiempoI,&tiempoF) != EOF){
    nodo* tempNodo = crearNodo(tiempoI,tiempoF);
    insertarNodoFinal(lista,tempNodo);
  }
  return lista;
}

/*Esta funcion obtiene cada dato de una lista enlazada, y la agrega a un ABB
  De esta forma, los datos estaran ordenados
  No de la manera mas ideal, pero lo suficiente*/
TDAabb* lista2ABB(TDAlista* lista){
  TDAabb* arbol = crearABBVacio();
  nodo* aux = lista->inicio;
  while (aux != NULL){
    insertarNodoABB(arbol,aux->tiempoI,aux->tiempoF);
    aux = aux->siguiente;
  }
  return arbol;
}

void ABB2listaRecursivo(nodoABB* nodoArbol, TDAlista* listaNueva, nodo* ultimoElemento){
  //Se usara exploracion INORDEN, asi obtengo datos ordenados...
  if (nodoArbol != NULL){
    ABB2listaRecursivo(nodoArbol->hijoIzquierdo,listaNueva,ultimoElemento);
    //--------------------------------------------------------------------------------------PROCESO
    // Caso inicial, cuando la lista esta vacia.
    if (ultimoElemento == NULL){
      nodo* nuevoNodo = crearNodo(nodoArbol->tiempoI,nodoArbol->tiempoF); 
      insertarNodoInicio(listaNueva,nuevoNodo);
      ultimoElemento = listaNueva->inicio;
    }
    //Para el resto de elementos en la lista
    else{ 
      if (isOverlap(nodoArbol->tiempoI,nodoArbol->tiempoF,ultimoElemento->tiempoI,ultimoElemento->tiempoF)){
        // Hay sobreposicion, unir datos del arbol con el ultimo de la lista.
        ultimoElemento->tiempoI = min(nodoArbol->tiempoI,ultimoElemento->tiempoI);
        ultimoElemento->tiempoF = max(nodoArbol->tiempoF,ultimoElemento->tiempoF);
      }else{
        // No hay sobreposicion, crear un nodo nuevo, y cambiar el ultimo elemento a este.
        nodo* nuevoNodo = crearNodo(nodoArbol->tiempoI,nodoArbol->tiempoF);
        insertarNodoSiguiente(ultimoElemento,nuevoNodo);
        ultimoElemento = ultimoElemento->siguiente;
      }
    }
    //--------------------------------------------------------------------------------------PROCESO
    ABB2listaRecursivo(nodoArbol->hijoDerecho,listaNueva,ultimoElemento);
  }
}

TDAlista* ABB2listaMix(TDAabb* arbol){
  if (!esABBvacio(arbol)){
    TDAlista* lista = crearListaVacia();
    ABB2listaRecursivo(arbol->inicio,lista,NULL);
    return lista;
  }
}

void lista2Archivo(TDAlista* lista, char* nombreArchivo){
  FILE* out = fopen(nombreArchivo,"w");
  nodo* aux = lista->inicio;
  while (aux != NULL){
    fprintf(out,"%d %d\n",(aux->tiempoI),(aux->tiempoF));
    aux = aux->siguiente;
  }
  fclose(out);
}

int main(int argc,char *argv[]){
  if (argc < 2){
    printf("Faltan parametros.\n");
    return -1;
  }
  FILE* archivo = fopen(argv[1],"r");
  TDAlista* lista = cargarListaDeArchivo(archivo);
  fclose(archivo);

  TDAabb* arbol = lista2ABB(lista);
  liberarLista(lista);
  free(lista);

  recorridoInordenABB(arbol);
  TDAlista* nuevaLista = ABB2listaMix(arbol);
  printf("-\n");
  printLista(nuevaLista);
  lista2Archivo(nuevaLista,argv[2]);
  printf("-\n");
  liberarLista(nuevaLista);
  free(nuevaLista);
  return 0;
}
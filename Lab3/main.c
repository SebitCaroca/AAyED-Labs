#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAlista.h"
#include "TDApila.h"
#include "TDAgrafo-edit.h"

int extraerMinimo(int* d_longitud,int* d_visitado,int cvertices){
	int minimo = INT_MAX;
	int indiceMinimo = -1;
	int i;
	for (i = 0; i < cvertices; ++i){
		//Obtener la minima distancia que no haya sido visto aun.
		if (d_visitado[i] == 0){
			if ( (d_longitud[i] < minimo) && (d_longitud[i] != 0) ){
				minimo = d_longitud[i];
				indiceMinimo = i;
			}
		}
	}
	
	return indiceMinimo + 1;
}

//I: Array, Int
//O: Bool (Int)
//Revisa si existe un 0 en el arreglo.
//Si es asi, retorna 1, sino 0.
int quedanSinVisitar(int* d_visitado, int limite){
  for (int i = 0; i < limite ; i++){
    if (d_visitado[i] == 0){ return 1; }
  }
  return 0;
}

/*
La idea que tengo actualmente es la siguiente...
Definamos X como nodos que NO pertenecen a las estaciones de bomberos
--(Implica que Xi es un nodo que pertenece a X)
Definamos Y como nodos que pertenecen a las estaciones de bomberos
--(Implica que Yi es un nodo que pertenece a Y)

Procedimiento:
--Repetir lo siguiente hasta que todos los nodos de X hayan sido visitados:
----Obtener la distancia mas corta entre Xi y un nodo de Y (Dijkstra sera util)
----Si hay multiples nodos de Y
------Probar con todos los Yi
------Obtener el mas corto
----Despues de probar con todos los nodos
----Escribir en cuartel.out el nodo cuyo valor es el mas alto del arreglo
*/
void dijkstra(TDAgrafo* grafo,int vertice){
	//Inicializacion.
	int* d_anterior = (int*)calloc(sizeof(int),grafo->cvertices);
	int* d_visitado = (int*)calloc(sizeof(int),grafo->cvertices);
	int* d_longitud = (int*)calloc(sizeof(int),grafo->cvertices);
	int u;
  	int s = vertice-1;
	TDAlista* listaAdy;
	nodo* aux;
	int w,i;

	//Algoritmo.
	for (w = 0; w < grafo->cvertices ; w++){
		d_anterior[w] = -1; //NULL
		d_visitado[w] = 0;  //FALSO
		if ( grafo->adyacencias[s][w] > 0 ){
			d_longitud[w] = grafo->adyacencias[s][w];
			d_anterior[w] = s;
		}else{
			d_longitud[w] = INT_MAX; //INFINITO
		}
	}
  
	d_longitud[s] = 0;
	d_visitado[s] = 1; //VERDADERO
	while( quedanSinVisitar(d_visitado , grafo->cvertices) ){
		u = extraerMinimo(d_longitud , d_visitado , grafo->cvertices);
		d_visitado[u] = 1;
		listaAdy = obtenerAdyacentes(grafo,u);
		aux = listaAdy->inicio;
		while(aux != NULL){
			if (d_longitud[aux->dato] > d_longitud[u] + grafo->adyacencias[u][aux->dato] ){
				d_longitud[aux->dato] = d_longitud[u] + grafo->adyacencias[u][aux->dato];
				d_anterior[aux->dato] = u;
			}
			aux=aux->siguiente;
		}
	}

  for (i = 0; i < grafo->cvertices ; i++){
    printf("%d %d %d\n",d_anterior[i],d_visitado[i],d_longitud[i]);
  }
}

      
int main(void) {
  FILE* archivo = fopen("pueblo1.in","r");
  TDAgrafo* grafo = leerGrafoNoDirigidoPonderado(archivo);
  imprimirMatrizAdyacencia(grafo);
  fclose(archivo);
  dijkstra(grafo,5);
  printf("Fin.\n");
  return 0;
}
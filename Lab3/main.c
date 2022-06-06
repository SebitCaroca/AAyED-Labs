#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDAlista.h"
#include "TDApila.h"
#include "TDAgrafo-edit.h"

int valorMinimoArreglo(int* arr, int limit){
	int minimo = INT_MAX;
	int minIndex = 0;
	for (size_t i = 0; i < limit; i++){
		if (arr[i] <= minimo){
			minimo = arr[i];
			minIndex = i;
		}
	}
	return minIndex;
}

int valorMaximoArreglo(int* arr, int limit){
	int maximo = 0;
	int maxIndex = 0;
	for (size_t i = 0; i < limit; i++){
		if (arr[i] >= maximo){
			maximo = arr[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

int extraerMinimo(int* d_longitud,int* d_visitado,int cvertices){
	int minimo = INT_MAX;
	int indiceMinimo = 0;
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
	return indiceMinimo;
}

//I: Array, Int
//O: Bool (Int)
//Revisa si existe un 0 en el arreglo.
//Si es asi, retorna 1, sino 0.
int quedanSinVisitar(int* d_visitado, int limite){
  for (int i = 0; i < limite ; i++){
    if (d_visitado[i] != 1){ return 1; }
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
int* dijkstra(TDAgrafo* grafo,int vertice){
	//Inicializacion.
	int* d_anterior = (int*)calloc(grafo->cvertices,sizeof(int));//padre
	int* d_visitado = (int*)calloc(grafo->cvertices,sizeof(int));//visto
	int* d_longitud = (int*)calloc(grafo->cvertices,sizeof(int));//distancia
	int u;
  int s = vertice;
	TDAlista* listaAdy;
	nodo* aux;
	int w,i;

	//Algoritmo.
	for (w = 0 ; w < grafo->cvertices ; w++){
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
		liberarLista(listaAdy);
		free(listaAdy);
	}
	free(d_anterior);
	free(d_visitado);
	return d_longitud;
}

/*
Procedimiento:
--Repetir lo siguiente hasta que todos los nodos de X hayan sido visitados:
----Obtener la distancia mas corta entre Xi y un nodo de Y (Dijkstra sera util)
----Si hay multiples nodos de Y
------Probar con todos los Yi
------Obtener el mas corto
----Despues de probar con todos los nodos
----Escribir en cuartel.out el nodo cuyo valor es el mas alto del arreglo
*/

int lugarIdeal(TDAgrafo* G){
	int* distancia;
	int distCortaEsp[G->espLimit];
	int distLargaEsp[G->cvertices];
	for (size_t i = 0; i < G->cvertices; i++){
		distancia = dijkstra(G,i);
		for (size_t j = 0; j < G->espLimit; j++){
			distCortaEsp[j] = distancia[G->especial[j]];
		}
		distLargaEsp[i] = valorMinimoArreglo(distCortaEsp,G->espLimit);
	}
	return (valorMaximoArreglo(distLargaEsp,G->cvertices));
}

int main(void) {
  FILE* archivo = fopen("pueblo1.in","r");
  TDAgrafo* grafo = leerGrafoNoDirigidoPonderado(archivo);
  imprimirMatrizAdyacencia(grafo);
  fclose(archivo);
	FILE* output = fopen("cuartel1.out","w");
	fprintf(output,"%d",lugarIdeal(grafo));
	printf("Fin\n");
  return 0;
}
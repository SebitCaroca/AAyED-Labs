#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define INT_MAX 2147483647

/*------------- estructura de datos -------------*/

typedef struct matrizGrafo{
	int cvertices;
	int espLimit;
	int* especial;
	int** adyacencias;
}TDAgrafo;

/*----------------- operaciones -----------------*/

TDAgrafo* crearGrafoVacio(int vertices,int tamEspecial) {
	TDAgrafo* grafo = (TDAgrafo*)calloc(1,sizeof(TDAgrafo));
	grafo->cvertices = vertices;
	grafo->espLimit = tamEspecial;
	grafo->especial = (int*)calloc(tamEspecial,sizeof(int));
	grafo->adyacencias = (int**)calloc(vertices,sizeof(int*));
  
	for (int i = 0; i < vertices ; i++) {
		grafo->adyacencias[i] = (int*)calloc(vertices,sizeof(int));
		for (int j = 0 ; j < vertices ; j++) {
			grafo->adyacencias[i][j] = 0;
		}	
	}
	return grafo;
}

void imprimirMatrizAdyacencia(TDAgrafo* grafo){
  printf("Matriz de adyacencia: \n");
	int i, j;
	for (i = 0; i < grafo->cvertices; i++) {
		for (j = 0; j < grafo->cvertices; j++) {
			printf("%-3d ", grafo->adyacencias[i][j]);
		}
		printf("\n");
	}
  printf("Estaciones de Bomberos: \n");
  for(i=0;i<grafo->espLimit;i++){
    printf("%d ",grafo->especial[i]);
  }
  printf("\n----------\n");
}

int adyacenciaNodos(TDAgrafo * grafo, int vertA, int vertB) {
	if (grafo->adyacencias[vertA - 1][vertB - 1] == 1) { return 1; }
	return 0;
}

int obtenerCantNodos(FILE* archivo){
  rewind(archivo);
  int a,b,c;
  int x,y,w;
  int largestValue=0;
  fscanf(archivo,"%d %d",&a,&b);
  while (a != 0){
    fscanf(archivo,"%d",&c);
    a--;
  }
  while (b!=0){
    fscanf(archivo,"%d %d %d",&x,&y,&w);
    if (x>largestValue || y>largestValue){
      largestValue = MAX(x,y);
    }
    b--;
  }
  rewind(archivo);
  return largestValue;
}

//NoDirigido Ponderado
TDAgrafo* leerGrafoNoDirigidoPonderado(FILE* pf){
	int n_vertices, m_aristas, estaciones;
	int nodo_x,nodo_y,nodo_w;
  int garbage;
  
	if (pf == NULL){
		printf("Error de archivo.\n");
		return NULL;
	}else{
		//Cantidad de nodos y aristas
    //No se nos entrega una cantidad de nodos, solo de aristas.
    //Hice una funcion que me ayudara con eso.
    n_vertices = obtenerCantNodos(pf);
		fscanf(pf,"%d %d", &estaciones , &m_aristas); 		
    //Ahora a crear el grafo para poder usarlo.
		TDAgrafo* G = crearGrafoVacio(n_vertices,	estaciones);
    //Debido a la estructura del archivo, necesitamos mover el lector
    //al lugar apropiado
    for (int i = 0; i < estaciones; i++){ fscanf(pf,"%d",&G->especial[i]); }
    //Ahora a cargar los datos en la matriz de forma apropiada
		for (int j = 0 ; j < m_aristas ; j++){
			fscanf(pf,"%d %d %d",&nodo_x, &nodo_y,&nodo_w);
			G->adyacencias[nodo_x-1][nodo_y-1] = nodo_w;
			G->adyacencias[nodo_y-1][nodo_x-1] = nodo_w;
		}
		rewind(pf);
		return G;	
	}
}

//Actividad 1
/*
Entrada: Grafo x int
Salida: Lista Enlazada de los vertices adyacentes
Descripcion: Entrega una lista enlazada de los vertices adyacentes al usuario.
Nota: int vertice usa variables entre 1 y grafo->cvertices, inclusivo.*/
TDAlista* obtenerAdyacentes(TDAgrafo* grafo, int vertice){
	TDAlista* adyacente = crearListaVacia();
	nodo* tempNodo;
	for (int i = 0; i < grafo->cvertices; ++i) {
		if (grafo->adyacencias[vertice-1][i] == 1){
			tempNodo = crearNodoVacio();
			tempNodo->dato = (i+1);
			insertarNodoInicio(adyacente,tempNodo);
		}
	}
  return adyacente;
}

//Actividad 2
/*Entrada: Grafo x Lista Enlazada
  Salida: Int
  Descripcion: Revisa si una secuencia cualquiera es posible hacer en un determinado grafo.
  			   Entrega 1 si es posible, entrega 0 si no lo es.*/
int esCamino( TDAgrafo* grafo, TDAlista* secuencia ){
	if (esListaVacia(secuencia)){
		return -1;
	}
	nodo* aux = secuencia->inicio;
	while (aux->siguiente != NULL){
		if ( adyacenciaNodos( grafo,aux->dato,aux->siguiente->dato ) == 0) {
			return (0);
		}
		aux = aux->siguiente;
	}
	return (1);
}

//Actividad 3
int esCiclo( TDAgrafo* grafo, TDAlista* secuencia){
	if (esCamino(grafo,secuencia) == 1){
		nodo* inicioSec = secuencia->inicio;
		nodo* aux = secuencia->inicio;
		while (aux->siguiente != NULL){
			aux = aux->siguiente;
		}
		if (inicioSec->dato == aux->dato){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

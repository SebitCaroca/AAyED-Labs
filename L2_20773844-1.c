#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "L2_TDALista-Editada.h"

// Dom : int, int, int
// Rec : int
// Desc: Revisa si un numero esta dentro de un rango.
//       (1) El numero esta dentro del rango.
//       (0) El numero no esta dentro del rango
int revisarRango(int num,int bottom, int top){
    if ((num <= top) && (num >= bottom)){
        return 1;
    } else {
        return 0;
    }
}

// Dom : int, int
// Rec : int
// Desc: Revisa que los horarios de un nodo esten estructurados de forma correcta.
//       Esto es, que no haya un horario de un dia a otro, y que los numeros esten en rango.
int revisarHorario(int horario1, int horario2){
    int dia1 = horario1/100;
    int dia2 = horario2/100;
    int hora1 = horario1%100;
    int hora2 = horario2%100;
    //Dias: [1,5]
    //Horas: [8,22]
    //Ademas de revisar que esten dentro de rango, los dias deben ser los mismos.
    if ( ( revisarRango(dia1,1,5) ) && ( revisarRango(dia2,1,5) ) && ( revisarRango(hora1,8,22) ) && ( revisarRango(hora2,8,22) ) && (dia1 == dia2) ){
        return 1;
    }else{
        return 0;
    }
}

// Dom : Archivo entrada
// Rec : TDA Lista
// Desc: Adapta el archivo de entrada hacia un formato de lista enlazada.
TDAlista* armarInicio(FILE* entrada){
    TDAlista* lista = crearListaVacia();
    char fileBuffer[9];
    char* ptr;
    int temp_I,temp_F;
    while (fgets(fileBuffer,sizeof(fileBuffer),entrada) != NULL){
        ptr = strtok(fileBuffer," ");
        temp_I = (int) strtol(ptr,NULL,10);
        ptr = strtok(NULL," ");
        temp_F = (int) strtol(ptr,NULL,10);
        if ( revisarHorario(temp_I,temp_F) ){
            insertarNodo(lista,temp_I,temp_F);
        }
    }
    return lista;
}

// Dom : nodo, nodo
// Rec : int
// Desc: Revisa si dos nodos determinados tienen rangos que se sobreponen.
//       (1) Hay sobreposicion.
//       (0) No hay sobreposicion.
int rangoEnRango(nodo* nodo1, nodo* nodo2){
    if ( (nodo1->n_inicio <= nodo2->n_final) && (nodo1->n_final >= nodo2->n_inicio) ){
        return 1;
    }else{
        return 0;
    }
}

// Doc : TDA Lista Enlazada, int
// Rec : TDA Lista Enlazada
// Desc: Creo un horario que contenga solo un dia, dependiendo del valor dia.
TDAlista* filtroHorarios(TDAlista* listaMaestra, int dia){
    TDAlista* lista = crearListaVacia();
    nodo* aux = listaMaestra->l_inicio;
    while (aux != NULL){
        if ( (aux->n_inicio)/100 == dia ){
            insertarNodo(lista,aux->n_inicio,aux->n_final);
        }
        aux = aux->siguiente;
    }
    return lista;
}

// Doc : TDA Nodo, TDA Nodo
// Rec : TDA Nodo
// Desc: Retorna un nodo que contiene los valores mas grandes y pequeños de los dos nodos.
//       Notar que su valor siguiente es NULL.
nodo* mezclarNodos(nodo* nodo1, nodo* nodo2){
    nodo* nodoMezcla = crearNodoVacio();
    //Revisar los mas pequeños
    if (nodo1->n_inicio =< nodo2->n_inicio){
        nodoMezcla->n_inicio = nodo1->n_inicio;
    }else if (nodo1->n_inicio > nodo2->n_inicio){
        nodoMezcla->n_inicio = nodo2->n_inicio;
    }
    
    //Revisar los mas grandes
    if (nodo1->n_final =< nodo2->n_final){
        nodoMezcla->n_final = nodo2->n_final;
    }else if (nodo1->n_final > nodo2->n_final){
        nodoMezcla->n_final = nodo1->n_final;
    }
    
    return nodoMezcla;
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

int main(int argc,char *argv[]){
    FILE *f_I = fopen(argv[1],"r");
    if (f_I==NULL){
        printf("Se necesita un archivo de entrada.\n");
        return 0;
    }
    FILE *f_O = fopen(argv[2],"w");
    if (f_O==NULL){
        printf("Se necesita un lugar donde guardar la salida.\n");
        return 0;
    }

    clock_t mergeStart,mergeEnd;
    mergeStart = clock();

    //---------------------------------------------------------------------------------------------

    //Obtener Horario original.
    TDAlista* listaMaestra = armarInicio(f_I);
    fclose(f_I);
    
    //Crear arreglo de horarios filtrados. 
    int i;
    TDAlista* horario[5];
    for (i = 0; i < 5; i++){
        horario[i] = filtroHorarios(listaMaestra,i+1);
    }

    liberarLista(listaMaestra);
    free(listaMaestra);

    for (i = 0; i < 5; i++){
        printf("Dia %d ---------------------\n",i+1);
        printLista(horario[i],1);
    }

    fclose(f_O);
    for (i = 0; i < 5; i++){
        liberarLista(horario[i]);
        free(horario[i]);
    }

    //---------------------------------------------------------------------------------------------

    mergeEnd = clock();
    printf("Tiempo demorado: %f\n",(double)(mergeEnd-mergeStart)/CLOCKS_PER_SEC);
    
    return 0;
}
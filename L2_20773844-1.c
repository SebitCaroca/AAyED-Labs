#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// Doc : TDA Lista Enlazada
// Rec : Array de TDA Lista Enlazada
// Desc: Una forma bastante ridicula de como separar los dias en sus propias listas.
TDAlista** separaHorarios(TDAlista* listaMaestra){
    int i;
    int dias = 5;
    TDAlista** horario = (TDAlista**)malloc( dias * sizeof(TDAlista*) );
    for (i = 0; i < dias; i++){
        horario[i] = crearListaVacia();
    }
    nodo* aux = listaMaestra->l_inicio;
    while (aux != NULL){
        i=aux->n_inicio; //Tras revisar n_inicio & n_final, ambos deberian tener el mismo dia.
        i=i/100;
        insertarNodo(horario[i],aux->n_inicio,aux->n_final);
        aux=aux->siguiente;
    }
    return horario;
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
    TDAlista* lista = armarInicio(f_I);
    fclose(f_I);
    /*CODIGO*/
    TDAlista** horario = separaHorarios(lista);
    printf("Lunes...\n");
    printLista(horario[0],1);
    printf("Martes...\n");
    printLista(horario[1],1);
    printf("Miercoles...\n");
    printLista(horario[2],1);
    printf("Jueves...\n");
    printLista(horario[3],1);
    printf("Viernes...\n");
    printLista(horario[4],1);
    printf("\nFin\n");
    /*CODIGO*/
    liberarLista(lista);
    free(lista);
    fclose(f_O);
    return 0;
}
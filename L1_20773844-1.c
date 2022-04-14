#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------

void printArr(int *arr,int arrSize){
    int i;
    printf("%d",arr[0]);
    for (i = 1; i < arrSize; i++)
    {
        printf(" - %d",arr[i]);
    }
    printf("\n");
}

//----------------------------------------------------------------------------------------------------

int isSorted(int *arr,int arrLen){
    int i;
    for (i = 0; i < (arrLen-1); i++){
        if (arr[i]>arr[i+1]) {
            return 0; //no está ordenado
        }
    }
    return 1; //si está ordenado
}

//----------------------------------------------------------------------------------------------------

int checkHighestValue(int *arr,int bottomLimit,int arrLen){ //Revisa cual es el valor mas alto de una lista dentro de un rango.
    int i,id=bottomLimit;

    //Me permite ver si es que se desborda la lista.
    if (bottomLimit >= arrLen) {
        return (-1);
    }
    else{
        for (i = bottomLimit; i < arrLen; i++) {
            if ( arr[i] > arr[id] ) {
                id = i;
            }
        }
        return id;
    }
}

//----------------------------------------------------------------------------------------------------

void flip(int *arr, int arrLen,int cutoff){
    int tempArr[arrLen-cutoff],i,j=0;
    for (i = cutoff; i < arrLen; i++){
        tempArr[j]=arr[i];
        j++;
    }
    j=(arrLen-cutoff)-1;
    for (i = cutoff; i < arrLen; i++){
        arr[i]=tempArr[j];
        j--;
    }
}

//----------------------------------------------------------------------------------------------------

void flipSort(int *arrayFile,int arrLen){
    int low=0,id;
    //FILE *out = fopen("salida.out","w");

    while (isSorted(arrayFile,arrLen) == 0){ //Mientras la lista no este ordenada, hacer giros.
        id=checkHighestValue(arrayFile,low,arrLen);
        printf("Estado actual... base: %d | id-num-mayor: %d\n",low,id);
        printArr(arrayFile,arrLen);
        printf("\n");

        if (id == -1){ //Con esto sabre que onda pasa aqui.
            printf("Error.\n");
            break;
        }
        else if (id == low){ //Significa que el numero mas grande esta al inicio del rango a ver, nada que hacer aqui.
            low++;
        }
        else if (id == (arrLen-1)){ //Significa que el numero mas grande está en la cima de la lista, hay que dar vuelta la lista.
            flip(arrayFile,arrLen,low);
        }
        else{ //Significa que hay que mover el numero mas grande hacia la cima para poder ponerla al final.
            flip(arrayFile,arrLen,id);
        }
        
    }
    //fclose(out);
}

//----------------------------------------------------------------------------------------------------

int main(){
    FILE *f_I = fopen("entrada.in","r");
    if (f_I==NULL){
        printf("Se necesita un archivo entrada.in \n");
        return 0;
    }

    //Obtener longitud del array, y formarlo
    char fileBuffer[80];
    char *ptr;
    int arrLen,i;

    fgets(fileBuffer,sizeof(fileBuffer),f_I);
    arrLen = atoi(fileBuffer);
    
    int arrayFile[arrLen],a_top=arrLen,a_bottom=0,id=0;
    
    //Obtener valores del array
    fgets(fileBuffer,sizeof(fileBuffer),f_I);
    ptr=strtok(fileBuffer," ");
    for (i = 0; i < arrLen; i++){
        arrayFile[i] = atoi(ptr);
        ptr=strtok(NULL," ");
    }
    fclose(f_I);

    //Ahora con el array armado, usar el algoritmo para ordenarlo
    //printf("Arreglo inicial:\n");printArr(arrayFile,arrLen);

    flipSort(arrayFile,arrLen);

    //Ya con el array ordenado, a ver como se ve
    //printf("Arreglo en orden:");printArr(arrayFile,arrLen);

    return 1;
}
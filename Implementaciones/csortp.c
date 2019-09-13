#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAXLON 70
#define MAX 9
#define MAXARC 100000

struct Dato{
    char usuario[MAXLON];
    char comando[MAXLON];
    char numProc[MAXLON];
    int tiempoEjec;
    char anio[MAXLON];
    char hora[MAXLON];
};

struct Archivo{
    char nombre[MAXLON];
    struct Dato *procesos;
    int numProcesos;
};

//Lee un archivo que llega por parámetro y lo guarda en una estructura de tipo Archivo.
void leerArchivo(struct Archivo *arc, char *nombreArc){

    struct Dato datos;
    int cont;
    FILE *stream;
    char cadena[MAXLON];

    cont = 0;
    stream = fopen(nombreArc, "r");
    strcpy(arc->nombre, nombreArc);

    if(stream == NULL){
        perror("Error. No se pudo arbir el archivo.");
        exit(1);
    }

    while( !feof( stream ) ){

        fscanf(stream, "%s", cadena);
        if(cont == 0){
            strcpy(datos.usuario, cadena);
            cont++;  
        }
        else if(cont == 1){
            strcpy(datos.comando, cadena);
            cont++;
        }
        else if(cont == 2){
            strcpy(datos.numProc, cadena);
            cont++;
        }
        else if(cont == 3){
            datos.tiempoEjec = atoi(cadena);
            cont++;
        }
        else if(cont == 4){
            strcpy(datos.anio, cadena);
            cont++;
        }
        else if(cont == 5){
            strcpy(datos.hora, cadena);
            cont = 0;
        }

        if(cont == 0){
            *(arc->procesos + arc->numProcesos) = datos;
            arc->numProcesos++;
        }
    }
    fclose(stream);
}

//Escribe un archivo con nombre que llega por parámetro lo procesos que se encuentran en una estructura 
//de tipo archivo. 
void escribirArchivo(struct Archivo *arc, char *salida, int flag){

    char cadena[MAXLON];
    FILE *stream;

    strcpy(cadena, salida);
    strcat(cadena, "Temp.txt");

    if(flag == 1){
        stream = fopen(salida, "w");
    }else{
        stream =  fopen(cadena, "w");
    }

    if(stream == NULL){
        perror("Error. No se pudo abrir el archivo.");
        exit(1);
    }

    for(int i = 0; i < arc->numProcesos; i++){
        fprintf(stream, "%s %s %s %d %s %s \n", arc->procesos[i].usuario, arc->procesos[i].comando,
                                                arc->procesos[i].numProc, arc->procesos[i].tiempoEjec,
                                                arc->procesos[i].anio, arc->procesos[i].hora);
    }
    fclose(stream);
}

//Ordena el archivo que llega por parametro con el método burbuja. Primero se ordena por el tiempo de 
//ejecución, luego por año y por último por la hora. Al finalizar el ordenamiento se escriben los 
//procesos ordenados de cada archivo en un archivo temporal.
void sortp(struct Archivo *arc){

    struct Dato aux;

    for(int i = 0; i < arc->numProcesos; i++){
        for(int j = i + 1; j < arc->numProcesos; j++){

            if(arc->procesos[i].tiempoEjec > arc->procesos[j].tiempoEjec){
                aux = arc->procesos[i];
                arc->procesos[i] = arc->procesos[j];
                arc->procesos[j] = aux;
            }
            else if(arc->procesos[i].tiempoEjec == arc->procesos[j].tiempoEjec){
            
                if(strcmp(arc->procesos[i].anio, arc->procesos[j].anio) > 0){
                    aux = arc->procesos[i];
                    arc->procesos[i] = arc->procesos[j];
                    arc->procesos[j] = aux;
                }
                else if(strcmp(arc->procesos[i].anio, arc->procesos[j].anio) == 0){

                    if(strcmp(arc->procesos[i].hora, arc->procesos[j].hora) > 0){
                        aux = arc->procesos[i];
                        arc->procesos[i] = arc->procesos[j];
                        arc->procesos[j] = aux;
                    }
                }
            }

        }
    }
    escribirArchivo(arc, arc->nombre, 0);
}

//Función auxiliar del método MergeSort
void merge(struct Archivo *arc, int l, int m, int r){

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct Dato *aux1 = (struct Dato *) calloc(n1, sizeof(struct Dato));
    struct Dato *aux2 = (struct Dato *) calloc(n2, sizeof(struct Dato));

    for(i = 0; i < n1; i++){
        aux1[i] = arc->procesos[l + i];
    }
    for(j = 0; j < n2; j++){
        aux2[j] = arc->procesos[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while(i < n1 && j < n2){

        if(aux1[i].tiempoEjec < aux2[j].tiempoEjec){
            arc->procesos[k] = aux1[i];
            i++; 
        }
        else if(aux1[i].tiempoEjec == aux2[j].tiempoEjec){
        
            if(strcmp(aux1[i].anio, aux2[j].anio) < 0){
                arc->procesos[k] = aux1[i];
                i++; 
            }
            else if(strcmp(aux1[i].anio, aux2[j].anio) == 0){

                if(strcmp(aux1[i].hora, aux2[j].hora) < 0){
                    arc->procesos[k] = aux1[i];
                    i++; 
                }
                else{
                    arc->procesos[k] = aux2[j];
                    j++;
                }
            }
            else{
                arc->procesos[k] = aux2[j];
                j++;
            }
        }
        else{
            arc->procesos[k] = aux2[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        arc->procesos[k] = aux1[i];
        i++;
        k++;
    }

    while(j < n2){
        arc->procesos[k] = aux2[j];
        j++;
        k++;
    }
}

//Ordena los procesos de un archivo utilizando el método MergeSort. Se utilizó una base del codigo 
//encontrado en: https://www.geeksforgeeks.org/merge-sort/ sin embargo se realizaron modificaciones
//al código para poder ordenar la estructura como se debía
void mergesort(struct Archivo *arc, int l, int r){

    if(l < r){
        int m = l + (r - l) / 2;
        mergesort(arc, l, m); 
        mergesort(arc, m + 1, r);
        merge(arc, l, m, r);
    }
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char * argv[]){
    FILE * entrada;
    FILE * salida;
    char * nombreDeArchivos;
    int n = argc-1;
    char ** listaDeArchivos;
    if(argv[1] == "-r" && argc < 3 || argc <2 ){
        perror("no hay suficientes argumentos");
        exit(1);
    }
    for (int i = 0; i < 1; i++)
    {
        *(listaDeArchivos+i)= argv[i]; 
        printf(*(listaDeArchivos+i));
    }
    

    return 0;
}

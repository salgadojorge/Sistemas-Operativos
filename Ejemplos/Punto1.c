#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char** argv ){

    if( argc != 3 ){
        printf("El número de parámetros es invalido. ");
        exit(1);
    }
    else{
        char nombre[1048];
        int numero;

        strcpy(nombre, argv[1]);
        numero = atoi(argv[2]);

        for(int i = 0; i < numero; i++){
            printf("%s \n", nombre);
        }
    }

    return 0;
}
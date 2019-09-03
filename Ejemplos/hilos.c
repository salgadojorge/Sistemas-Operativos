#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void imprimir(char* cad){
    printf("%s", cad);
}

int main(int argc, char* argv[]){
    pthread_t hilo;
    if(argc!=3){
        perror("numero de argumentos invalido");
        exit(1);
    }
    for(int i = 1; i < argc; i++){
       int pt = pthread_create(&hilo, NULL, (void*)imprimir, argv[i] );
    if( pt < 0 ){
        perror("Error creando el hilo");
        exit(0);
    }

    
    }
    pthread_exit(0);
}
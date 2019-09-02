#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#define MAXLON 1000

//INTEGRANTES: Juan Camilo Chafloque y Jorge Salgado

void cuenta (char *nombre) {
    int pos, cont= 0, leidos;
    char cadena[MAXLON];
    int fd;
    fd= open(nombre, O_RDONLY);
    while ((leidos= read (fd, cadena, MAXLON))!= 0)
        for (pos= 0; pos< leidos; pos++)
            if ((cadena[pos]== 'a') || (cadena[pos]== 'A'))
                cont++;
            
            printf ("Fichero %s:%d caracteres ’a’ o ’A’ encontrados\n", nombre, cont);
            close (fd);
}

int main (int argc, char *argv[]) {

    if (argc != 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }

    pthread_t hilo;
    int pt = pthread_create(&hilo, NULL, (void*)cuenta, argv[1] );
    if( pt < 0 ){
        perror("Error creando el hilo");
        exit(0);
    }

    pthread_exit(0);
}

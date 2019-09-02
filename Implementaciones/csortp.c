#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char * argv[]){
    FILE * entrada;
    FILE * salida;
    char * nombreDeArchivos;
    int n = argc;
    char buffer[1048];
    char *listaDeArchivos[1048];

    if(argc<2){
        perror("No hay suficientes argumentos");
        exit(1);
    }

    for(int i=0; i<n; i++)
    {
        strcpy(buffer, argv[i]);
    	listaDeArchivos[i] = strdup(buffer);
    }
    
    for(int i=1; i<n; i++){
        printf("%s", "argumento: ");
    	printf("%s", listaDeArchivos[i]);
        printf("%s", " ");
	
    }

    return 0;
}

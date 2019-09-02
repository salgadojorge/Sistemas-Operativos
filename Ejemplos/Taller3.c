#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc,char  *argv[]){

    int vect[3];
    int numProc = 2;
    pid_t child;

    if(argc < 4){
        printf("Cantidad de argumentos invalidos.");
        exit(1);
    }

    vect[0] = atoi(argv[1]);
    vect[1] = atoi(argv[2]);
    vect[2] = atoi(argv[3]);

    for(int i = 0; i < numProc; i++){

        if((child = fork()) == 0){

            if(i == 0){

                int aux;
                for(int i = 0; i < 3; i++){
                    for(int j = i + 1; j < 3; j++){
                        if(vect[i] > vect[j]){
                            aux = vect[i];
                            vect[i] = vect[j];
                            vect[j] = aux;
                        }
                    }
                }
                printf("\nHijo con PID %d imprime %d %d %d", getpid(), vect[0], vect[1], vect[2]);
                exit(0);

            }else{

                int aux;
                for(int i = 0; i < 3; i++){
                    for(int j = i + 1; j < 3; j++){
                        if(vect[i] < vect[j]){
                            aux = vect[i];
                            vect[i] = vect[j];
                            vect[j] = aux;
                        }
                    }
                }
                printf("\nHijo con PID %d imprime %d %d %d", getpid(), vect[0], vect[1], vect[2]);
                exit(0);
            }

        }
    }

    return 0;
}
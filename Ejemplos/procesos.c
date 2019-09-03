#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[]){
    pid_t child;
    if(argc!=3){
        perror("numero de argumentos invalido");
        exit(1);
    }
    for(int i = 1; i < argc; i++){
       if((child = fork())==0){
           printf("ID: %d cadena %s", getpid() , argv[i]);
           exit(0);
       }
    }
    int status; 
    for( int i = 1; i<argc ; i++){
        wait(&status);
    }
    return 0;
}
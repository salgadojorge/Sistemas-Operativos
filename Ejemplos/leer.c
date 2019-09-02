
/* archivo leer.c
 * Ejemplo de uso del perror() para validar llamadas al sistema
 *
 * Realizado por Mariela Curiel,  Enero 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char *argv[]){

  char buffer[5]="hola";
  int a = 7, fd;

  if (argc < 2) {
    printf ("Modo de uso: leer filename \n");
    exit(-1);
  }

  //Según el man, la función open retorna un valor negativo cuando hay un error al abrir el archivo.
  //Que en este caso es el argumento 1 del main. 
  fd = open(argv[1], O_RDWR, S_IRWXU|S_IRWXO);
  if( fd > 0 ){
    write (fd, buffer, sizeof(buffer));
    close(fd);
  }
  else{
    perror("Error:");
    exit(-1);
  }

  return 0;
}




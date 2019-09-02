#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int n = 0, temp = 0;
 	pid_t phijo;
	
	n = argc-1;
	
	int lista[n];
	int lista_dos[n];	
	
	for(int i=0; i<n; i++){
		lista[i] = atoi(*&argv[i+1]);
		lista_dos[i] = atoi(*&argv[i+1]);
	}
	
	for(int h=0; h<2; h++){
		if((phijo = fork()) < 0){
			perror("fork:");
			exit(1);			
		}
		if(phijo == 0){
			printf("Proceso hijo con PID: %d \n", getpid());
			if(h == 0){	
				//ordenamiento ascendente
				for(int i=0; i<n; i++){
       					for(int j=0; j < n-i;j++) {
         					if(lista[j] > lista[j+1]){
            						temp = lista[j];
            						lista[j] = lista[j+1];
            						lista[j+1] = temp;
          					}
       					}
					printf("%d\t", lista[i]);
				}
				printf("\n");
			}
			else{
				//ordenamiento descendente
				for(int i=0; i<n; i++){
       					for(int j=0; j < n-i; j++) {
         					if(lista_dos[j] < lista[j+1]){
            						temp = lista_dos[j];
            						lista_dos[j] = lista_dos[j+1];
            						lista_dos[j+1] = temp;
          					}
       					}
					printf("%d\t", lista_dos[i]);
				}
				printf("\n");				
			}
		}
		else{
			printf("Proceso padre con PID: %d \n", getpid());
		}
	}	

	return 0;
}

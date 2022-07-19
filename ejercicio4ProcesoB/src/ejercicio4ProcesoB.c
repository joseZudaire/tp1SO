#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define SEMA "seA"
#define SEMB "seB"
#define SEMC "seC"

int cantidad;

sem_t *semA;
sem_t *semB;
sem_t *semC;

int main(int argc, char **argv) {

	if (argc == 2 && (!strncmp(argv[1],"0",1) || atoi(argv[1]) != 0)) {
		cantidad = atoi(argv[1]);
	} else {
		printf("ERROR: Se debe ingresar un solo argumento y debe ser numérico\n");
		return (-1);
	}

	semA = sem_open(SEMA, O_CREAT, 0644, 1);
	semB = sem_open(SEMB, O_CREAT, 0644, 0);
	semC = sem_open(SEMC, O_CREAT, 0644, 0);

	printf("\nSe crea proceso B\n");
	while(cantidad>0){
		
		cantidad--;

		sem_wait(semB);
		//el sleep es para ver mejor la sincronización
		sleep(1);
		printf("\nB\n");
		sem_post(semA);
	}
	printf("\nTerminó el proceso B\n");

	return 0;
}

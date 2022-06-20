#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SEMA "seA"
#define SEMB "seB"
#define SEMC "seC"

int cantidad;

sem_t *semA;
sem_t *semB;
sem_t *semC;

int main(int argc, char **argv) {

	cantidad = atoi(argv[1]);

	printf("\nSe crea proceso C\n");

	semA = sem_open(SEMA, O_CREAT, 0644, 1);
	semB = sem_open(SEMB, O_CREAT, 0644, 0);
	semC = sem_open(SEMC, O_CREAT, 0644, 0);

	//proceso C
	while(cantidad>0){
		cantidad--;
		sem_wait(semC);
		sleep(1);
		//el sleep es para ver mejor la sincronización
		printf("\nC\n");
		sem_post(semA);
	}
	printf("\nTerminó el proceso C\n");

	return 0;
}

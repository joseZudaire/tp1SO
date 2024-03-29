#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

// Compilacion: gcc -Wall -o ejercicio4ProcesoA ejercicio4ProcesoA.c -pthread

#define SEMA "seA"
#define SEMB "seB"
#define SEMC "seC"

sem_t *semA;
sem_t *semB;
sem_t *semC;

int main(int argc, char **argv) {
	int cantidad = atoi(argv[0]);

	semA = sem_open(SEMA, O_CREAT, 0644, 1);
	semB = sem_open(SEMB, O_CREAT, 0644, 0);
	semC = sem_open(SEMC, O_CREAT, 0644, 0);

	while (cantidad>0) {	
		cantidad--;
		sem_wait(semA);
		printf("A\n");	
		sem_post(semB);
		sem_wait(semA);
		
		printf("A\n");
		sem_post(semC);
	}
	sem_unlink(SEMA);
	sem_unlink(SEMB);
	sem_unlink(SEMC);
	sem_destroy(semA);
	sem_destroy(semB);
	sem_destroy(semC);

	return 0;
}

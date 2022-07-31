#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

// Compilacion: gcc -Wall -o ejercicio4ProcesoB ejercicio4ProcesoB.c -pthread

#define SEMA "seA"
#define SEMB "seB"

sem_t *semA;
sem_t *semB;

int main(int argc, char **argv) {
	int cantidad = atoi(argv[0]);

	semA = sem_open(SEMA, O_CREAT, 0644, 1);
	semB = sem_open(SEMB, O_CREAT, 0644, 0);

	while (cantidad>0) {	
		cantidad--;
		sem_wait(semB);
		printf("B\n");
		sem_post(semA);
	}
	
	return 0;
}

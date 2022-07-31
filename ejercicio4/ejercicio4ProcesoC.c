#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

// Compilacion: gcc -Wall -o ejercicio4ProcesoC ejercicio4ProcesoC.c -pthread

#define SEMA "seA"
#define SEMC "seC"

sem_t *semA;
sem_t *semC;

int main(int argc, char **argv) {
	int cantidad = atoi(argv[0]);

	semA = sem_open(SEMA, O_CREAT, 0644, 1);
	semC = sem_open(SEMC, O_CREAT, 0644, 0);

	while (cantidad>0) {
		cantidad--;
		sem_wait(semC);
		printf("C\n");
		sem_post(semA);
	}

	return 0;
}

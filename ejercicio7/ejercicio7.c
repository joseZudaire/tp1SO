#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

// Ejercicio 7: Implementación de una sincronización con procesos emparentados PadreA, HijoB y HijoC de forma tal, que la secuencia de ejecución y acceso a su sección crítica sea la siguiente: PadreAHijoBPadreAHijoC... detener el proceso luego de N iteraciones completas (el número N se ingresa por línea de comandos). HijoB e HijoC son hermanos. Resolver la sincronización de la forma que a Ud. le parezca más apropiada (no usar señales).

// Compilacion: gcc -Wall -o ejercicio7 ejercicio7.c -pthread

#define SEMA "seA"
#define SEMB "seB"
#define SEMC "seC"

int main(int argc, char **argv) {
	int cantidad = 0;
	pid_t pid;
	
	sem_t *semA;
	sem_t *semB;
	sem_t *semC;
	
	if (argc == 2 && (!strncmp(argv[1],"0",1) || atoi(argv[1]) != 0)) {
		cantidad = atoi(argv[1]);
	} else {
		printf("ERROR: Se debe ingresar un solo argumento y debe ser numérico\n");
		return (-1);
	}
	
	semA = sem_open(SEMA, O_CREAT, 0644, 1);
	semB = sem_open(SEMB, O_CREAT, 0644, 0);
	semC = sem_open(SEMC, O_CREAT, 0644, 0);

	pid = fork();	
	if (pid == 0) {
		// HijoB
		while (cantidad > 0) {
			cantidad--;
			sem_wait(semB);
			printf("B\n");
			sem_post(semA);
		}
		return 0;
	}
		
	pid = fork();
	if (pid == 0) {
		// HijoC
		while (cantidad > 0) {
			cantidad--;
			sem_wait(semC);
			printf("C\n\n");
			sem_post(semA);
		}
		return 0;
	}
	// PadreA
	while (cantidad > 0) {
		cantidad--;
		sem_wait(semA);
		printf("A\n");
		sem_post(semB);

		sem_wait(semA);
		printf("A\n");
		sem_post(semC);
	}
		
	while (wait(0) > 0);

	sem_unlink(SEMA);
	sem_unlink(SEMB);
	sem_unlink(SEMC);
	sem_destroy(semA);
	sem_destroy(semB);
	sem_destroy(semC);

	return 0;
}


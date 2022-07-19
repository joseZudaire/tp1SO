/*
 ============================================================================
 Name        : ejercicio3.c
 Author      : 
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>

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

	int idSemA = shm_open("/semA", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemA, sizeof(sem_t));

	int idSemB = shm_open("/semB", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemB, sizeof(sem_t));

	semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
	semB = mmap(500, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemB, 0);

	while(cantidad > 0) {
		cantidad--;

		sem_wait(semB);

		printf("\nB\n");
		sleep(1); //es solamente así se puede ver la sincro en tiempo real
		sem_post(semA);
	}

	printf("\nTerminó el proceso B\n");


	sem_destroy(semA);
	sem_destroy(semB);
	sem_destroy(semC);

	shmctl(idSemB, IPC_RMID, 0);

	return 0;
}



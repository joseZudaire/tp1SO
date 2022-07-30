#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

// Para compilar: gcc -Wall -o ejercicio5ProcesoB ejercicio5ProcesoB.c -pthread -lrt

sem_t *semA;
sem_t *semB;
sem_t *semC;

int main(int argc, char **argv) {
	int cantidad = 0;

	cantidad = atoi(argv[0]);

	int idSemA = shm_open("/semA", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemA, sizeof(sem_t));
	
	int idSemB = shm_open("/semB", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemB, sizeof(sem_t));

	semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
	semB = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemB, 0);

	while (cantidad > 0) {
		cantidad--;
		sem_wait(semB);
		printf("B\n");
		sem_post(semA);
	}

	return 0;
}



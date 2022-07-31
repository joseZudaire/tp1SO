#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

// Para compilar: gcc -Wall -o ejercicio5ProcesoC ejercicio5ProcesoC.c -pthread -lrt

sem_t *semA;
sem_t *semC;

int main(int argc, char **argv) {
	int cantidad = 0;

	cantidad = atoi(argv[0]);

	int idSemA = shm_open("/semA", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemA, sizeof(sem_t));
	
	int idSemC = shm_open("/semC", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemC, sizeof(sem_t));
	
	if (idSemA == (-1) || idSemC == (-1)) {
		printf("Error de shm_open. Verificar existencia de semáforos\n");
		return (-1);
	} 

	semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
	semC = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemC, 0);

	while (cantidad > 0) {
		cantidad--;
		sem_wait(semC);
		printf("C\n");
		sem_post(semA);
	}

	return 0;
}

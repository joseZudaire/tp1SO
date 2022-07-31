#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

// Compilacion: gcc -Wall -o ejercicio5Sem_ini ejercicio5Sem_ini.c -pthread -lrt

sem_t *semA;
sem_t *semB;
sem_t *semC;

int main(void) {
	int idSemA = shm_open("/semA", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemA, sizeof(sem_t));

	int idSemB = shm_open("/semB", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemB, sizeof(sem_t));

	int idSemC = shm_open("/semC", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemC, sizeof(sem_t));
	
	if (idSemA != (-1) || idSemB != (-1) || idSemC != (-1) ) {
		printf("\nInicialización de semáforos con éxito\n");
		printf("id_Sem_A = %d\n",idSemA);
		printf("id_Sem_B = %d\n",idSemB);
		printf("id_Sem_C = %d\n",idSemC);
		printf("sem_A = 1\n");
		printf("sem_B = 0\n");
		printf("sem_C = 0\n\n");
		sem_init(semA,1,1);
		sem_init(semB,1,0);
		sem_init(semC,1,0);
		semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
		semB = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemB, 0);
		semC = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemC, 0);

	} else {
		printf("Error de semget en la dirección 0xa. Verificar existencia de semáforos\n");
		return (-1);
	}
	
	return 0;
}

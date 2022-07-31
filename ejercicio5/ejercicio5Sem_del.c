#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Compilacion: gcc -Wall -o ejercicio5Sem_del ejercicio5Sem_del.c -pthread -lrt

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
		printf("\nDestrucción de semáforos con éxito\n");
		printf("id_Sem_A = %d\n",idSemA);
		printf("id_Sem_B = %d\n",idSemB);
		printf("id_Sem_C = %d\n\n",idSemC);
		semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
		semB = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemB, 0);
		semC = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemC, 0);
		
		sem_destroy(semA);
		sem_destroy(semB);
		sem_destroy(semC);

		shmctl(idSemA, IPC_RMID, 0);
		shmctl(idSemB, IPC_RMID, 0);
		shmctl(idSemC, IPC_RMID, 0);

	} else {
		printf("Error de semget en la dirección 0xa. Verificar existencia de semáforos\n");
		return (-1);
	}
	
	exit(0);
}

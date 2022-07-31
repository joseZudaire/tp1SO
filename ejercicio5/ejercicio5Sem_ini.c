#include <unistd.h>
#include <stdlib.h>
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

	semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
	semB = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemB, 0);
	semC = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemC, 0);

	sem_init(semA,1,1);
	sem_init(semB,1,0);
	sem_init(semC,1,0);
	
	exit(0);
}
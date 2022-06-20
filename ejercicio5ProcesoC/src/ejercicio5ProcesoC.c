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

int cantidad;

sem_t *semA;
sem_t *semB;
sem_t *semC;

int main(int argc, char **argv) {

	cantidad = atoi(argv[1]);

	int idSemA = shm_open("/semA", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemA, sizeof(sem_t));

	int idSemC = shm_open("/semC", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemC, sizeof(sem_t));

	semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
	semC = mmap(1000, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemC, 0);

	while(cantidad > 0) {
		cantidad--;
		sem_wait(semC);

		printf("\nC\n");
		sleep(1); //es solamente así se puede ver la sincro en tiempo real

		sem_post(semA);

	}
	printf("\nTerminó el proceso C\n");

	sem_destroy(semA);
	sem_destroy(semB);
	sem_destroy(semC);

	shmctl(idSemC, IPC_RMID, 0);

	return 0;
}



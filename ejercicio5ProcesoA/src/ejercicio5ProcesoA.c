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

	int idSemC = shm_open("/semC", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	ftruncate(idSemC, sizeof(sem_t));

	semA = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemA, 0);
	semB = mmap(500, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemB, 0);
	semC = mmap(1000, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, idSemC, 0);

	sem_init(semA,1,1);
	sem_init(semB,1,0);
	sem_init(semC,1,0);

	while(cantidad>0){
		
		cantidad--;

		sem_wait(semA);
		sleep(1);
		//el sleep es para ver mejor la sincronización
		printf("\n\nA\n");

		sem_post(semB);

		sem_wait(semA);

		printf("\nA\n");
		sem_post(semC);
	}
	printf("\nTerminó el proceso A\n");

	sem_destroy(semA);
	sem_destroy(semB);
	sem_destroy(semC);


	shmctl(idSemA, IPC_RMID, 0);
	shmctl(idSemB, IPC_RMID, 0);
	shmctl(idSemC, IPC_RMID, 0);

	return 0;
}



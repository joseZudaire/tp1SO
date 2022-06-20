#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SEMA "seA"
#define SEMB "seB"
#define SEMC "seC"

int cantidad;

sem_t *semA;
sem_t *semB;
sem_t *semC;

int main(int argc, char **argv) {

	cantidad = atoi(argv[1]);

	printf("\nSe crea proceso A\n");

	semA = sem_open(SEMA, O_CREAT, 0644, 1);
	semB = sem_open(SEMB, O_CREAT, 0644, 0);
	semC = sem_open(SEMC, O_CREAT, 0644, 0);

	char strCantidad[2];
	sprintf(strCantidad,"%i", cantidad);

	while(cantidad>0){
		
		cantidad--;

		sem_wait(semA);
		sleep(1);
		//el sleep es para ver mejor la sincronización
		printf("\n\nA\n");
		
		sem_post(semB);

		sem_wait(semA);
		sleep(1);
		//el sleep es para ver mejor la sincronización
		printf("\nA\n");
		sem_post(semC);
	}
	printf("\nTerminó el proceso A\n");
	sem_unlink(SEMA);
	sem_unlink(SEMB);
	sem_unlink(SEMC);
	sem_destroy(semA);
	sem_destroy(semB);
	sem_destroy(semC);

	return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define SEMA "seA"
#define SEMB "seB"
#define SEMC "seC"

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

	pid_t pid = fork();
	
	if(pid == 0) {
		//proceso B

		semA = sem_open(SEMA, O_CREAT, 0644, 1);
		semB = sem_open(SEMB, O_CREAT, 0644, 0);
		semC = sem_open(SEMC, O_CREAT, 0644, 0);

		printf("\nSe crea proceso B\n");

		while(cantidad>0){
			cantidad--;
			sem_wait(semB);
			printf("\nB\n");
			sem_post(semA);
		}
		printf("\nTerminó el proceso B\n");

	}
	else {

		pid = fork();

		if (pid == 0) {
			printf("\nSe crea proceso C\n");

			semA = sem_open(SEMA, O_CREAT, 0644, 1);
			semB = sem_open(SEMB, O_CREAT, 0644, 0);
			semC = sem_open(SEMC, O_CREAT, 0644, 0);

			//proceso C
			while(cantidad>0){
				cantidad--;
				sem_wait(semC);
				printf("\nC\n");
				sem_post(semA);
			}
			printf("\nTerminó el proceso C\n");
		}
		else {
			printf("\nSe crea proceso padre A\n");

			semA = sem_open(SEMA, O_CREAT, 0644, 1);
			semB = sem_open(SEMB, O_CREAT, 0644, 0);
			semC = sem_open(SEMC, O_CREAT, 0644, 0);

			//proceso A
			while(cantidad>0){
				cantidad--;

				sem_wait(semA);
				printf("\n\nA\n");
				sem_post(semB);

				sem_wait(semA);
				printf("\nA\n");
				sem_post(semC);
			}
			while(wait(0) > 0);

			printf("\nTerminó el proceso padre A\n");
			sem_unlink(SEMA);
			sem_unlink(SEMB);
			sem_unlink(SEMC);
			sem_destroy(semA);
			sem_destroy(semB);
			sem_destroy(semC);
		}

	}
	return 0;
}



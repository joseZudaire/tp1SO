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
//#include <pthread.h>
#include <unistd.h>
//#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
//#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

int salir;
char comando[64];
pid_t pid;

void f_sigint(int);
void f_sigchld(int);

int main(int argc, char **argv) {

	signal(SIGINT,(void*)f_sigint);
	signal(SIGCHLD,(void*)f_sigchld);

	printf("\nEscriba comando a ejecutar: \n");
	memset(comando, '\0', 64);
	fgets(comando, 64, stdin);

	for(int i = 0; i < 64; i++) {
		if(comando[i] == '\n') {
			comando[i] = '\0';
		}
	}

	salir = 1;

	char** args[10];

	for(int j = 0; j < 10; j++) {
		args[j] = malloc(sizeof(char)*64);
		memset(args[j], '\0', 64*sizeof(char));
	}

	int argID = 0;
	int j = 0;

	for(int i = 0; i < 64; i++) {
		if(comando[i] == ' ') {
			//args[argID] = malloc(sizeof(char)*(i-j+1));
			memcpy(args[argID], &comando[j], (i-j)*sizeof(char));
			j = i + 1;
			argID++;
		}
	}

	//args[argID] = malloc(sizeof(char)*(64-j));
	memcpy(args[argID], &comando[j], (64-j));
	args[argID+1] = NULL;

	/*
	int argID, j;
	char** args[10];
	salir = 1;

	memcpy(comando, "nosalir", 6);*/

	while((strcmp(comando,"salir")) && (salir==1)) {

		/*argID = 0;
		j = 0;

		printf("\nEscriba comando a ejecutar: \n");
		memset(comando, '\0', 64);

		fgets(comando, 64, stdin);

		for(int i = 0; i < 64; i++) {
			printf("\nEntramos para los enter\n");
			if(comando[i] == '\n') {
				comando[i] = '\0';
			}
		}

		printf("\nAntes del memset\n");

		for(int i = 0; i < 10; i++) {
			args[i] = malloc(sizeof(char)*64);
			memset(args[i], '\0', 64*sizeof(char));
		}

		printf("\nDespues del memset\n");

		for(int i = 0; i < 64; i++) {
			if(comando[i] == ' ') {
				printf("\nEntramos para los espacios\n");
				//args[argID] = malloc(sizeof(char)*(i-j+1));
				memcpy(args[argID], &comando[j], (i-j)*sizeof(char));
				j = i + 1;
				argID++;
			}
		}

		printf("\nDespues de los espacios\n");

		//args[argID] = malloc(sizeof(char)*(64-j));
		memcpy(args[argID], &comando[j], (64-j));
		args[argID+1] = NULL;*/

		pid = fork();
		if(pid == 0) {
			execlp(args[0], args, NULL);
			printf("\nComando no válido\n");
			exit(0);
		}
		else {
			if(pid > 0) {
				waitpid(pid,0,0);
				printf("\nComando ejecutado\n");
				printf("\nEscriba comando a ejecutar: \n");
				memset(comando, '\0', 64);
				fgets(comando, 64, stdin);

				for(int i = 0; i < 64; i++) {
					if(comando[i] == '\n') {
						comando[i] = '\0';
					}
				}

				for(int j = 0; j < 10; j++) {
					args[j] = malloc(sizeof(char)*64);
					memset(args[j], '\0', 64*sizeof(char));
				}

				argID = 0;
				j = 0;

				for(int i = 0; i < 64; i++) {
					if(comando[i] == ' ') {
						//args[argID] = malloc(sizeof(char)*(i-j+1));
						memcpy(args[argID], &comando[j], (i-j)*sizeof(char));
						j = i + 1;
						argID++;
					}
				}

				//args[argID] = malloc(sizeof(char)*(64-j));
				memcpy(args[argID], &comando[j], (64-j));
				args[argID+1] = NULL;


			}
			else {
				perror("\nError fork\n");
			}
		}
	}

	while((pid = wait(0)) > 0);

	exit(0);

}

void f_sigint(int s) {
	printf("\nSe activó señal de interrupción\n");
	salir = 0;
	int totalNulos = 0;
	for(int i = 0; i < 64; i++){
		if(comando[i] == '\0'){
			totalNulos++;
		}
	}
	if(totalNulos == 64) {
		while((pid = wait(0)) > 0);
		exit(0);
	}
}

void f_sigchld(int s) {
	printf("\nSe terminó el proceso hijo\n");
}



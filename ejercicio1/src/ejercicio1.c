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
	scanf("%s", comando);

	salir = 1;

	while((strcmp(comando,"salir")) && (salir==1)) {
		pid = fork();
		if(pid == 0) {
			execlp(comando, comando, NULL);
			printf("\nComando no válido\n");
			exit(0);
		}
		else {
			if(pid > 0) {
				waitpid(pid,0,0);
				printf("\nComando ejecutado\n");
				printf("\nEscriba comando a ejecutar: \n");
				memset(comando, '\0', 64);
				scanf("%s", comando);
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



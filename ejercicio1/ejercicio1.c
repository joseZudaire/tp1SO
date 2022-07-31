#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Ejercicio 1: Implementación del programa Shell (en su versión más completa, que soporta procesos foreground y background; que haga uso de la señal SIGCHLD para verificar la finalización de procesos en background) que evite la existencia de procesos zombies. El programa termina cuando el usuario ingresa el comando “salir”. Si el usuario presiona CTRL+C el programa esperará a que terminen todos los procesos y luego finalizará sin dejar procesos zombies o huérfanos.

// Compilacion: gcc -Wall -o ejercicio1 ejercicio1.c

int salir;
char comando[64];
pid_t pid;
char** args;

void f_sigint(int);
void f_sigchld(int);
void reemplazar_enter(char*);
void separar_argumentos(char**, char*);

int main(int argc, char **argv) {

	args = malloc(10*sizeof(char*));

	signal(SIGINT,(void*)f_sigint);
	signal(SIGCHLD,(void*)f_sigchld);

	printf("\nEscriba comando a ejecutar: \n");
	memset(comando, '\0', 64);
	fgets(comando, 64, stdin);

	reemplazar_enter(comando);

	salir = 1;

	for (int k = 0; k < 10; k++) {
		args[k] = malloc(sizeof(char)*64);
		memset(args[k], '\0', 64*sizeof(char));
	}

	separar_argumentos(args, comando);

	while ((strcmp(comando,"salir")) && (salir==1)) {
		pid = fork();
		if (pid == 0) {
			execv(args[0], args);
			printf("\nComando no válido\n");
			exit(0);
		} else {
			if (pid > 0) {
				printf("\nComando ejecutado\n");
				printf("\nEscriba comando a ejecutar: \n");
				memset(comando, '\0', 64);
				fgets(comando, 64, stdin);

				reemplazar_enter(comando);

				for(int k = 0; k < 10; k++) {
					free(args[k]);
					args[k] = malloc(sizeof(char)*64);
					memset(args[k], '\0', 64*sizeof(char));
				}
				separar_argumentos(args, comando);
			} else {
				perror("\nError fork\n");
			}
		}
	}

	while ((pid = wait(0)) > 0);
	
	for (int i = 0; i < 10; i++) {
		free(args[i]);
	}	
	free(args);

	exit(0);
}

void separar_argumentos(char** args, char* comando) {
	int argID = 0;
	int j = 0;

	for (int i = 0; i < 64; i++) {
		if (comando[i] == ' ') {
			memcpy(args[argID], &comando[j], (i-j)*sizeof(char));
			j = i + 1;
			argID++;
		}
	}
	memcpy(args[argID], &comando[j], (64-j));
	free(args[argID+1]);
	args[argID+1] = NULL;
}

void reemplazar_enter(char* comando) {
	for(int i = 0; i < 64; i++) {
		if(comando[i] == '\n') {
			comando[i] = '\0';
		}
	}
}

void f_sigint(int s) {
	salir = 0;
	int totalNulos = 0;
	
	printf("\nSe activó señal de interrupción\n");
	
	for(int i = 0; i < 64; i++){
		if(comando[i] == '\0'){
			totalNulos++;
		}
	}
	if (totalNulos == 64) {
		while((pid = wait(0)) > 0);
		
		for(int i = 0; i < 10; i++) {
			free(args[i]);
		}
		free(args);
		exit(0);
	}
}

void f_sigchld(int s) {
	printf("\nSe terminó el proceso hijo\n");
}

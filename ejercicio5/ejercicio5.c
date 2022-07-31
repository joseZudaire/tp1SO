#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Ejercicio 5: Idem anterior resolviendo la sincronización con semáforos Posix sin nombre

// Compilacion: gcc -Wall -o ejercicio5 ejercicio5.c

int main(int argc, char *argv[]) {
	pid_t pid;

	if (!(argc == 2 && (!strncmp(argv[1],"0",1) || atoi(argv[1]) != 0))) {
		printf("ERROR: SE DEBE INGRESAR UN SOLO ARGUMENTO Y DEBE SER NUMÉRICO\n");
		return (-1);
	}
	
	// INICIALIZO SEMÁFOROS
	pid = fork();	
	if (pid == 0) {
		char *vector[0];
		vector[0] = NULL;
		if (execvp("./ejercicio5Sem_ini",vector) == -1) printf("ERROR EN EXECVP INICIALIZACIÓN DE SEMÁFORO\n");
	}
	wait(0);
	
	// INICIALIZO PROCESO A
	pid = fork();	
	if (pid == 0) {
		char *vector[1];
		vector[0] = argv[1];
		vector[1] = NULL;
		if (execvp("./ejercicio5ProcesoA",vector) == -1) printf("ERROR EN EXECVP PROCESO A\n");
	}
		
	// INICIALIZO PROCESO B
	pid = fork();	
	if (pid == 0) {
		char *vector[1];
		vector[0] = argv[1];
		vector[1] = NULL;
		if (execvp("./ejercicio5ProcesoB",vector) == -1) printf("ERROR EN EXECVP PROCESO B\n");
	}
	
	// INICIALIZO PROCESO C
	pid = fork();	
	if (pid == 0) {
		char *vector[1];
		vector[0] = argv[1];
		vector[1] = NULL;
		if (execvp("./ejercicio5ProcesoC",vector) == -1) printf("ERROR EN EXECVP PROCESO C\n");
	}
	
	while((pid = wait(0)) > 0);
		
	// DESTRUYO SEMÁFOROS
	pid = fork();	
	if (pid == 0) {
		char *vector[0];
		vector[0] = NULL;
		if (execvp("./ejercicio5Sem_del",vector) == -1) printf("ERROR EN EXECVP DESTRUCCIÓN DE SEMÁFOROS\n");
	}
	wait(0);
	
	return 0;
}

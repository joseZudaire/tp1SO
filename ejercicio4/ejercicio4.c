#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Ejercicio 4: Implementación de una sincronización con procesos independientes A, B y C de forma tal, que la secuencia de ejecución y acceso a su sección crítica sea la siguiente: ABAC... detener el proceso luego de N iteraciones completas (el número N se ingresa por línea de comandos). Resolver la sincronización con: semáforos Posix con nombre.

// Compilacion: gcc -Wall -o ejercicio4 ejercicio4.c

int main(int argc, char *argv[]) {
	pid_t pid;

	if (!(argc == 2 && (!strncmp(argv[1],"0",1) || atoi(argv[1]) != 0))) {
		printf("ERROR: SE DEBE INGRESAR UN SOLO ARGUMENTO Y DEBE SER NUMÉRICO\n");
		return (-1);
	}
	
	// INICIALIZO PROCESO A
	pid = fork();	
	if (pid == 0) {
		char *vector[1];
		vector[0] = argv[1];
		vector[1] = NULL;
		if (execvp("./ejercicio4ProcesoA",vector) == -1) printf("ERROR EN EXECVP PROCESO A\n");
	}
		
	// INICIALIZO PROCESO B
	pid = fork();	
	if (pid == 0) {
		char *vector[1];
		vector[0] = argv[1];
		vector[1] = NULL;
		if (execvp("./ejercicio4ProcesoB",vector) == -1) printf("ERROR EN EXECVP PROCESO B\n");
	}
	
	// INICIALIZO PROCESO C
	pid = fork();	
	if (pid == 0) {
		char *vector[1];
		vector[0] = argv[1];
		vector[1] = NULL;
		if (execvp("./ejercicio4ProcesoC",vector) == -1) printf("ERROR EN EXECVP PROCESO C\n");
	}
	
	while((pid = wait(0)) > 0);
	
	return 0;
}



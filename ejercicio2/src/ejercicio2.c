#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Compilacion: gcc -Wall -o ejercicio2 ejercicio2.c

int terminado = 0;

void f_sigint (int);

int main(int argc, char **argv) {
	int cantidad = 0;
	pid_t pid;
	
	signal(SIGINT,(void*)f_sigint);

	if (argc == 2 && (!strncmp(argv[1],"0",1) || atoi(argv[1]) != 0)) {
		cantidad = atoi(argv[1]);
	} else {
		printf("ERROR: Se debe ingresar un solo argumento y debe ser numérico\n");
		return (-1);
	}
	
	for (int i = 0; i < cantidad; i++) {
		pid = fork();
		if (pid == 0) {
			printf("\nProceso nuevo creado: mi PID es %i\n", getpid());
			break;
		}
	}
	if (pid != 0) {
		int sumaTotal = 0;
		int resultadoProceso = 0;

		for(int i = 0; i < cantidad; i++) {
			resultadoProceso = waitpid(0,0,0);
			sumaTotal = sumaTotal + resultadoProceso;
		}
		printf("\nLa sumatoria de los resultados de cada proceso es: %i\n", sumaTotal);
	} else {
		while (terminado == 0) { pause(); }
	}

	return getpid();
}

void f_sigint(int s) {
	terminado = 1;
}
